/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Designer of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "GUI/coregui/Views/widgetbox/widgetboxtreewidget.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/widgetbox/widgetboxcategorylistview.h"

// shared
#include "GUI/coregui/Views/widgetbox/qdesigner_utils_p.h"
#include "GUI/coregui/Views/widgetbox/sheet_delegate_p.h"
#include "GUI/coregui/Views/widgetbox/ui4_p.h"

// sdk
#include <QtDesigner/QDesignerDnDItemInterface>
#include <QtDesigner/QDesignerFormEditorInterface>

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
#include <QtDesigner/QDesignerCustomWidgetInterface>
#else
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#endif

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QContextMenuEvent>
#include <QHeaderView>
#include <QMenu>
#include <QTreeWidgetItem>

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTimer>

#include <iostream>

static const char* widgetBoxRootElementC = "widgetbox";
static const char* widgetElementC = "widget";
static const char* uiElementC = "ui";
static const char* categoryElementC = "category";
static const char* categoryEntryElementC = "categoryentry";
static const char* nameAttributeC = "name";
static const char* typeAttributeC = "type";
static const char* iconAttributeC = "icon";
static const char* defaultTypeValueC = "default";
static const char* customValueC = "custom";
static const char* iconPrefixC = "__qt_icon__";
static const char* scratchPadValueC = "scratchpad";
static const char* qtLogoC = "qtlogo.png";
static const char* invisibleNameC = "[invisible]";

QIcon createIconSet(const QString& name)
{
    return QIcon(QString::fromUtf8(":/widgetbox/") + name);
}

enum ETopLevelRole { NORMAL_ITEM, SCRATCHPAD_ITEM, CUSTOM_ITEM };

QT_BEGIN_NAMESPACE

static void setTopLevelRole(ETopLevelRole tlr, QTreeWidgetItem* item)
{
    item->setData(0, Qt::UserRole, QVariant(tlr));
}

static ETopLevelRole topLevelRole(const QTreeWidgetItem* item)
{
    return static_cast<ETopLevelRole>(item->data(0, Qt::UserRole).toInt());
}

namespace qdesigner_internal
{

WidgetBoxTreeWidget::WidgetBoxTreeWidget(SampleDesignerInterface* core, QWidget* parent)
    : QTreeWidget(parent), m_core(core), m_iconMode(false), m_scratchPadDeleteTimer(nullptr)
{
    setFocusPolicy(Qt::NoFocus);
    setIndentation(0);
    setRootIsDecorated(false);
    setColumnCount(1);
    header()->hide();
#if QT_VERSION >= 0x050000
    header()->setSectionResizeMode(QHeaderView::Stretch);
#endif
    setTextElideMode(Qt::ElideMiddle);
    setVerticalScrollMode(ScrollPerPixel);

    setItemDelegate(new SheetDelegate(this, this));

    connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this,
            SLOT(handleMousePress(QTreeWidgetItem*)));
}

QIcon WidgetBoxTreeWidget::iconForWidget(QString iconName) const
{
    if (iconName.isEmpty())
        iconName = QLatin1String(qtLogoC);

    if (iconName.startsWith(QLatin1String(iconPrefixC))) {
        const IconCache::const_iterator it = m_pluginIcons.constFind(iconName);
        if (it != m_pluginIcons.constEnd())
            return it.value();
    }
    return createIconSet(iconName);
}

WidgetBoxCategoryListView* WidgetBoxTreeWidget::categoryViewAt(int idx) const
{
    WidgetBoxCategoryListView* rc = nullptr;
    if (QTreeWidgetItem* cat_item = topLevelItem(idx))
        if (QTreeWidgetItem* embedItem = cat_item->child(0))
            rc = qobject_cast<WidgetBoxCategoryListView*>(itemWidget(embedItem, 0));
    ASSERT(rc);
    return rc;
}

void WidgetBoxTreeWidget::saveExpandedState() const
{
    return;
}

void WidgetBoxTreeWidget::restoreExpandedState()
{
    std::cout << "WidgetBoxTreeWidget::restoreExpandedState() -> XXX Not implemented." << std::endl;
    return;
}

WidgetBoxTreeWidget::~WidgetBoxTreeWidget()
{
    saveExpandedState();
}

void WidgetBoxTreeWidget::setFileName(const QString& file_name)
{
    m_file_name = file_name;
}

