// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ScientificSpinBox.h
//! @brief     Defines class ScientificSpinBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SCIENTIFICSPINBOX_H
#define SCIENTIFICSPINBOX_H

#include "WinDllMacros.h"
#include <QDoubleSpinBox>

class BA_CORE_API_ ScientificSpinBox : public QDoubleSpinBox
{
public:
    ScientificSpinBox(QWidget* parent = nullptr);
    ~ScientificSpinBox() override;

    double valueFromText(const QString& text) const override;
    QString textFromValue(double val) const override;

    void setDecimalPoints(int val);
    int decimalPoints() const;

    static QString toString(double val, int decimal_points);
    static double toDouble(QString text, const QDoubleValidator& validator,
                           double min, double max, double default_value);

private:
    void setDecimals(int);
    int decimals() const;

    int m_decimal_points;
    QDoubleValidator m_validator;
};

#endif // SCIENTIFICSPINBOX_H
