// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DetailedMessageBox.h
//! @brief     Defines class DetailedMessageBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_DETAILEDMESSAGEBOX_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_DETAILEDMESSAGEBOX_H

#include "Wrap/WinDllMacros.h"
#include <QDialog>
#include <QString>

class QLabel;
class QTextEdit;
class QBoxLayout;

//! A dialog similar to standard QMessageBox intended for detailed warning messages.
//! On the contrary to QMessageBox, the dialog has size grip and visible text editor.

class BA_CORE_API_ DetailedMessageBox : public QDialog
{
    Q_OBJECT
public:
    DetailedMessageBox(QWidget* parent, const QString& title, const QString& text,
                       const QString& details);

    void setText(const QString& text);
    void setDetailedText(const QString& text);

private:
    QBoxLayout* createLogoLayout();
    QBoxLayout* createInfoLayout();
    QBoxLayout* createButtonLayout();

    QLabel* m_topLabel;
    QTextEdit* m_textEdit;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_DETAILEDMESSAGEBOX_H