QString WidgetBoxTreeWidget::fileName() const
{
    return m_file_name;
}

bool WidgetBoxTreeWidget::save()
{
    if (fileName().isEmpty())
        return false;

    QFile file(fileName());
    if (!file.open(QIODevice::WriteOnly))
        return false;

    CategoryList cat_list;
    const int count = categoryCount();
    for (int i = 0; i < count; ++i)
        cat_list.append(category(i));

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.setAutoFormattingIndent(1);
    writer.writeStartDocument();
    writeCategories(writer, cat_list);
    writer.writeEndDocument();

    return true;
}

void WidgetBoxTreeWidget::slotSave()
{
    save();
}

void WidgetBoxTreeWidget::handleMousePress(QTreeWidgetItem* item)
{
    if (item == nullptr)
        return;

    if (QApplication::mouseButtons() != Qt::LeftButton)
        return;

    if (item->parent() == nullptr) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        item->setExpanded(!item->isExpanded());
#else
        setItemExpanded(item, !isItemExpanded(item));
#endif
        return;
    }
}

int WidgetBoxTreeWidget::ensureScratchpad()
{
    const int existingIndex = indexOfScratchpad();
    if (existingIndex != -1)
        return existingIndex;

    QTreeWidgetItem* scratch_item = new QTreeWidgetItem(this);
    scratch_item->setText(0, "Scratchpad");
    setTopLevelRole(SCRATCHPAD_ITEM, scratch_item);
    addCategoryView(scratch_item, false); // Scratchpad in list mode.
    return categoryCount() - 1;
}

WidgetBoxCategoryListView* WidgetBoxTreeWidget::addCategoryView(QTreeWidgetItem* parent,
                                                                bool iconMode)
{
    QTreeWidgetItem* embed_item = new QTreeWidgetItem(parent);
    embed_item->setFlags(Qt::ItemIsEnabled);
    WidgetBoxCategoryListView* categoryView = new WidgetBoxCategoryListView(m_core, this);
    categoryView->setViewMode(iconMode ? QListView::IconMode : QListView::ListMode);
    connect(categoryView, SIGNAL(scratchPadChanged()), this, SLOT(slotSave()));
    connect(categoryView, SIGNAL(pressed(QString, QString, QPoint)), this,
            SIGNAL(pressed(QString, QString, QPoint)));
    connect(categoryView, SIGNAL(itemRemoved()), this, SLOT(slotScratchPadItemDeleted()));
    connect(categoryView, SIGNAL(lastItemRemoved()), this, SLOT(slotLastScratchPadItemDeleted()));
    setItemWidget(embed_item, 0, categoryView);
    return categoryView;
}

int WidgetBoxTreeWidget::indexOfScratchpad() const
{
    if (const int numTopLevels = topLevelItemCount()) {
        for (int i = numTopLevels - 1; i >= 0; --i) {
            if (topLevelRole(topLevelItem(i)) == SCRATCHPAD_ITEM)
                return i;
        }
    }
    return -1;
}

int WidgetBoxTreeWidget::indexOfCategory(const QString& name) const
{
    const int topLevelCount = topLevelItemCount();
    for (int i = 0; i < topLevelCount; ++i) {
        if (topLevelItem(i)->text(0) == name)
            return i;
    }
    return -1;
}

bool WidgetBoxTreeWidget::load(QDesignerWidgetBox::LoadMode loadMode)
{
    switch (loadMode) {
    case QDesignerWidgetBox::LoadReplace:
        clear();
        break;
    case QDesignerWidgetBox::LoadCustomWidgetsOnly:
        addCustomCategories(true);
        updateGeometries();
        return true;
    default:
        break;
    }
    const QString name = fileName();

    QFile f(name);
    if (!f.open(QIODevice::ReadOnly)) // Might not exist at first startup
        return false;

    const QString contents = QString::fromUtf8(f.readAll());
    return loadContents(contents);
}

bool WidgetBoxTreeWidget::loadContents(const QString& contents)
{
    QString errorMessage;
    CategoryList cat_list;
    if (!readCategories(m_file_name, contents, &cat_list, &errorMessage)) {
        qdesigner_internal::designerWarning(errorMessage);
        return false;
    }
    for (const Category& cat : cat_list)
        addCategory(cat);

    return true;
}

