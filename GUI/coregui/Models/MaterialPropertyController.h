// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialPropertyController.h
//! @brief     Defines MaterialPropertyController class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MATERIALPROPERTYCONTROLLER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MATERIALPROPERTYCONTROLLER_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class MaterialModel;
class SampleModel;
class SessionItem;

//! Listens MaterialModel for changes in MaterialItems and then
//! updates MaterialProperties in all related items in SampleModel.

class BA_CORE_API_ MaterialPropertyController : public QObject
{
    Q_OBJECT
public:
    MaterialPropertyController(QObject* parent = nullptr);

    void setModels(MaterialModel* materialModel, SampleModel* sampleModel);

public slots:
    void onMaterialModelLoad();

private slots:
    void onMaterialDataChanged(const QModelIndex& topLeft, const QModelIndex&, const QVector<int>&);
    void onMaterialRowsAboutToBeRemoved(const QModelIndex& parent, int first, int last);

private:
    QVector<SessionItem*> relatedSampleItems();

    MaterialModel* m_materialModel;
    SampleModel* m_sampleModel;
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MATERIALPROPERTYCONTROLLER_H
