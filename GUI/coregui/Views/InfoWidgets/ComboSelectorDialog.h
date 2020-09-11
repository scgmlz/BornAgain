// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/ComboSelectorDialog.h
//! @brief     Defines class ComboSelectorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_COMBOSELECTORDIALOG_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_COMBOSELECTORDIALOG_H

#include "Wrap/WinDllMacros.h"
#include <QDialog>
#include <QString>

class QLabel;
class QComboBox;
class QBoxLayout;

//! A dialog similar to standard QMessageBox with combo box selector.

class BA_CORE_API_ ComboSelectorDialog : public QDialog
{
    Q_OBJECT
public:
    ComboSelectorDialog(QWidget* parent = 0);

    void addItems(const QStringList& selection, const QString& currentItem = "");
    void setTextTop(const QString& text);
    void setTextBottom(const QString& text);

    QString currentText() const;

private:
    QBoxLayout* createLogoLayout();
    QBoxLayout* createInfoLayout();
    QBoxLayout* createButtonLayout();

    QLabel* m_topLabel;
    QComboBox* m_comboSelector;
    QLabel* m_bottomLabel;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INFOWIDGETS_COMBOSELECTORDIALOG_H