void WidgetBoxTreeWidget::addCustomCategories(bool replace)
{
    if (replace) {
        // clear out all existing custom widgets
        if (const int numTopLevels = topLevelItemCount()) {
            for (int t = 0; t < numTopLevels; ++t)
                categoryViewAt(t)->removeCustomWidgets();
        }
    }
    // re-add
    const CategoryList customList = loadCustomCategoryList();
    const CategoryList::const_iterator cend = customList.constEnd();
    for (CategoryList::const_iterator it = customList.constBegin(); it != cend; ++it)
        addCategory(*it);
}

static inline QString msgXmlError(const QString& fileName, const QXmlStreamReader& r)
{
    return QString("An error has been encountered at line %1 of %2: %3")
        .arg(r.lineNumber())
        .arg(fileName, r.errorString());
}

bool WidgetBoxTreeWidget::readCategories(const QString& fileName, const QString& contents,
                                         CategoryList* cats, QString* errorMessage)
{
    // Read widget box XML:
    //
    //<widgetbox version="4.5">
    // <category name="Layouts">
    //  <categoryentry name="Vertical Layout" icon="win/editvlayout.png" type="default">
    //   <widget class="QListWidget" ...>
    // ...

    QXmlStreamReader reader(contents);

    // Entries of category with name="invisible" should be ignored
    bool ignoreEntries = false;

    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement: {
            const QStringRef tag = reader.name();
            if (tag == QLatin1String(widgetBoxRootElementC)) {
                //<widgetbox version="4.5">
                continue;
            }
            if (tag == QLatin1String(categoryElementC)) {
                // <category name="Layouts">
                const QXmlStreamAttributes attributes = reader.attributes();
                const QString categoryName =
                    attributes.value(QLatin1String(nameAttributeC)).toString();
                if (categoryName == QLatin1String(invisibleNameC)) {
                    ignoreEntries = true;
                } else {
                    Category category(categoryName);
                    if (attributes.value(QLatin1String(typeAttributeC))
                        == QLatin1String(scratchPadValueC))
                        category.setType(Category::Scratchpad);
                    cats->push_back(category);
                }
                continue;
            }
            if (tag == QLatin1String(categoryEntryElementC)) {
                //  <categoryentry name="Vertical Layout" icon="win/editvlayout.png" type="default">
                if (!ignoreEntries) {
                    QXmlStreamAttributes attr = reader.attributes();
                    const QString widgetName = attr.value(QLatin1String(nameAttributeC)).toString();
                    const QString widgetIcon = attr.value(QLatin1String(iconAttributeC)).toString();
                    const WidgetBoxTreeWidget::Widget::Type widgetType =
                        attr.value(QLatin1String(typeAttributeC)).toString()
                                == QLatin1String(customValueC)
                            ? WidgetBoxTreeWidget::Widget::Custom
                            : WidgetBoxTreeWidget::Widget::Default;

                    Widget w;
                    w.setName(widgetName);
                    w.setIconName(widgetIcon);
                    w.setType(widgetType);
                    if (!readWidget(&w, contents, reader))
                        continue;

                    cats->back().addWidget(w);
                } // ignoreEntries
                continue;
            }
            break;
        }
        case QXmlStreamReader::EndElement: {
            const QStringRef tag = reader.name();
            if (tag == QLatin1String(widgetBoxRootElementC)) {
                continue;
            }
            if (tag == QLatin1String(categoryElementC)) {
                ignoreEntries = false;
                continue;
            }
            if (tag == QLatin1String(categoryEntryElementC)) {
                continue;
            }
            break;
        }
        default:
            break;
        }
    }

    if (reader.hasError()) {
        *errorMessage = msgXmlError(fileName, reader);
        return false;
    }

    return true;
}

/*!
 * Read out a widget within a category. This can either be
 * enclosed in a <ui> element or a (legacy) <widget> element which may
 * contain nested <widget> elements.
 *
 * Examples:
 *
 * <ui language="c++">
 *  <widget class="MultiPageWidget" name="multipagewidget"> ... </widget>
 *  <customwidgets>...</customwidgets>
 * <ui>
 *
 * or
 *
 * <widget>
 *   <widget> ... </widget>
 *   ...
 * <widget>
 *
 * Returns true on success, false if end was reached or an error has been encountered
 * in which case the reader has its error flag set. If successful, the current item
 * of the reader will be the closing element (</ui> or </widget>)
 */
