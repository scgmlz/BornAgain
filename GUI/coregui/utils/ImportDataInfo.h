// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/ImportDataInfo.h
//! @brief     Defines ImportDataInfo helper struct
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_UTILS_IMPORTDATAINFO_H
#define BORNAGAIN_GUI_COREGUI_UTILS_IMPORTDATAINFO_H

#include "Core/Intensity/IUnitConverter.h"
#include "Wrap/WinDllMacros.h"
#include <QString>
#include <memory>

template <class T> class OutputData;

//! Carries information about loaded data.

class BA_CORE_API_ ImportDataInfo
{
public:
    ImportDataInfo();
    ImportDataInfo(ImportDataInfo&& other);
    ImportDataInfo(std::unique_ptr<OutputData<double>> data, AxesUnits units);
    ImportDataInfo(std::unique_ptr<OutputData<double>> data, const QString& units);
    ~ImportDataInfo();

    operator bool() const;

    std::unique_ptr<OutputData<double>> intensityData() const&;
    std::unique_ptr<OutputData<double>> intensityData() &&;
    size_t dataRank() const;
    QString unitsLabel() const;
    QString axisLabel(size_t axis_index) const;

private:
    void checkValidity();
    std::unique_ptr<OutputData<double>> m_data;
    AxesUnits m_units;
};

#endif // BORNAGAIN_GUI_COREGUI_UTILS_IMPORTDATAINFO_H
