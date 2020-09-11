// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/CustomEditors.cpp
//! @brief     Implements CustomEditors classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/PropertyEditor/CustomEditors.h"
#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/GroupItemController.h"
#include "GUI/coregui/Views/JobWidgets/ScientificSpinBox.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/utils/CustomEventFilters.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QApplication>
#include <QBoxLayout>
#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <cmath>

namespace
{
//! Single step for QDoubleSpinBox.

double singleStep(int decimals)
{
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1. / std::pow(10., decimals - 1);
}

} // namespace

//! Sets the data from the model to editor.

void CustomEditor::setData(const QVariant& data)
{
    m_data = data;
    initEditor();
}

//! Inits editor widgets from m_data.

void CustomEditor::initEditor() {}

//! Saves the data from the editor and informs external delegates.

void CustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged(m_data);
}

// --- MaterialPropertyEditor ---

ExternalPropertyEditor::ExternalPropertyEditor(QWidget* parent)
    : CustomEditor(parent), m_textLabel(new QLabel), m_pixmapLabel(new QLabel),
      m_focusFilter(new LostFocusFilter(this)), m_extDialogType("ExtMaterialEditor")
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    ExternalProperty defProperty; // to get label and pixmap of undefined material
    m_textLabel->setText(defProperty.text());
    m_pixmapLabel->setPixmap(defProperty.pixmap());

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));
    button->setText(QLatin1String(" . . . "));
    button->setToolTip("Material selector");
    layout->addWidget(m_pixmapLabel);
    layout->addWidget(m_textLabel);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &ExternalPropertyEditor::buttonClicked);

    setLayout(layout);
}

void ExternalPropertyEditor::setExternalDialogType(const QString& editorType)
{
    m_extDialogType = editorType;
}

void ExternalPropertyEditor::buttonClicked()
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);
    ExternalProperty property = m_data.value<ExternalProperty>();

    ExternalProperty newProperty;
    if (m_extDialogType == "ExtMaterialEditor") {
        newProperty = MaterialItemUtils::selectMaterialProperty(property);
    } else if (m_extDialogType == "ExtColorEditor") {
        newProperty = MaterialItemUtils::selectColorProperty(property);
    } else {
        throw GUIHelpers::Error("ExternalPropertyEditor::buttonClicked() -> Unexpected dialog");
    }

    removeEventFilter(m_focusFilter);

    if (newProperty.isValid() && newProperty != property)
        setDataIntern(newProperty.variant());
}

void ExternalPropertyEditor::initEditor()
{
    ASSERT(m_data.canConvert<ExternalProperty>());
    ExternalProperty materialProperty = m_data.value<ExternalProperty>();
    m_textLabel->setText(materialProperty.text());
    m_pixmapLabel->setPixmap(materialProperty.pixmap());
}

// --- CustomComboEditor ---

ComboPropertyEditor::ComboPropertyEditor(QWidget* parent)
    : CustomEditor(parent), m_box(new QComboBox), m_wheel_event_filter(new WheelEventEater(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);

    m_box->installEventFilter(m_wheel_event_filter);

    setLayout(layout);
    setConnected(true);
}

QSize ComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize ComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void ComboPropertyEditor::onIndexChanged(int index)
{
    ComboProperty comboProperty = m_data.value<ComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
    }
}

void ComboPropertyEditor::initEditor()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, internLabels());
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

QStringList ComboPropertyEditor::internLabels()
{
    if (!m_data.canConvert<ComboProperty>())
        return {};
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.getValues();
}

//! Returns index for QComboBox.

int ComboPropertyEditor::internIndex()
{
    if (!m_data.canConvert<ComboProperty>())
        return 0;
    ComboProperty comboProperty = m_data.value<ComboProperty>();
    return comboProperty.currentIndex();
}

void ComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &ComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &ComboPropertyEditor::onIndexChanged);
}

// --- ScientificDoublePropertyEditor ---

ScientificDoublePropertyEditor::ScientificDoublePropertyEditor(QWidget* parent)
    : CustomEditor(parent), m_lineEdit(new QLineEdit), m_validator(nullptr)
{
    setAutoFillBackground(true);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_lineEdit);

    m_validator = new QDoubleValidator(0.0, 1e+200, 1000, this);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(m_validator);

    connect(m_lineEdit, &QLineEdit::editingFinished, this,
            &ScientificDoublePropertyEditor::onEditingFinished);

    setLayout(layout);
}

void ScientificDoublePropertyEditor::setLimits(const RealLimits& limits)
{
    double minimum = limits.hasLowerLimit() ? std::max(limits.lowerLimit(), -1e+200) : -1e+200;
    double maximum = limits.hasUpperLimit() ? std::min(limits.upperLimit(), +1e+200) : +1e+200;
    m_validator->setRange(minimum, maximum, 1000);
}

