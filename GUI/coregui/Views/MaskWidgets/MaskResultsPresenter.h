// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskResultsPresenter.h
//! @brief     Defines class MaskResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKRESULTSPRESENTER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKRESULTSPRESENTER_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorFlags.h"
#include "Wrap/WinDllMacros.h"
#include <QModelIndex>
#include <QObject>
#include <memory>

class SessionModel;
class IntensityDataItem;
template <class T> class OutputData;

//! Updates bin values inside IntensityData to display current mask state. Returns IntensityData
//! to original state when requested.

class BA_CORE_API_ MaskResultsPresenter : public QObject
{
public:
    MaskResultsPresenter(QWidget* parent = 0);

    void setMaskContext(SessionModel* maskModel, const QModelIndex& maskContainerIndex,
                        IntensityDataItem* intensityItem);

    void resetContext();

    void updatePresenter(MaskEditorFlags::PresentationType mode);

private:
    void setShowMaskMode();
    void setOriginalMode();
    void backup_data();
    OutputData<double>* createMaskPresentation() const;

    SessionModel* m_maskModel;
    QModelIndex m_maskContainerIndex;
    IntensityDataItem* m_intensityDataItem;
    std::unique_ptr<OutputData<double>> m_dataBackup;
    bool m_interpolation_flag_backup;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_MASKRESULTSPRESENTER_H