bool WidgetBoxTreeWidget::readWidget(Widget* w, const QString& xml, QXmlStreamReader& r)
{
    qint64 startTagPosition = 0, endTagPosition = 0;

    int nesting = 0;
    bool endEncountered = false;
    bool parsedWidgetTag = false;
    QString outmostElement;
    while (!endEncountered) {
        const qint64 currentPosition = r.characterOffset();
        switch (r.readNext()) {
        case QXmlStreamReader::StartElement:
            if (nesting++ == 0) {
                // First element must be <ui> or (legacy) <widget>
                const QStringRef name = r.name();
                if (name == QLatin1String(uiElementC)) {
                    startTagPosition = currentPosition;
                } else {
                    if (name == QLatin1String(widgetElementC)) {
                        startTagPosition = currentPosition;
                        parsedWidgetTag = true;
                    } else {
                        r.raiseError(QString("Unexpected element <%1> encountered when "
                                             "parsing for <widget> or <ui>")
                                         .arg(name.toString()));
                        return false;
                    }
                }
            } else {
                // We are within <ui> looking for the first <widget> tag
                if (!parsedWidgetTag && r.name() == QLatin1String(widgetElementC)) {
                    parsedWidgetTag = true;
                }
            }
            break;
        case QXmlStreamReader::EndElement:
            // Reached end of widget?
            if (--nesting == 0) {
                endTagPosition = r.characterOffset();
                endEncountered = true;
            }
            break;
        case QXmlStreamReader::EndDocument:
            r.raiseError("Unexpected end of file encountered when parsing widgets.");
            return false;
        case QXmlStreamReader::Invalid:
            return false;
        default:
            break;
        }
    }
    if (!parsedWidgetTag) {
        r.raiseError("A widget element could not be found.");
        return false;
    }
    // Oddity: Startposition is 1 off
    QString widgetXml = xml.mid(startTagPosition, endTagPosition - startTagPosition);
    const QChar lessThan = QLatin1Char('<');
    if (!widgetXml.startsWith(lessThan))
        widgetXml.prepend(lessThan);
    w->setDomXml(widgetXml);
    return true;
}

void WidgetBoxTreeWidget::writeCategories(QXmlStreamWriter& writer,
                                          const CategoryList& cat_list) const
{
    const QString widgetbox = QLatin1String(widgetBoxRootElementC);
    const QString name = QLatin1String(nameAttributeC);
    const QString type = QLatin1String(typeAttributeC);
    const QString icon = QLatin1String(iconAttributeC);
    const QString defaultType = QLatin1String(defaultTypeValueC);
    const QString category = QLatin1String(categoryElementC);
    const QString categoryEntry = QLatin1String(categoryEntryElementC);
    const QString iconPrefix = QLatin1String(iconPrefixC);
    const QString widgetTag = QLatin1String(widgetElementC);

    //
    // <widgetbox>
    //   <category name="Layouts">
    //     <categoryEntry name="Vertical Layout" type="default" icon="win/editvlayout.png">
    //       <ui>
    //        ...
    //       </ui>
    //     </categoryEntry>
    //     ...
    //   </category>
    //   ...
    // </widgetbox>
    //

    writer.writeStartElement(widgetbox);

    for (const Category& cat : cat_list) {
        writer.writeStartElement(category);
        writer.writeAttribute(name, cat.name());
        if (cat.type() == Category::Scratchpad)
            writer.writeAttribute(type, QLatin1String(scratchPadValueC));

        const int widgetCount = cat.widgetCount();
        for (int i = 0; i < widgetCount; ++i) {
            const Widget wgt = cat.widget(i);
            if (wgt.type() == Widget::Custom)
                continue;

            writer.writeStartElement(categoryEntry);
            writer.writeAttribute(name, wgt.name());
            if (!wgt.iconName().startsWith(iconPrefix))
                writer.writeAttribute(icon, wgt.iconName());
            writer.writeAttribute(type, defaultType);

            const DomUI* domUI = QDesignerWidgetBox::xmlToUi(
                wgt.name(), WidgetBoxCategoryListView::widgetDomXml(wgt), false);
            if (domUI) {
                domUI->write(writer);
                delete domUI;
            }
            writer.writeEndElement(); // categoryEntry
        }
        writer.writeEndElement(); // categoryEntry
    }
    writer.writeEndElement(); // widgetBox
}

