// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskGraphicsScene.cpp
//! @brief     Implements class MaskGraphicsScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskGraphicsScene.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h"
#include "GUI/coregui/Views/MaskWidgets/ISceneAdaptor.h"
#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "GUI/coregui/Views/MaskWidgets/MaskGraphicsProxy.h"
#include "GUI/coregui/Views/MaskWidgets/MaskViewFactory.h"
#include "GUI/coregui/Views/MaskWidgets/PolygonView.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMoveEvent>
#include <QItemSelection>
#include <QLineF>
#include <QPainter>

namespace
{
const QRectF default_scene_rect(0, 0, 800, 600);
const qreal min_distance_to_create_rect = 10;
} // namespace

MaskGraphicsScene::MaskGraphicsScene(QObject* parent)
    : QGraphicsScene(parent), m_maskModel(0), m_selectionModel(0), m_proxy(0),
      m_block_selection(false), m_intensityItem(0), m_currentItem(0)
{
    setSceneRect(default_scene_rect);
    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
}

MaskGraphicsScene::~MaskGraphicsScene()
{
    // Fix within #1792
    if (m_proxy)
        m_proxy->setSceneAdaptor(0);
}

void MaskGraphicsScene::setMaskContext(SessionModel* model, const QModelIndex& maskContainerIndex,
                                       IntensityDataItem* intensityItem)
{
    m_intensityItem = intensityItem;

    if (model != m_maskModel || m_maskContainerIndex != maskContainerIndex) {

        if (m_maskModel) {
            disconnect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            disconnect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                       SLOT(onRowsInserted(QModelIndex, int, int)));
            disconnect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            disconnect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsRemoved(QModelIndex, int, int)));
            disconnect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        m_maskModel = model;

        QString containerType = m_maskModel->itemForIndex(maskContainerIndex)->modelType();
        if (containerType != "MaskContainer" && containerType != "ProjectionContainer")
            throw GUIHelpers::Error(
                "MaskGraphicsScene::setMaskContext() -> Error. Not a container");

        m_maskContainerIndex = maskContainerIndex;

        if (m_maskModel) {
            connect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            connect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                    SLOT(onRowsInserted(QModelIndex, int, int)));
            connect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                    SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            connect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                    SLOT(onRowsRemoved(QModelIndex, int, int)));
            connect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        resetScene();
        updateScene();
    }
}

