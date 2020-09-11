// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ExtendedDetectorDialog.h
//! @brief     Defines class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_EXTENDEDDETECTORDIALOG_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_EXTENDEDDETECTORDIALOG_H

#include <QDialog>

class MaskEditor;
class DetectorItem;
class DetectorMaskDelegate;
class InstrumentModel;

//! The dialog which shows a MaskEditor

class ExtendedDetectorDialog : public QDialog
{
    Q_OBJECT

public:
    ExtendedDetectorDialog(QWidget* parent = nullptr);

public slots:
    void setDetectorContext(InstrumentModel* instrumentModel, DetectorItem* detectorItem);

private:
    void reject();

private:
    void readSettings();
    void writeSettings();

    MaskEditor* m_maskEditor;
    DetectorMaskDelegate* m_maskDelegate;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_INSTRUMENTWIDGETS_EXTENDEDDETECTORDIALOG_H