WidgetBoxTreeWidget::CategoryList WidgetBoxTreeWidget::loadCustomCategoryList() const
{
    CategoryList result;

    std::cout << "WidgetBoxTreeWidget::loadCustomCategoryList() -> XXX Not implemented."
              << std::endl;
    return result;
}

void WidgetBoxTreeWidget::adjustSubListSize(QTreeWidgetItem* cat_item)
{
    QTreeWidgetItem* embedItem = cat_item->child(0);
    if (embedItem == nullptr)
        return;

    WidgetBoxCategoryListView* list_widget =
        static_cast<WidgetBoxCategoryListView*>(itemWidget(embedItem, 0));
    list_widget->setFixedWidth(header()->width());
    list_widget->doItemsLayout();
    const int height = qMax(list_widget->contentsSize().height(), 1);
    list_widget->setFixedHeight(height);
    embedItem->setSizeHint(0, QSize(-1, height - 1));
}

int WidgetBoxTreeWidget::categoryCount() const
{
    return topLevelItemCount();
}

WidgetBoxTreeWidget::Category WidgetBoxTreeWidget::category(int cat_idx) const
{
    if (cat_idx >= topLevelItemCount())
        return Category();

    QTreeWidgetItem* cat_item = topLevelItem(cat_idx);

    QTreeWidgetItem* embedItem = cat_item->child(0);
    WidgetBoxCategoryListView* categoryView =
        static_cast<WidgetBoxCategoryListView*>(itemWidget(embedItem, 0));

    Category result = categoryView->category();
    result.setName(cat_item->text(0));

    switch (topLevelRole(cat_item)) {
    case SCRATCHPAD_ITEM:
        result.setType(Category::Scratchpad);
        break;
    default:
        result.setType(Category::Default);
        break;
    }
    return result;
}

void WidgetBoxTreeWidget::addCategory(const Category& cat)
{
    if (cat.widgetCount() == 0)
        return;

    const bool isScratchPad = cat.type() == Category::Scratchpad;
    WidgetBoxCategoryListView* categoryView;
    QTreeWidgetItem* cat_item;

    if (isScratchPad) {
        const int idx = ensureScratchpad();
        categoryView = categoryViewAt(idx);
        cat_item = topLevelItem(idx);
    } else {
        const int existingIndex = indexOfCategory(cat.name());
        if (existingIndex == -1) {
            cat_item = new QTreeWidgetItem();
            cat_item->setText(0, cat.name());
            setTopLevelRole(NORMAL_ITEM, cat_item);
            // insert before scratchpad
            const int scratchPadIndex = indexOfScratchpad();
            if (scratchPadIndex == -1) {
                addTopLevelItem(cat_item);
            } else {
                insertTopLevelItem(scratchPadIndex, cat_item);
            }
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
            cat_item->setExpanded(true);
#else
            setItemExpanded(cat_item, true);
#endif

            categoryView = addCategoryView(cat_item, m_iconMode);
        } else {
            categoryView = categoryViewAt(existingIndex);
            cat_item = topLevelItem(existingIndex);
        }
    }
    // The same categories are read from the file $HOME, avoid duplicates
    const int widgetCount = cat.widgetCount();
    for (int i = 0; i < widgetCount; ++i) {
        const Widget w = cat.widget(i);
        if (!categoryView->containsWidget(w.name()))
            categoryView->addWidget(w, iconForWidget(w.iconName()), isScratchPad);
    }
    adjustSubListSize(cat_item);
}

void WidgetBoxTreeWidget::removeCategory(int cat_idx)
{
    if (cat_idx >= topLevelItemCount())
        return;
    delete takeTopLevelItem(cat_idx);
}

int WidgetBoxTreeWidget::widgetCount(int cat_idx) const
{
    if (cat_idx >= topLevelItemCount())
        return 0;
    // SDK functions want unfiltered access
    return categoryViewAt(cat_idx)->count(WidgetBoxCategoryListView::UNFILTERED);
}

WidgetBoxTreeWidget::Widget WidgetBoxTreeWidget::widget(int cat_idx, int wgt_idx) const
{
    if (cat_idx >= topLevelItemCount())
        return Widget();
    // SDK functions want unfiltered access
    WidgetBoxCategoryListView* categoryView = categoryViewAt(cat_idx);
    return categoryView->widgetAt(WidgetBoxCategoryListView::UNFILTERED, wgt_idx);
}