void MaskGraphicsScene::resetContext()
{
    m_intensityItem = nullptr;
    if (m_maskModel) {
        disconnect(m_maskModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
        disconnect(m_maskModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                   SLOT(onRowsInserted(QModelIndex, int, int)));
        disconnect(m_maskModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                   SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
        disconnect(m_maskModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SLOT(onRowsRemoved(QModelIndex, int, int)));
        disconnect(m_maskModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
    }
    m_maskModel = nullptr;
    m_maskContainerIndex = {};
    resetScene();
}

void MaskGraphicsScene::setSelectionModel(QItemSelectionModel* model)
{
    ASSERT(model);
    m_selectionModel = model;
    connect(m_selectionModel, &QItemSelectionModel::selectionChanged, this,
            &MaskGraphicsScene::onSessionSelectionChanged, Qt::UniqueConnection);
}

ColorMap* MaskGraphicsScene::colorMap()
{
    ASSERT(m_proxy);
    return m_proxy->colorMap();
}

void MaskGraphicsScene::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    if (!m_proxy)
        return;

    if (m_context.isActivityRequiresDrawingCancel(value))
        cancelCurrentDrawing();

    m_context.setActivityType(value);
    setInPanAndZoomMode(m_context.isInZoomMode());

    updateCursors();
}

void MaskGraphicsScene::onMaskValueChanged(MaskEditorFlags::MaskValue value)
{
    m_context.setMaskValue(value);
}

void MaskGraphicsScene::onRowsInserted(const QModelIndex&, int, int)
{
    updateScene();
}

void MaskGraphicsScene::onRowsAboutToBeRemoved(const QModelIndex& parent, int first, int last)
{
    m_block_selection = true;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_maskModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

void MaskGraphicsScene::onRowsRemoved(const QModelIndex&, int, int)
{
    updateScene();
}

void MaskGraphicsScene::cancelCurrentDrawing()
{
    if (isDrawingInProgress()) {
        ASSERT(m_currentItem);
        QModelIndex index = m_maskModel->indexOfItem(m_currentItem);
        m_maskModel->removeRows(index.row(), 1, index.parent());
        setDrawingInProgress(false);
    }
}

void MaskGraphicsScene::resetScene()
{
    ASSERT(m_selectionModel);
    m_block_selection = true;
    m_selectionModel->clearSelection();
    clearSelection();

    clear();
    m_ItemToView.clear();
    m_proxy = 0;
    m_adaptor.reset(new ColorMapSceneAdaptor);

    m_block_selection = false;
}

//! Main method to update scene on various changes in the model.

void MaskGraphicsScene::updateScene()
{
    if (!m_maskModel)
        return;

    updateProxyWidget();
    updateViews(m_maskContainerIndex,
                addViewForItem(m_maskModel->itemForIndex(m_maskContainerIndex)));
    setZValues();
}

//! Propagates selection from model to scene.

void MaskGraphicsScene::onSessionSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    if (m_block_selection)
        return;

    m_block_selection = true;

    for (auto it = m_ItemToView.begin(); it != m_ItemToView.end(); ++it) {
        QModelIndex index = m_maskModel->indexOfItem(it.key());
        if (index.isValid())
            it.value()->setSelected(m_selectionModel->isSelected(index));
    }
    m_block_selection = false;
}

//! Propagates selection from scene to model.

void MaskGraphicsScene::onSceneSelectionChanged()
{
    if (m_block_selection)
        return;

    m_block_selection = true;

    m_selectionModel->clearSelection();

    for (QGraphicsItem* graphicsItem : selectedItems()) {
        if (IShape2DView* view = dynamic_cast<IShape2DView*>(graphicsItem)) {
            QModelIndex itemIndex = m_maskModel->indexOfItem(view->parameterizedItem());
            ASSERT(itemIndex.isValid());
            if (!m_selectionModel->isSelected(itemIndex))
                m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
        }
    }
    m_block_selection = false;
}

void MaskGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() & Qt::RightButton) {
        if (isDrawingInProgress()) {
            cancelCurrentDrawing();
        } else {
            makeViewAtMousePosSelected(event);
        }
        return;
    }
    if (isValidForPolygonDrawing(event)) {
        processPolygonItem(event);
        return;
    }
    if (isValidForLineDrawing(event)) {
        processLineItem(event);
        return;
    }
    if (isValidForMaskAllDrawing(event)) {
        processMaskAllItem(event);
        return;
    }
    if (isValidForRectangleShapeDrawing(event)) {
        processRectangleShapeItem(event);
        return;
    }
    QGraphicsScene::mousePressEvent(event);
}

void MaskGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (isDrawingInProgress() && m_context.isRectangleShapeMode()) {
        processRectangleShapeItem(event);
        return;
    }
    QGraphicsScene::mouseMoveEvent(event);

    if ((isDrawingInProgress() && m_context.isPolygonMode()) || m_context.isLineMode()) {
        m_currentMousePosition = event->scenePos();
        invalidate();
    }
}

//! Finalizes item drawing or pass events to other items.

void MaskGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (isDrawingInProgress()) {
        if (m_context.isRectangleShapeMode()) {
            clearSelection();
            if (m_currentItem) {
                // drawing ended up with item drawn, let's make it selected
                if (IShape2DView* view = m_ItemToView[m_currentItem]) {
                    view->setSelected(true);
                }
            } else {
                // drawing ended without item to be draw (too short mouse move)
                // making item beneath of mouse release position to be selected
                makeViewAtMousePosSelected(event);
            }
            setDrawingInProgress(false);
        }
    } else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

//! Draws dashed line to the current mouse position in the case of ungoing
//! line or polygon drawing.