void ScientificDoublePropertyEditor::onEditingFinished()
{
    double new_value = m_lineEdit->text().toDouble();

    if (new_value != m_data.toDouble())
        setDataIntern(QVariant::fromValue(new_value));
}

void ScientificDoublePropertyEditor::initEditor()
{
    ASSERT(m_data.type() == QVariant::Double);
    m_lineEdit->setText(QString::number(m_data.toDouble(), 'g'));
}

// --- DoubleEditor ---

DoubleEditor::DoubleEditor(QWidget* parent)
    : CustomEditor(parent), m_doubleEditor(new QDoubleSpinBox)
{
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
}

void DoubleEditor::setLimits(const RealLimits& limits)
{
    m_doubleEditor->setMaximum(std::numeric_limits<double>::max());
    m_doubleEditor->setMinimum(std::numeric_limits<double>::lowest());

    if (limits.hasLowerLimit())
        m_doubleEditor->setMinimum(limits.lowerLimit());
    if (limits.hasUpperLimit())
        m_doubleEditor->setMaximum(static_cast<int>(limits.upperLimit()));
}

void DoubleEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
    m_doubleEditor->setSingleStep(singleStep(decimals));
}

void DoubleEditor::onEditingFinished()
{
    double new_value = m_doubleEditor->value();

    if (new_value != m_data.toDouble())
        setDataIntern(QVariant::fromValue(new_value));
}

void DoubleEditor::initEditor()
{
    ASSERT(m_data.type() == QVariant::Double);
    m_doubleEditor->setValue(m_data.toDouble());
}

// --- DoubleEditor ---

ScientificSpinBoxEditor::ScientificSpinBoxEditor(QWidget* parent)
    : CustomEditor(parent), m_doubleEditor(new ScientificSpinBox)
{
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor, &ScientificSpinBox::valueChanged, [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
}

void ScientificSpinBoxEditor::setLimits(const RealLimits& limits)
{
    m_doubleEditor->setMinimum(limits.hasLowerLimit() ? limits.lowerLimit()
                                                      : std::numeric_limits<double>::lowest());
    m_doubleEditor->setMaximum(limits.hasUpperLimit() ? limits.upperLimit()
                                                      : std::numeric_limits<double>::max());
}

void ScientificSpinBoxEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
    m_doubleEditor->setSingleStep(singleStep(decimals));
}

void ScientificSpinBoxEditor::setSingleStep(double step)
{
    m_doubleEditor->setSingleStep(step);
}

void ScientificSpinBoxEditor::onEditingFinished()
{
    double new_value = m_doubleEditor->value();

    if (new_value != m_data.toDouble())
        setDataIntern(QVariant::fromValue(new_value));
}

void ScientificSpinBoxEditor::initEditor()
{
    ASSERT(m_data.type() == QVariant::Double);
    m_doubleEditor->setValue(m_data.toDouble());
}

// --- IntEditor ---

IntEditor::IntEditor(QWidget* parent) : CustomEditor(parent), m_intEditor(new QSpinBox)
{
    setAutoFillBackground(true);
    m_intEditor->setFocusPolicy(Qt::StrongFocus);
    m_intEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_intEditor);

    connect(m_intEditor, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_intEditor);
}

void IntEditor::setLimits(const RealLimits& limits)
{
    m_intEditor->setMaximum(std::numeric_limits<int>::max());

    if (limits.hasLowerLimit())
        m_intEditor->setMinimum(static_cast<int>(limits.lowerLimit()));
    if (limits.hasUpperLimit())
        m_intEditor->setMaximum(static_cast<int>(limits.upperLimit()));
}

void IntEditor::onEditingFinished()
{
    int new_value = m_intEditor->value();

    if (new_value != m_data.toInt())
        setDataIntern(QVariant::fromValue(new_value));
}

void IntEditor::initEditor()
{
    if (!m_data.isValid() || m_data.type() != QVariant::Int)
        return;
    m_intEditor->setValue(m_data.toInt());
}

// --- BoolEditor ---

BoolEditor::BoolEditor(QWidget* parent) : CustomEditor(parent), m_checkBox(new QCheckBox)
{
    setAutoFillBackground(true);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_checkBox);
    setLayout(layout);

    connect(m_checkBox, &QCheckBox::toggled, this, &BoolEditor::onCheckBoxChange);
    setFocusProxy(m_checkBox);
    m_checkBox->setText(tr("True"));
}

void BoolEditor::onCheckBoxChange(bool value)
{
    if (value != m_data.toBool())
        setDataIntern(QVariant(value));
}

void BoolEditor::initEditor()
{
    ASSERT(m_data.type() == QVariant::Bool);
    bool value = m_data.toBool();

    m_checkBox->blockSignals(true);
    m_checkBox->setChecked(value);
    m_checkBox->setText(value ? "True" : "False");
    m_checkBox->blockSignals(false);
}