void WidgetBoxTreeWidget::addWidget(int cat_idx, const Widget& wgt)
{
    if (cat_idx >= topLevelItemCount())
        return;

    QTreeWidgetItem* cat_item = topLevelItem(cat_idx);
    WidgetBoxCategoryListView* categoryView = categoryViewAt(cat_idx);

    const bool scratch = topLevelRole(cat_item) == SCRATCHPAD_ITEM;
    categoryView->addWidget(wgt, iconForWidget(wgt.iconName()), scratch);
    adjustSubListSize(cat_item);
}

void WidgetBoxTreeWidget::removeWidget(int cat_idx, int wgt_idx)
{
    if (cat_idx >= topLevelItemCount())
        return;

    WidgetBoxCategoryListView* categoryView = categoryViewAt(cat_idx);

    // SDK functions want unfiltered access
    const WidgetBoxCategoryListView::EAccessMode am = WidgetBoxCategoryListView::UNFILTERED;
    if (wgt_idx >= categoryView->count(am))
        return;

    categoryView->removeRow(am, wgt_idx);
}

void WidgetBoxTreeWidget::slotScratchPadItemDeleted()
{
    const int scratch_idx = indexOfScratchpad();
    QTreeWidgetItem* scratch_item = topLevelItem(scratch_idx);
    adjustSubListSize(scratch_item);
    save();
}

void WidgetBoxTreeWidget::slotLastScratchPadItemDeleted()
{
    // Remove the scratchpad in the next idle loop
    if (!m_scratchPadDeleteTimer) {
        m_scratchPadDeleteTimer = new QTimer(this);
        m_scratchPadDeleteTimer->setSingleShot(true);
        m_scratchPadDeleteTimer->setInterval(0);
        connect(m_scratchPadDeleteTimer, SIGNAL(timeout()), this, SLOT(deleteScratchpad()));
    }
    if (!m_scratchPadDeleteTimer->isActive())
        m_scratchPadDeleteTimer->start();
}

void WidgetBoxTreeWidget::deleteScratchpad()
{
    const int idx = indexOfScratchpad();
    if (idx == -1)
        return;
    delete takeTopLevelItem(idx);
    save();
}

void WidgetBoxTreeWidget::slotListMode()
{
    m_iconMode = false;
    updateViewMode();
}

void WidgetBoxTreeWidget::slotIconMode()
{
    m_iconMode = true;
    updateViewMode();
}

void WidgetBoxTreeWidget::updateViewMode()
{
    if (const int numTopLevels = topLevelItemCount()) {
        for (int i = numTopLevels - 1; i >= 0; --i) {
            QTreeWidgetItem* topLevel = topLevelItem(i);
            // Scratch pad stays in list mode.
            const QListView::ViewMode viewMode =
                m_iconMode && (topLevelRole(topLevel) != SCRATCHPAD_ITEM) ? QListView::IconMode
                                                                          : QListView::ListMode;
            WidgetBoxCategoryListView* categoryView = categoryViewAt(i);
            if (viewMode != categoryView->viewMode()) {
                categoryView->setViewMode(viewMode);
                adjustSubListSize(topLevelItem(i));
            }
        }
    }
    updateGeometries();
}

void WidgetBoxTreeWidget::resizeEvent(QResizeEvent* e)
{
    QTreeWidget::resizeEvent(e);
    if (const int numTopLevels = topLevelItemCount()) {
        for (int i = numTopLevels - 1; i >= 0; --i)
            adjustSubListSize(topLevelItem(i));
    }
}