void MaskGraphicsScene::drawForeground(QPainter* painter, const QRectF&)
{
    //    if(!isDrawingInProgress())
    //        return;

    if (m_currentMousePosition == QPointF())
        return;

    if (PolygonView* polygon = currentPolygon()) {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawLine(QLineF(polygon->lastAddedPoint(), m_currentMousePosition));
    } else {
        if (m_context.isLineMode()) {
            const QRectF& plot_scene_rectangle = m_adaptor->viewportRectangle();
            if (!plot_scene_rectangle.contains(m_currentMousePosition))
                return;

            painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
            if (m_context.isVerticalLineMode()) {
                QPointF p1(m_currentMousePosition.x(), plot_scene_rectangle.bottom());
                QPointF p2(m_currentMousePosition.x(), plot_scene_rectangle.top());
                painter->drawLine(QLineF(p1, p2));
            }
            if (m_context.isHorizontalLineMode()) {
                QPointF p1(plot_scene_rectangle.left(), m_currentMousePosition.y());
                QPointF p2(plot_scene_rectangle.right(), m_currentMousePosition.y());
                painter->drawLine(QLineF(p1, p2));
            }
        }
    }
}

//! Creates item context menu if there is IMaskView beneath the mouse right click.

void MaskGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    if (isDrawingInProgress())
        return;

    if (dynamic_cast<IShape2DView*>(itemAt(event->scenePos(), QTransform())))
        emit itemContextMenuRequest(event->screenPos());
}

//! Updates proxy widget for intensity data item.

void MaskGraphicsScene::updateProxyWidget()
{
    ASSERT(m_intensityItem);
    if (!m_proxy) {
        m_proxy = new MaskGraphicsProxy;
        m_proxy->setIntensityItem(m_intensityItem);
        m_proxy->setSceneAdaptor(m_adaptor.data());
        addItem(m_proxy);
    }
}

//! Recutsively runs through the model and creates corresponding views.

void MaskGraphicsScene::updateViews(const QModelIndex& parentIndex, IShape2DView* parentView)
{
    ASSERT(m_maskModel);
    IShape2DView* childView(0);
    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);
        if (SessionItem* item = m_maskModel->itemForIndex(itemIndex)) {
            if (item->modelType() == "GroupProperty" || item->modelType() == "Property")
                continue;

            childView = addViewForItem(item);
            if (childView) {
                if (parentView)
                    parentView->addView(childView, i_row);
            }
        }
        updateViews(itemIndex, childView);
    }
}

//! Creates a view for given item.

IShape2DView* MaskGraphicsScene::addViewForItem(SessionItem* item)
{
    ASSERT(item);
    IShape2DView* view = m_ItemToView[item];
    if (!view) {
        view = MaskViewFactory::createMaskView(item, m_adaptor.data());
        if (view) {
            m_ItemToView[item] = view;
            addItem(view);
            return view;
        }
    }
    return view;
}

//! Recursive delete of all views corresponding to given index.

void MaskGraphicsScene::deleteViews(const QModelIndex& parentIndex)
{
    for (int i_row = 0; i_row < m_maskModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, parentIndex);

        if (SessionItem* item = m_maskModel->itemForIndex(itemIndex))
            removeItemViewFromScene(item);

        deleteViews(itemIndex);
    }
    removeItemViewFromScene(m_maskModel->itemForIndex(parentIndex)); // deleting parent item
}

//! Removes single view from scene.

void MaskGraphicsScene::removeItemViewFromScene(SessionItem* item)
{
    for (auto it = m_ItemToView.begin(); it != m_ItemToView.end(); ++it) {
        if (it.key() == item) {
            IShape2DView* view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            delete view;
            break;
        }
    }
}

//! Returns true if left mouse bottom click was inside ColorMap viewport rectangle.

bool MaskGraphicsScene::isValidMouseClick(QGraphicsSceneMouseEvent* event)
{
    if (!m_adaptor)
        return false;
    if (!(event->buttons() & Qt::LeftButton))
        return false;
    if (!m_adaptor->viewportRectangle().contains(event->scenePos()))
        return false;
    return true;
}

//! Returns true if mouse click is valid for rectangular/elliptic/ROI shapes.

