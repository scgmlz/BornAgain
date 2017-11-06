// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/SaveProjectionsAssistant.h
//! @brief     Defines class SaveProjectionsAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAVEPROJECTIONSASSISTANT_H
#define SAVEPROJECTIONSASSISTANT_H

#include "WinDllMacros.h"
#include <QString>
#include <memory>
#include <QVector>

class IntensityDataItem;
class QWidget;
class Histogram2D;
class SessionItem;

//! Assistant class which save all projections of IndensityDataItem into ASCII file.

class BA_CORE_API_ SaveProjectionsAssistant
{
public:
    SaveProjectionsAssistant();
    ~SaveProjectionsAssistant();

    void saveProjections(QWidget* parent, IntensityDataItem* intensityItem);

private:
    struct Projection {
        double axis_value; //!< value on axis where projection has been made
        QVector<double> bin_values;
    };

    struct ProjectionsData {
        bool is_horizontal;
        QVector<double> bin_centers;
        QVector<Projection> projections;
    };

    QString projectionsToString(const QString& projectionsType, IntensityDataItem* intensityItem);

    std::unique_ptr<Histogram2D> m_hist2d;
    ProjectionsData projectionsData(const QString& projectionsType,
                                            IntensityDataItem* intensityItem);
    QVector<SessionItem*> projectionItems(const QString& projectionsType,
                                          IntensityDataItem* intensityItem);

    QString projectionFileHeader(ProjectionsData& projectionsData);
};

#endif  // SAVEPROJECTIONSASSISTANT_H
