// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/CustomEditors.h
//! @brief     Defines CustomEditors classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_CUSTOMEDITORS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_CUSTOMEDITORS_H

#include "Wrap/WinDllMacros.h"
#include <QVariant>
#include <QWidget>

class LostFocusFilter;
class QLabel;
class QComboBox;
class RealLimits;

//! Base class for all custom variants editors.

class BA_CORE_API_ CustomEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CustomEditor(QWidget* parent = nullptr) : QWidget(parent) {}

    QVariant editorData() { return m_data; }

public slots:
    void setData(const QVariant& data);

signals:
    //! Signal emit then user changed the data through the editor
    void dataChanged(const QVariant& data);

protected:
    virtual void initEditor();
    void setDataIntern(const QVariant& data);
    QVariant m_data;
};

//! Editor for ExternalProperty variant.

class BA_CORE_API_ ExternalPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit ExternalPropertyEditor(QWidget* parent = nullptr);

    void setExternalDialogType(const QString& dialogType);

private slots:
    void buttonClicked();

protected:
    void initEditor();

private:
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
    LostFocusFilter* m_focusFilter;
    QString m_extDialogType; //!< Type of the dialog which will be created on button click
};

//! Editor for ComboProperty variant.

class BA_CORE_API_ ComboPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit ComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected slots:
    virtual void onIndexChanged(int index);

protected:
    void initEditor();
    virtual QStringList internLabels();
    virtual int internIndex();
    void setConnected(bool isConnected);

    QComboBox* m_box;
    class WheelEventEater* m_wheel_event_filter;
};

//! Editor for ScientificDoubleProperty variant.

class BA_CORE_API_ ScientificDoublePropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    ScientificDoublePropertyEditor(QWidget* parent = nullptr);

    void setLimits(const RealLimits& limits);

private slots:
    void onEditingFinished();

protected:
    void initEditor();

private:
    class QLineEdit* m_lineEdit;
    class QDoubleValidator* m_validator;
};

//! Editor for Double variant.

class BA_CORE_API_ DoubleEditor : public CustomEditor
{
    Q_OBJECT
public:
    DoubleEditor(QWidget* parent = nullptr);

    void setLimits(const RealLimits& limits);
    void setDecimals(int decimals);

private slots:
    void onEditingFinished();

protected:
    void initEditor();

private:
    class QDoubleSpinBox* m_doubleEditor;
};

//! Editor for Double variant using ScientificSpinBox.

class BA_CORE_API_ ScientificSpinBoxEditor : public CustomEditor
{
    Q_OBJECT
public:
    ScientificSpinBoxEditor(QWidget* parent = nullptr);

    void setLimits(const RealLimits& limits);
    void setDecimals(int decimals);
    void setSingleStep(double step);

private slots:
    void onEditingFinished();

protected:
    void initEditor();

private:
    class ScientificSpinBox* m_doubleEditor;
};

//! Editor for Int variant.

class BA_CORE_API_ IntEditor : public CustomEditor
{
    Q_OBJECT
public:
    IntEditor(QWidget* parent = nullptr);

    void setLimits(const RealLimits& limits);

private slots:
    void onEditingFinished();

protected:
    void initEditor();

private:
    class QSpinBox* m_intEditor;
};

//! Editor for boolean.

class QCheckBox;

class BA_CORE_API_ BoolEditor : public CustomEditor
{
    Q_OBJECT
public:
    BoolEditor(QWidget* parent = nullptr);

private slots:
    void onCheckBoxChange(bool value);

protected:
    void initEditor();

private:
    QCheckBox* m_checkBox;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_CUSTOMEDITORS_H