bool MaskGraphicsScene::isValidForRectangleShapeDrawing(QGraphicsSceneMouseEvent* event)
{
    if (isDrawingInProgress())
        return false;
    if (!isValidMouseClick(event))
        return false;
    if (!m_context.isRectangleShapeMode())
        return false;
    if (isAreaContains(event, MaskEditorHelper::SIZEHANDLE))
        return false;
    if (m_context.isROIMode()) {
        // only one ROI is allowed
        for (SessionItem* item : m_ItemToView.keys())
            if (item->modelType() == "RegionOfInterest")
                return false;
    }
    return true;
}

//! Returns true if mouse click is in context suitable for polygon drawing.

bool MaskGraphicsScene::isValidForPolygonDrawing(QGraphicsSceneMouseEvent* event)
{
    if (!isValidMouseClick(event))
        return false;
    if (!m_context.isPolygonMode())
        return false;
    if (!isDrawingInProgress()) {
        if (isAreaContains(event, MaskEditorHelper::POLYGONPOINT))
            return false;
    }
    return true;
}

//! Returns true if mouse click is in context suitable for line drawing.

bool MaskGraphicsScene::isValidForLineDrawing(QGraphicsSceneMouseEvent* event)
{
    if (!isValidMouseClick(event))
        return false;
    if (isDrawingInProgress())
        return false;
    if (!m_context.isLineMode())
        return false;
    if (QGraphicsItem* graphicsItem = itemAt(event->scenePos(), QTransform())) {
        if (graphicsItem->type() == MaskEditorHelper::VERTICALLINE
            || graphicsItem->type() == MaskEditorHelper::HORIZONTALLINE)
            return false;
    }
    return true;
}

//! Returns true if MaskAllItem can be drawn. Only one item of such type is allowed.

bool MaskGraphicsScene::isValidForMaskAllDrawing(QGraphicsSceneMouseEvent* event)
{
    if (!isValidMouseClick(event))
        return false;
    if (isDrawingInProgress())
        return false;
    if (!m_context.isMaskAllMode())
        return false;
    for (SessionItem* item : m_ItemToView.keys())
        if (item->modelType() == "MaskAllMask")
            return false;
    return true;
}

//! Return true if area beneath the mouse contains views of given type.

bool MaskGraphicsScene::isAreaContains(QGraphicsSceneMouseEvent* event,
                                       MaskEditorHelper::EViewTypes viewType)
{
    for (QGraphicsItem* graphicsItem : this->items(event->scenePos()))
        if (graphicsItem->type() == viewType)
            return true;
    return false;
}

bool MaskGraphicsScene::isDrawingInProgress() const
{
    return m_context.isDrawingInProgress();
}

void MaskGraphicsScene::setDrawingInProgress(bool value)
{
    m_context.setDrawingInProgress(value);
    if (value == false)
        m_currentItem = 0;
}

//! Sets the state of all views in pan&zoom mode.
//! In pan&zoom mode, the selection is removed, all items can't receive mouse clicks, and all
//! events are propagated down to ColorMap plot.

void MaskGraphicsScene::setInPanAndZoomMode(bool value)
{
    if (value)
        m_selectionModel->clearSelection();

    Qt::MouseButtons acceptedButton = (value ? Qt::NoButton : Qt::LeftButton);
    for (IShape2DView* view : m_ItemToView.values())
        view->setAcceptedMouseButtons(acceptedButton);

    m_proxy->setInZoomMode(value);
}

//! Change cursor to stress that hovered item is movable (when not in PanZoom mode)

void MaskGraphicsScene::updateCursors()
{
    for (auto it = m_ItemToView.begin(); it != m_ItemToView.end(); ++it) {
        if (it.key()->modelType() == "VerticalLineMask") {
            it.value()->setCursor(m_context.isInZoomMode() ? Qt::ArrowCursor : Qt::SizeHorCursor);
        } else if (it.key()->modelType() == "HorizontalLineMask") {
            it.value()->setCursor(m_context.isInZoomMode() ? Qt::ArrowCursor : Qt::SizeVerCursor);
        }
    }
}

