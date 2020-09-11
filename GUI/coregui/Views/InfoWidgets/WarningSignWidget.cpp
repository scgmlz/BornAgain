// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/WarningSignWidget.cpp
//! @brief     Implements class WarningSignWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/InfoWidgets/WarningSignWidget.h"
#include <QMessageBox>
#include <QPainter>
#include <QRect>

WarningSignWidget::WarningSignWidget(QWidget* parent)
    : QWidget(parent), m_pixmap(":/images/warning@2x.png"),
      m_warning_header("Houston, we have a problem.")
{
    setAttribute(Qt::WA_NoSystemBackground);
    setToolTip(m_warning_header + "\nClick to see details.");
}

void WarningSignWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect target(m_pixmap.rect());
    painter.drawPixmap(target, m_pixmap);
}

void WarningSignWidget::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    QMessageBox box;
    box.setWindowTitle(m_warning_header);
    box.setInformativeText(m_warning_message);
    box.setStandardButtons(QMessageBox::Ok);
    box.setDefaultButton(QMessageBox::Ok);
    box.exec();
}

//! set geometry of widget around center point
void WarningSignWidget::setPosition(int x, int y)
{
    setGeometry(x, y, m_pixmap.width(), m_pixmap.height());
}

void WarningSignWidget::setWarningHeader(const QString& message)
{
    m_warning_header = message;
    setToolTip(m_warning_header + "\nClick to see details.");
}
