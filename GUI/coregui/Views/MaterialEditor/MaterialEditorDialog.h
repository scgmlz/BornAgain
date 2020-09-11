// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditorDialog.h
//! @brief     Defines class MaterialEditorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITORDIALOG_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITORDIALOG_H

#include "Wrap/WinDllMacros.h"
#include <QDialog>
#include <memory>

class MaterialModel;
class MaterialEditor;
class ExternalProperty;
class QBoxLayout;

//! Dialog to hold MaterialEditor.
//! It's main function is to return MaterialModel to original state, if user decided to cancel
//! changes.

class BA_CORE_API_ MaterialEditorDialog : public QDialog
{
    Q_OBJECT

public:
    MaterialEditorDialog(MaterialModel* materialModel, QWidget* parent = nullptr);

    ExternalProperty selectedMaterialProperty();

    void setMaterialProperty(const ExternalProperty& matProperty);

public slots:
    void onOKButton();
    void onCancelButton();

private:
    QBoxLayout* createButtonLayout();

    void init_material_editor();
    void readSettings();
    void writeSettings();

    MaterialModel* m_origMaterialModel;
    std::unique_ptr<MaterialModel> m_tmpMaterialModel;
    MaterialEditor* m_materialEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALEDITORDIALOG_H