void MaskGraphicsScene::makeViewAtMousePosSelected(QGraphicsSceneMouseEvent* event)
{
    if (QGraphicsItem* graphicsItem = itemAt(event->scenePos(), QTransform()))
        graphicsItem->setSelected(true);
}

//! Processes RectangleItem and EllipseItem drawing
//! If the mouse move distance with left button down is larger than certain threshold,
//! new item will be created. Further, this function will update size and position
//! of current rectangle if mouse keep moving.

void MaskGraphicsScene::processRectangleShapeItem(QGraphicsSceneMouseEvent* event)
{
    if (!isDrawingInProgress())
        setDrawingInProgress(true);

    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);
    QPointF mouse_pos = event->scenePos();
    QLineF line(mouse_pos, click_pos);

    if (!m_currentItem && line.length() > min_distance_to_create_rect) {
        m_currentItem = m_maskModel->insertNewItem(m_context.activityToModelType(),
                                                   m_maskContainerIndex, m_context.activityToRow());
        if (!m_context.isROIMode())
            m_currentItem->setItemValue(MaskItem::P_MASK_VALUE, m_context.getMaskValue());
        setItemName(m_currentItem);
    }
    if (!m_currentItem)
        return;

    qreal xmin = std::min(click_pos.x(), mouse_pos.x());
    qreal xmax = std::max(click_pos.x(), mouse_pos.x());
    qreal ymin = std::min(click_pos.y(), mouse_pos.y());
    qreal ymax = std::max(click_pos.y(), mouse_pos.y());

    if (m_currentItem->modelType() == "RectangleMask"
        || m_currentItem->modelType() == "RegionOfInterest") {
        m_currentItem->setItemValue(RectangleItem::P_XLOW, m_adaptor->fromSceneX(xmin));
        m_currentItem->setItemValue(RectangleItem::P_YLOW, m_adaptor->fromSceneY(ymax));
        m_currentItem->setItemValue(RectangleItem::P_XUP, m_adaptor->fromSceneX(xmax));
        m_currentItem->setItemValue(RectangleItem::P_YUP, m_adaptor->fromSceneY(ymin));
    } else if (m_currentItem->modelType() == "EllipseMask") {
        m_currentItem->setItemValue(EllipseItem::P_XCENTER,
                                    m_adaptor->fromSceneX(xmin + (xmax - xmin) / 2.));
        m_currentItem->setItemValue(EllipseItem::P_YCENTER,
                                    m_adaptor->fromSceneY(ymin + (ymax - ymin) / 2.));
        m_currentItem->setItemValue(EllipseItem::P_XRADIUS,
                                    (m_adaptor->fromSceneX(xmax) - m_adaptor->fromSceneX(xmin))
                                        / 2.);
        m_currentItem->setItemValue(EllipseItem::P_YRADIUS,
                                    (m_adaptor->fromSceneY(ymin) - m_adaptor->fromSceneY(ymax))
                                        / 2.);
    }
}

void MaskGraphicsScene::processPolygonItem(QGraphicsSceneMouseEvent* event)
{
    ASSERT(m_context.isPolygonMode());

    if (!m_currentItem) {
        setDrawingInProgress(true);
        m_currentItem = m_maskModel->insertNewItem("PolygonMask", m_maskContainerIndex, 0);
        m_currentItem->setItemValue(MaskItem::P_MASK_VALUE, m_context.getMaskValue());
        m_selectionModel->clearSelection();
        m_selectionModel->select(m_maskModel->indexOfItem(m_currentItem),
                                 QItemSelectionModel::Select);
        setItemName(m_currentItem);
    }
    ASSERT(m_currentItem->modelType() == "PolygonMask");

    if (PolygonView* polygon = currentPolygon()) {
        if (polygon->closePolygonIfNecessary()) {
            setDrawingInProgress(false);
            m_currentMousePosition = {};
            return;
        }
    }
    SessionItem* point =
        m_maskModel->insertNewItem("PolygonPoint", m_maskModel->indexOfItem(m_currentItem));
    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);

    point->setItemValue(PolygonPointItem::P_POSX, m_adaptor->fromSceneX(click_pos.x()));
    point->setItemValue(PolygonPointItem::P_POSY, m_adaptor->fromSceneY(click_pos.y()));
}

