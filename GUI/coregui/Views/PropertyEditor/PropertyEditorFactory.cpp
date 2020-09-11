// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.cpp
//! @brief     Implements PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.h"
#include "Fit/Tools/RealLimits.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/GroupItemController.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/JobWidgets/ScientificSpinBox.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/PropertyEditor/CustomEditors.h"
#include "GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.h"
#include "GUI/coregui/utils/CustomEventFilters.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <limits>

namespace
{
QWidget* createCustomStringEditor(const SessionItem& item);
double getStep(double val);

bool isDoubleProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Double;
}

bool isIntProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Int;
}

bool isExternalProperty(const QVariant& variant)
{
    return variant.canConvert<ExternalProperty>();
}

bool isComboProperty(const QVariant& variant)
{
    return variant.canConvert<ComboProperty>();
}

bool isStringProperty(const QVariant& variant)
{
    return variant.type() == QVariant::String;
}

bool isBoolProperty(const QVariant& variant)
{
    return variant.type() == QVariant::Bool;
}

} // namespace

bool PropertyEditorFactory::hasStringRepresentation(const QModelIndex& index)
{
    auto variant = index.data();
    if (isExternalProperty(variant))
        return true;
    if (isComboProperty(variant))
        return true;
    if (isBoolProperty(variant))
        return true;
    if (isDoubleProperty(variant) && index.internalPointer())
        return true;

    return false;
}

QString PropertyEditorFactory::toString(const QModelIndex& index)
{
    auto variant = index.data();
    if (isExternalProperty(variant))
        return variant.value<ExternalProperty>().text();
    if (isComboProperty(variant))
        return variant.value<ComboProperty>().label();
    if (isBoolProperty(variant))
        return variant.toBool() ? "True" : "False";

    if (isDoubleProperty(variant) && index.internalPointer()) {
        auto item = static_cast<SessionItem*>(index.internalPointer());
        return item->editorType() == "ScientificDouble"
                   ? QString::number(item->value().toDouble(), 'g')
                   : item->editorType() == "ScientificSpinBox"
                         ? ScientificSpinBox::toString(item->value().toDouble(), item->decimals())
                         : QString::number(item->value().toDouble(), 'f', item->decimals());
    }

    return "";
}

QWidget* PropertyEditorFactory::CreateEditor(const SessionItem& item, QWidget* parent)
{
    QWidget* result(nullptr);

    if (isDoubleProperty(item.value())) {
        if (item.editorType() == "ScientificDouble") {
            auto editor = new ScientificDoublePropertyEditor;
            auto limits = item.limits();
            editor->setLimits(limits);
            result = editor;
        } else if (item.editorType() == "ScientificSpinBox") {
            auto editor = new ScientificSpinBoxEditor;
            auto limits = item.limits();
            editor->setLimits(limits);
            editor->setDecimals(item.decimals());
            editor->setSingleStep(getStep(item.roleProperty(Qt::EditRole).toDouble()));
            result = editor;
        } else {
            auto editor = new DoubleEditor;
            editor->setLimits(item.limits());
            editor->setDecimals(item.decimals());
            result = editor;
        }
    } else if (isIntProperty(item.value())) {
        auto editor = new IntEditor;
        editor->setLimits(item.limits());
        result = editor;
    } else if (isBoolProperty(item.value())) {
        auto editor = new BoolEditor;
        result = editor;
    } else if (isStringProperty(item.value())) {
        result = createCustomStringEditor(item);
    } else if (isExternalProperty(item.value())) {
        auto editor = new ExternalPropertyEditor;
        if (item.editorType() != "Default")
            editor->setExternalDialogType(item.editorType());
        result = editor;
    } else if (isComboProperty(item.value())) {
        if (item.editorType() == "Default") {
            auto editor = new ComboPropertyEditor;
            result = editor;
        } else if (item.editorType() == "MultiSelectionComboEditor") {
            auto editor = new MultiComboPropertyEditor;
            result = editor;
        }
    }
    if (parent && result)
        result->setParent(parent);

    return result;
}

namespace
{

QWidget* createCustomStringEditor(const SessionItem& item)
{
    QWidget* result(nullptr);

    if (item.isEditable()) {
        auto editor = new QLineEdit;
        editor->setText(item.value().toString());
        result = editor;
    } else {
        auto editor = new QLabel;
        editor->setText(item.value().toString());
        result = editor;
    }

    return result;
}

double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}

} // namespace
