// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceScene.cpp
//! @brief     Implements class RealSpaceScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AppSvc.h"
#include "projectmanager.h"
#include "RealSpaceCanvas.h"
#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "RealSpaceView.h"
#include "SampleModel.h"
#include "SessionItemUtils.h"
#include "WarningSign.h"
#include "FilterPropertyProxy.h"
#include <QFileDialog>
#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>

RealSpaceCanvas::RealSpaceCanvas(QWidget* parent)
    : QWidget(parent), m_sampleModel(nullptr), m_view(new RealSpaceView), m_selectionModel(nullptr),
      m_view_locked(false), m_sceneGeometry(new SceneGeometry), m_warningSign(new WarningSign(this))
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_view);
    setLayout(layout);
}

RealSpaceCanvas::~RealSpaceCanvas() = default;

void RealSpaceCanvas::setModel(SampleModel* sampleModel, QItemSelectionModel* selectionModel)
{
    if (sampleModel != m_sampleModel) {

        if (m_sampleModel)
            setConnected(m_sampleModel, false);

        m_sampleModel = sampleModel;

        if (m_sampleModel)
            setConnected(m_sampleModel, true);
    }

    if (selectionModel != m_selectionModel) {
        if (m_selectionModel)
            disconnect(m_selectionModel, &QItemSelectionModel::selectionChanged,
                       this, &RealSpaceCanvas::onSelectionChanged);

        m_selectionModel = selectionModel;

        if (m_selectionModel)
            connect(m_selectionModel, &QItemSelectionModel::selectionChanged,
                    this, &RealSpaceCanvas::onSelectionChanged);
    }

    updateToSelection();
}

void RealSpaceCanvas::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    updateToSelection();
}

void RealSpaceCanvas::updateToSelection()
{
    if (!m_selectionModel)
        return;

    if (!m_view_locked) {
        QModelIndexList indices = m_selectionModel->selection().indexes();

        if (indices.size())
            m_currentSelection = FilterPropertyProxy::toSourceIndex(indices.back());
        else
            m_currentSelection = QModelIndex();
        // if no object is selected then display nothing on canvas

        updateScene();
    }
}

void RealSpaceCanvas::onDefaultViewAction()
{
    defaultView();
}

void RealSpaceCanvas::onSideViewAction()
{
    sideView();
}

void RealSpaceCanvas::onTopViewAction()
{
    topView();
}

void RealSpaceCanvas::onLockViewAction(bool view_locked)
{
    if (m_view_locked != view_locked) {
        m_view_locked = view_locked;
        updateToSelection();
    }
}

void RealSpaceCanvas::onChangeLayerSizeAction(double layerSizeChangeScale)
{
    // when no object is selected --> take no action
    if (m_currentSelection == QModelIndex())
        return;

    m_sceneGeometry->set_layer_size(m_sceneGeometry->layer_size() * layerSizeChangeScale);
    updateScene();
}

void RealSpaceCanvas::onSavePictureAction()
{
    QPixmap pixmap(this->size());
    render(&pixmap, QPoint(), childrenRegion());
    savePicture(pixmap);
}

void RealSpaceCanvas::savePicture(const QPixmap &pixmap)
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    QString defaultExtension = ".png";
    QString selectedFilter("*"+defaultExtension);
    QString defaultName = dirname + QString("/untitled");
    QString fileName =QFileDialog::getSaveFileName(nullptr, "Save 3D real space view", defaultName, selectedFilter);
    QString nameToSave = fileName.endsWith(defaultExtension) ? fileName : fileName + defaultExtension;

    if(!nameToSave.isEmpty()) {
        try {
            pixmap.save(nameToSave);
        } catch(const std::exception &ex) {
            QString message = "Attempt to save file with the name '";
            message.append(nameToSave);
            message.append("' has failed with following error message\n\n");
            message.append(QString::fromStdString(ex.what()));
            QMessageBox::warning(nullptr, "Houston, we have a problem.", message);
        }
    }
}


void RealSpaceCanvas::onDataChanged(const QModelIndex& index)
{
    auto item = m_sampleModel->itemForIndex(index);
    if (!item)
        return;

    if (!SessionItemUtils::IsPositionRelated(*item))
        updateScene();
}

void RealSpaceCanvas::updateScene()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    m_realSpaceModel.reset(new RealSpaceModel);
    auto item = m_sampleModel->itemForIndex(m_currentSelection);
    if (!item)
        return;

    RealSpaceBuilder builder3D;

    try {
        m_warningSign->clear();
        // if the view is locked, keep the current orientation of the camera
        if (m_view_locked)
            builder3D.populate(m_realSpaceModel.get(), *item, *m_sceneGeometry,
                               m_view->getCamera().getPos());
        // otherwise use default orientation of camera
        else {
            builder3D.populate(m_realSpaceModel.get(), *item, *m_sceneGeometry);
            defaultView(); // Enforces default view and also sets the zoomLevel to default i.e. 0
        }
    } catch (const std::exception& ex) {
        m_warningSign->setWarningMessage(ex.what());
    } catch (...) {
        // ignore other exceptions thrown
    }
    m_view->setModel(m_realSpaceModel.get());

    QApplication::restoreOverrideCursor();
}

void RealSpaceCanvas::resetScene()
{
    m_realSpaceModel.reset();
    m_view->setModel(nullptr);
    m_currentSelection = QModelIndex();
}

void RealSpaceCanvas::defaultView()
{
    m_view->defaultView();
}

void RealSpaceCanvas::sideView()
{
    m_view->sideView();
}

void RealSpaceCanvas::topView()
{
    m_view->topView();
}

void RealSpaceCanvas::setConnected(SampleModel* model, bool makeConnected)
{
    if (!model)
        return;

    if (makeConnected) {
        connect(model, &SampleModel::rowsInserted, this, &RealSpaceCanvas::updateScene,
                Qt::UniqueConnection);
        connect(model, &SampleModel::rowsRemoved, this, &RealSpaceCanvas::updateScene,
                Qt::UniqueConnection);
        connect(model, &SampleModel::dataChanged, this, &RealSpaceCanvas::onDataChanged,
                Qt::UniqueConnection);
        connect(model, &SampleModel::modelReset, this, &RealSpaceCanvas::resetScene,
                Qt::UniqueConnection);
        connect(model, &SampleModel::modelAboutToBeReset, this,
                [&]() { m_currentSelection = QModelIndex(); }, Qt::UniqueConnection);

    } else {
        disconnect(model, &SampleModel::rowsInserted, this, &RealSpaceCanvas::updateScene);
        disconnect(model, &SampleModel::rowsRemoved, this, &RealSpaceCanvas::updateScene);
        disconnect(model, &SampleModel::dataChanged, this, &RealSpaceCanvas::onDataChanged);
        disconnect(model, &SampleModel::modelReset, this, &RealSpaceCanvas::resetScene);
    }
}
