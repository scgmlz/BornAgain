// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/StyleUtils.cpp
//! @brief     DefinesStyleUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/utils/StyleUtils.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/Views/CommonWidgets/detailswidget.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/utils/hostosinfo.h"
#include <QApplication>
#include <QBoxLayout>
#include <QDialog>
#include <QTreeView>

namespace
{
Utils::DetailsWidget* createEmptyDetailsWidget(const QString& name, bool expanded);
QSize FindSizeOfLetterM(const QWidget* widget);

QSize DefaultSizeOfLetterM()
{
    QWidget widget;
    return FindSizeOfLetterM(&widget);
}
} // namespace

void StyleUtils::setPropertyStyle(QTreeView* tree)
{
    ASSERT(tree);
    tree->setStyleSheet(StyleUtils::propertyTreeStyle());
    tree->setAlternatingRowColors(true);
}

QString StyleUtils::propertyTreeStyle()
{
    QString result;

    // lines arount cell content
    result += "QTreeView::item {"
              "    border-bottom: 1px solid #c7c8c9; "
              "    border-right: 1px solid #c7c8c9;}"
              "QTreeView::branch {border-bottom: 1px solid #c7c8c9;}";

    // styling of branch to restore open/closed signs eliminated by previous styling
    result += "QTreeView::branch:has-children:!has-siblings:closed,"
              "QTreeView::branch:closed:has-children:has-siblings {"
              "padding:2px 2px 2px 2px;border-image: none;"
              "image: url(:/images/caret-right.svg);}"
              "QTreeView::branch:open:has-children:!has-siblings,"
              "QTreeView::branch:open:has-children:has-siblings  {"
              "padding:2px 2px 2px 2px;border-image: none; image: url(:/images/caret-down.svg);"
              "}";

    // background of selected rows restored
    result += "QTreeView::item:selected{background:#3daee9;}";

    return result;
}

QFont StyleUtils::sectionFont(bool bold)
{
    QFont result;
    result.setPointSize(DesignerHelper::getSectionFontSize());
    result.setBold(bold);

    return result;
}

QFont StyleUtils::labelFont(bool bold)
{
    QFont result;
    result.setPointSize(DesignerHelper::getLabelFontSize());
    result.setBold(bold);

    return result;
}

void StyleUtils::setResizable(QDialog* dialog)
{
    if (GUI_OS_Utils::HostOsInfo::isMacHost()) {
        dialog->setWindowFlags(Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint
                               | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint
                               | Qt::Window);
    }
}

QWidget* StyleUtils::createDetailsWidget(QWidget* content, const QString& name, bool expanded)
{
    auto result = createEmptyDetailsWidget(name, expanded);
    result->setWidget(content);
    return result;
}

QWidget* StyleUtils::createDetailsWidget(QLayout* layout, const QString& name, bool expanded)
{
    auto placeholder = new QWidget();
    placeholder->setLayout(layout);
    return createDetailsWidget(placeholder, name, expanded);
}

QSize StyleUtils::SizeOfLetterM(const QWidget* widget)
{
    static QSize default_size = DefaultSizeOfLetterM();
    return widget ? FindSizeOfLetterM(widget) : default_size;
}

int StyleUtils::SystemPointSize()
{
    return QApplication::font().pointSize();
}

int StyleUtils::PropertyPanelWidth()
{
    return SizeOfLetterM().width() * 16;
}

namespace
{

Utils::DetailsWidget* createEmptyDetailsWidget(const QString& name, bool expanded)
{
    auto result = new Utils::DetailsWidget;
    result->setSummaryText(name);
    result->setSummaryFontBold(true);
    if (expanded)
        result->setState(Utils::DetailsWidget::Expanded);
    return result;
}

//! Calculates size of letter `M` for current system font settings.

QSize FindSizeOfLetterM(const QWidget* widget)
{
    QFontMetrics fontMetric(widget->font());
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    auto em = fontMetric.horizontalAdvance('M');
#else
    auto em = fontMetric.width('M');
#endif
    auto fontAscent = fontMetric.ascent();

    return QSize(em, fontAscent);
}

} // namespace
