// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditorDialog.cpp
//! @brief     Implements class MaterialEditorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaterialEditor/MaterialEditorDialog.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialEditor.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "GUI/coregui/utils/StyleUtils.h"
#include <QAction>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

namespace
{
const QSize default_dialog_size(512, 400);
}

MaterialEditorDialog::MaterialEditorDialog(MaterialModel* materialModel, QWidget* parent)
    : QDialog(parent), m_origMaterialModel(materialModel), m_materialEditor(nullptr)
{
    setWindowTitle("Material Editor");
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    init_material_editor();

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_materialEditor);
    layout->addLayout(createButtonLayout());

    setLayout(layout);

    StyleUtils::setResizable(this);
}

//! replaces original material model with the model modified by MaterialEditor
void MaterialEditorDialog::onOKButton()
{
    if (m_materialEditor->modelWasChanged()) {
        m_origMaterialModel->clear();
        m_origMaterialModel->initFrom(m_tmpMaterialModel.get(), 0);
    }
    writeSettings();
    accept();
}

void MaterialEditorDialog::onCancelButton()
{
    writeSettings();
    reject();
}

QBoxLayout* MaterialEditorDialog::createButtonLayout()
{
    auto result = new QHBoxLayout;

    auto okButton = new QPushButton("OK");
    connect(okButton, &QPushButton::clicked, this, &MaterialEditorDialog::onOKButton);
    auto cancelButton = new QPushButton("Cancel");
    connect(cancelButton, &QPushButton::clicked, this, &MaterialEditorDialog::onCancelButton);

    result->setMargin(10);
    result->setSpacing(5);
    result->addStretch(1);
    result->addWidget(okButton);
    result->addWidget(cancelButton);

    return result;
}

void MaterialEditorDialog::init_material_editor()
{
    ASSERT(m_origMaterialModel);
    m_tmpMaterialModel.reset(m_origMaterialModel->createCopy());
    m_materialEditor = new MaterialEditor(m_tmpMaterialModel.get(), this);
    readSettings();
}

void MaterialEditorDialog::readSettings()
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_MATERIALEDITOR)) {
        settings.beginGroup(Constants::S_MATERIALEDITOR);
        resize(settings.value(Constants::S_WINDOWSIZE, default_dialog_size).toSize());
        if (settings.contains(Constants::S_WINDOWPOSITION)) {
            move(settings.value(Constants::S_WINDOWPOSITION).toPoint());
        }
    } else {
        resize(default_dialog_size);
    }
}

void MaterialEditorDialog::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_MATERIALEDITOR);
    settings.setValue(Constants::S_WINDOWSIZE, this->size());
    settings.setValue(Constants::S_WINDOWPOSITION, this->pos());
    settings.endGroup();
}

ExternalProperty MaterialEditorDialog::selectedMaterialProperty()
{
    if (MaterialItem* material = m_materialEditor->selectedMaterial())
        return MaterialItemUtils::materialProperty(*material);

    return ExternalProperty();
}

//!
void MaterialEditorDialog::setMaterialProperty(const ExternalProperty& matProperty)
{
    ASSERT(m_materialEditor);

    m_materialEditor->setInitialMaterialProperty(matProperty);
}
