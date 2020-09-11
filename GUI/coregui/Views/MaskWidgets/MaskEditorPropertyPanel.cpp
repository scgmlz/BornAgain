// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorPropertyPanel.cpp
//! @brief     Implements class MaskEditorPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/MaskEditorPropertyPanel.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/AccordionWidget/AccordionWidget.h"
#include "GUI/coregui/Views/AccordionWidget/ContentPane.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentEditor.h"
#include <QListView>
#include <QVBoxLayout>

//! Widget to cheat Accordion to resize correctly.

class EnvelopWidget : public QWidget
{
public:
    EnvelopWidget(QWidget* content)
    {
        QVBoxLayout* mainLayout = new QVBoxLayout;
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);
        setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        mainLayout->addWidget(content);
        setLayout(mainLayout);
    }

    QSize sizeHint() const { return QSize(128, 500); }
};

MaskEditorPropertyPanel::MaskEditorPropertyPanel(QWidget* parent)
    : QWidget(parent), m_listView(new QListView), m_maskPropertyEditor(new ComponentEditor),
      m_plotPropertyEditor(new ComponentEditor(ComponentEditor::MiniTree)),
      m_accordion(new AccordionWidget), m_maskModel(nullptr), m_intensityDataItem(nullptr)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setObjectName(QLatin1String("MaskEditorToolPanel"));

    m_listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_listView, &QListView::customContextMenuRequested, this,
            &MaskEditorPropertyPanel::onCustomContextMenuRequested);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    setup_PlotProperties(m_accordion);
    setup_MaskStack(m_accordion);
    setup_MaskProperties(m_accordion);
    m_accordion->getContentPane(0)->headerClicked();

    mainLayout->addWidget(m_accordion);

    setLayout(mainLayout);
}

QSize MaskEditorPropertyPanel::sizeHint() const
{
    return QSize(128, 128);
}

QSize MaskEditorPropertyPanel::minimumSizeHint() const
{
    return QSize(128, 128);
}

void MaskEditorPropertyPanel::setMaskContext(SessionModel* model,
                                             const QModelIndex& maskContainerIndex,
                                             IntensityDataItem* intensityItem)
{
    m_maskModel = model;
    m_rootIndex = maskContainerIndex;
    m_intensityDataItem = intensityItem;

    m_listView->setModel(m_maskModel);
    m_listView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    m_listView->setRootIndex(m_rootIndex);

    connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &MaskEditorPropertyPanel::onSelectionChanged, Qt::UniqueConnection);

    m_plotPropertyEditor->setItem(m_intensityDataItem);
}

void MaskEditorPropertyPanel::resetContext()
{
    m_maskModel = nullptr;
    m_rootIndex = {};
    m_intensityDataItem = nullptr;
    m_listView->setModel(nullptr);
    m_maskPropertyEditor->setItem(nullptr);
    m_plotPropertyEditor->setItem(nullptr);
}

QItemSelectionModel* MaskEditorPropertyPanel::selectionModel()
{
    ASSERT(m_listView);
    return m_listView->selectionModel();
}

//! Show/Hide panel. When panel is hidden, all property editors are disabled.
void MaskEditorPropertyPanel::setPanelHidden(bool value)
{
    this->setHidden(value);

    if (!m_rootIndex.isValid())
        return;

    if (value) {
        m_maskPropertyEditor->setItem(nullptr);
        m_plotPropertyEditor->setItem(nullptr);
    } else {
        QModelIndexList indexes = selectionModel()->selectedIndexes();
        if (indexes.size())
            m_maskPropertyEditor->setItem(m_maskModel->itemForIndex(indexes.front()));

        m_plotPropertyEditor->setItem(m_intensityDataItem);
    }
}

void MaskEditorPropertyPanel::onSelectionChanged(const QItemSelection& selected,
                                                 const QItemSelection&)
{
    if (selected.size())
        m_maskPropertyEditor->setItem(m_maskModel->itemForIndex(selected.indexes().front()));
    else
        m_maskPropertyEditor->setItem(nullptr);
}

void MaskEditorPropertyPanel::onCustomContextMenuRequested(const QPoint& point)
{
    emit itemContextMenuRequest(m_listView->mapToGlobal(point));
}

void MaskEditorPropertyPanel::setup_PlotProperties(AccordionWidget* accordion)
{
    ContentPane* cp = accordion->getContentPane(accordion->addContentPane("Plot properties"));
    cp->setMaximumHeight(600);
    cp->setHeaderTooltip("Plot properties editor");
    cp->setContainerFrameStyle(QFrame::Plain);
    QFrame* contentFrame = cp->getContentFrame();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    m_plotPropertyEditor->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(new EnvelopWidget(m_plotPropertyEditor));
    contentFrame->setLayout(layout);
}

void MaskEditorPropertyPanel::setup_MaskStack(AccordionWidget* accordion)
{
    ContentPane* cp = accordion->getContentPane(accordion->addContentPane("Mask stack"));
    cp->setMaximumHeight(600);
    cp->setHeaderTooltip("List of created masks representing mask stacking order.");
    cp->setContainerFrameStyle(QFrame::Plain);
    QFrame* contentFrame = cp->getContentFrame();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_listView);
    layout->addWidget(new EnvelopWidget(m_listView));
    contentFrame->setLayout(layout);
}

void MaskEditorPropertyPanel::setup_MaskProperties(AccordionWidget* accordion)
{
    ContentPane* cp = accordion->getContentPane(accordion->addContentPane("Mask properties"));
    cp->setMaximumHeight(600);
    cp->setHeaderTooltip("Property editor for currently selected mask.");
    cp->setContainerFrameStyle(QFrame::Plain);
    QFrame* contentFrame = cp->getContentFrame();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new EnvelopWidget(m_maskPropertyEditor));
    contentFrame->setLayout(layout);
}