void MaskGraphicsScene::processLineItem(QGraphicsSceneMouseEvent* event)
{
    setDrawingInProgress(true);
    QPointF click_pos = event->buttonDownScenePos(Qt::LeftButton);

    if (m_context.isVerticalLineMode())
        processVerticalLineItem(click_pos);

    if (m_context.isHorizontalLineMode())
        processHorizontalLineItem(click_pos);

    m_selectionModel->clearSelection();
    m_selectionModel->select(m_maskModel->indexOfItem(m_currentItem), QItemSelectionModel::Select);
    setItemName(m_currentItem);
    m_currentItem->setItemValue(MaskItem::P_MASK_VALUE, m_context.getMaskValue());

    setDrawingInProgress(false);
}

void MaskGraphicsScene::processVerticalLineItem(const QPointF& pos)
{
    m_currentItem = m_maskModel->insertNewItem("VerticalLineMask", m_maskContainerIndex, 0);
    m_currentItem->setItemValue(VerticalLineItem::P_POSX, m_adaptor->fromSceneX(pos.x()));
}

void MaskGraphicsScene::processHorizontalLineItem(const QPointF& pos)
{
    m_currentItem = m_maskModel->insertNewItem("HorizontalLineMask", m_maskContainerIndex, 0);
    m_currentItem->setItemValue(HorizontalLineItem::P_POSY, m_adaptor->fromSceneY(pos.y()));
}

void MaskGraphicsScene::processMaskAllItem(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
    setDrawingInProgress(true);
    m_currentItem = m_maskModel->insertNewItem("MaskAllMask", m_maskContainerIndex);
    m_selectionModel->clearSelection();
    setDrawingInProgress(false);
}

//! Update Z-values of all IMaskView to reflect stacking order in SessionModel.
//! Item with irow=0 is the top most on graphics scene (and so is having largest z-values).

void MaskGraphicsScene::setZValues()
{
    ASSERT(m_maskContainerIndex.isValid());
    for (int i = 0; i < m_maskModel->rowCount(m_maskContainerIndex); i++) {
        QModelIndex itemIndex = m_maskModel->index(i, 0, m_maskContainerIndex);
        SessionItem* item = m_maskModel->itemForIndex(itemIndex);
        if (IShape2DView* view = m_ItemToView[item])
            view->setZValue(m_maskModel->rowCount(m_maskContainerIndex) - itemIndex.row() + 1);
    }
}

//! Returns polygon which is currently under the drawing.

PolygonView* MaskGraphicsScene::currentPolygon() const
{
    PolygonView* result(0);
    if (isDrawingInProgress() && m_context.isPolygonMode()) {
        if (m_currentItem)
            result = dynamic_cast<PolygonView*>(m_ItemToView[m_currentItem]);
    }
    return result;
}

//! Sets item name depending on alreay existent items.
//! If there is already "Rectangle1", the new name will be "Rectangle2"

void MaskGraphicsScene::setItemName(SessionItem* itemToChange)
{
    if (itemToChange->modelType() == "RegionOfInterest")
        return;

    int glob_index(0);
    for (int i_row = 0; i_row < m_maskModel->rowCount(m_maskContainerIndex); ++i_row) {
        QModelIndex itemIndex = m_maskModel->index(i_row, 0, m_maskContainerIndex);
        if (SessionItem* currentItem = m_maskModel->itemForIndex(itemIndex)) {
            if (currentItem->modelType() == itemToChange->modelType()) {
                QString itemName = currentItem->itemName();
                if (itemName.startsWith(itemToChange->itemName())) {
                    int item_index = itemName.remove(0, itemToChange->itemName().size()).toInt();
                    if (item_index > glob_index)
                        glob_index = item_index;
                }
            }
        }
    }
    itemToChange->setItemName(itemToChange->itemName() + QString::number(++glob_index));
}
