// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PlotStatusDescriptors.cpp
//! @brief     Implementations of plot descriptors to manage mouse position info
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PlotStatusDescriptors.h"

IPlotDescriptor::IPlotDescriptor()
    : m_in_axes_range(false), m_x(0.0), m_y(0.0)
{
}

IPlotDescriptor::~IPlotDescriptor() = default;

SpecularPlotDescriptor::SpecularPlotDescriptor()
    : IPlotDescriptor(), m_nx(0)
{
}

SpecularPlotDescriptor::~SpecularPlotDescriptor() = default;

QString SpecularPlotDescriptor::statusString() const
{
    QString result = QString(" [x: %1, y: %2]    [binx: %3]")
                         .arg(QString::number(x(), 'f', 4))
                         .arg(valueToString())
                         .arg(m_nx, 2);

    return result;
}

QString SpecularPlotDescriptor::valueToString() const
{
    return QString::fromStdString(PythonFormatting::printScientificDouble(y()));
}

ColorMapDescriptor::ColorMapDescriptor()
    : IPlotDescriptor(), m_nx(0), m_ny(0), m_value(0), m_logz(false)
{
}

ColorMapDescriptor::~ColorMapDescriptor() = default;

QString ColorMapDescriptor::statusString() const
{
    QString result = QString(" [x: %1, y: %2]    [binx: %3, biny:%4]    [value: %5]")
                         .arg(QString::number(x(), 'f', 4))
                         .arg(QString::number(y(), 'f', 4), 2)
                         .arg(m_nx, 2)
                         .arg(m_ny, 2)
                         .arg(valueToString());

    return result;
}

QString ColorMapDescriptor::valueToString() const
{
    return m_logz ? QString::fromStdString(PythonFormatting::printScientificDouble(m_value))
                  : QString::number(m_value, 'f', 2);
}