void WidgetBoxTreeWidget::contextMenuEvent(QContextMenuEvent* e)
{
    QTreeWidgetItem* item = itemAt(e->pos());

    const bool scratchpad_menu = item != nullptr && item->parent() != nullptr
                                 && topLevelRole(item->parent()) == SCRATCHPAD_ITEM;

    QMenu menu;
    menu.addAction("Expand all", this, SLOT(expandAll()));
    menu.addAction("Collapse all", this, SLOT(collapseAll()));
    menu.addSeparator();

    QAction* listModeAction = menu.addAction("List View");
    QAction* iconModeAction = menu.addAction("Icon View");
    listModeAction->setCheckable(true);
    iconModeAction->setCheckable(true);
    QActionGroup* viewModeGroup = new QActionGroup(&menu);
    viewModeGroup->addAction(listModeAction);
    viewModeGroup->addAction(iconModeAction);
    if (m_iconMode)
        iconModeAction->setChecked(true);
    else
        listModeAction->setChecked(true);
    connect(listModeAction, SIGNAL(triggered()), SLOT(slotListMode()));
    connect(iconModeAction, SIGNAL(triggered()), SLOT(slotIconMode()));

    if (scratchpad_menu) {
        menu.addSeparator();
        menu.addAction("Remove", itemWidget(item, 0), SLOT(removeCurrentItem()));
        if (!m_iconMode)
            menu.addAction("Edit name", itemWidget(item, 0), SLOT(editCurrentItem()));
    }
    e->accept();
    menu.exec(mapToGlobal(e->pos()));
}

void WidgetBoxTreeWidget::dropWidgets(const QList<QDesignerDnDItemInterface*>& item_list)
{
    QTreeWidgetItem* scratch_item = nullptr;
    WidgetBoxCategoryListView* categoryView = nullptr;
    bool added = false;

    for (QDesignerDnDItemInterface* item : item_list) {
        QWidget* w = item->widget();
        if (w == nullptr)
            continue;

        DomUI* dom_ui = item->domUi();
        if (dom_ui == nullptr)
            continue;

        const int scratch_idx = ensureScratchpad();
        scratch_item = topLevelItem(scratch_idx);
        categoryView = categoryViewAt(scratch_idx);

        // Temporarily remove the fake toplevel in-between
        DomWidget* fakeTopLevel = dom_ui->takeElementWidget();
        DomWidget* firstWidget = nullptr;
        if (fakeTopLevel && !fakeTopLevel->elementWidget().isEmpty()) {
            firstWidget = fakeTopLevel->elementWidget().first();
            dom_ui->setElementWidget(firstWidget);
        } else {
            dom_ui->setElementWidget(fakeTopLevel);
            continue;
        }
        // Serialize to XML
        QString xml;
        {
            QXmlStreamWriter writer(&xml);
            writer.setAutoFormatting(true);
            writer.setAutoFormattingIndent(1);
            writer.writeStartDocument();
            dom_ui->write(writer);
            writer.writeEndDocument();
        }
        // Insert fake toplevel again
        dom_ui->takeElementWidget();
        dom_ui->setElementWidget(fakeTopLevel);

        const Widget wgt = Widget(w->objectName(), xml);
        categoryView->addWidget(wgt, iconForWidget(wgt.iconName()), true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
        scratch_item->setExpanded(true);
#else
        setItemExpanded(scratch_item, true);
#endif

        added = true;
    }
    if (added) {
        save();
        QApplication::setActiveWindow(this);
        // Is the new item visible in filtered mode?
        const WidgetBoxCategoryListView::EAccessMode am = WidgetBoxCategoryListView::FILTERED;
        if (const int count = categoryView->count(am))
            categoryView->setCurrentItem(am, count - 1);
        categoryView->adjustSize(); // XXX
        adjustSubListSize(scratch_item);
    }
}

void WidgetBoxTreeWidget::filter(const QString& f)
{
    const bool empty = f.isEmpty();
    QRegExp re = empty ? QRegExp() : QRegExp(f, Qt::CaseInsensitive, QRegExp::FixedString);
    const int numTopLevels = topLevelItemCount();
    bool changed = false;
    for (int i = 0; i < numTopLevels; i++) {
        QTreeWidgetItem* tl = topLevelItem(i);
        WidgetBoxCategoryListView* categoryView = categoryViewAt(i);
        // Anything changed? -> Enable the category
        const int oldCount = categoryView->count(WidgetBoxCategoryListView::FILTERED);
        categoryView->filter(re);
        const int newCount = categoryView->count(WidgetBoxCategoryListView::FILTERED);
        if (oldCount != newCount) {
            changed = true;
            const bool categoryEnabled = newCount > 0 || empty;
            if (categoryEnabled) {
                categoryView->adjustSize();
                adjustSubListSize(tl);
            }
            setRowHidden(i, QModelIndex(), !categoryEnabled);
        }
    }
    if (changed)
        updateGeometries();
}

} // namespace qdesigner_internal

QT_END_NAMESPACE
