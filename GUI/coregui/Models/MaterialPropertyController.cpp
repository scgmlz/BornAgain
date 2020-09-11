// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialPropertyController.cpp
//! @brief     Defines MaterialPropertyController class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MaterialPropertyController.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/ModelUtils.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include <QVector>

MaterialPropertyController::MaterialPropertyController(QObject* parent)
    : QObject(parent), m_materialModel(nullptr), m_sampleModel(nullptr)
{
}

void MaterialPropertyController::setModels(MaterialModel* materialModel, SampleModel* sampleModel)
{
    m_materialModel = materialModel;
    m_sampleModel = sampleModel;

    //    connect(m_materialModel, &MaterialModel::dataChanged, this,
    //            &MaterialPropertyController::onMaterialDataChanged);

    //    connect(m_materialModel, &MaterialModel::rowsAboutToBeRemoved, this,
    //            &MaterialPropertyController::onMaterialRowsAboutToBeRemoved);

    connect(m_materialModel, &MaterialModel::modelLoaded, this,
            &MaterialPropertyController::onMaterialModelLoad);
}

//! Special case when original MaterialModel was fully rebuild from MaterialEditor.
//! Full update of MaterialProperties.

void MaterialPropertyController::onMaterialModelLoad()
{
    for (auto sampleItem : relatedSampleItems()) {
        QString tag = MaterialItemUtils::materialTag(*sampleItem);
        ASSERT(!tag.isEmpty());

        ExternalProperty property = sampleItem->getItemValue(tag).value<ExternalProperty>();
        if (MaterialItem* material =
                m_materialModel->materialFromIdentifier(property.identifier())) {
            ExternalProperty new_property = MaterialItemUtils::materialProperty(*material);
            sampleItem->setItemValue(tag, new_property.variant());
        } else {
            ExternalProperty undefined;
            sampleItem->setItemValue(tag, undefined.variant());
        }
    }
}

//! On MaterialItem change: updates corresponding MaterialProperty in sample items.

void MaterialPropertyController::onMaterialDataChanged(const QModelIndex& topLeft,
                                                       const QModelIndex&, const QVector<int>&)
{
    auto changedItem = m_materialModel->itemForIndex(topLeft);
    if (auto materialItem =
            dynamic_cast<const MaterialItem*>(ModelPath::ancestor(changedItem, "Material"))) {

        for (auto sampleItem : relatedSampleItems()) {
            QString tag = MaterialItemUtils::materialTag(*sampleItem);
            ASSERT(!tag.isEmpty());

            ExternalProperty property = sampleItem->getItemValue(tag).value<ExternalProperty>();
            if (property.identifier() == materialItem->identifier()) {
                ExternalProperty new_property = MaterialItemUtils::materialProperty(*materialItem);
                sampleItem->setItemValue(tag, new_property.variant());
            }
        }
    }
}

//! On MaterialItem removal: updates corresponding MaterialProperty in sample items.

void MaterialPropertyController::onMaterialRowsAboutToBeRemoved(const QModelIndex& parent,
                                                                int first, int last)
{
    // looking for top level items (MaterialItems)
    if (parent.isValid())
        return;

    // Building list of material identifiers which will be deleted
    QStringList identifiersToDelete;
    for (int i_row = first; i_row <= last; ++i_row) {
        QModelIndex changed = m_materialModel->index(i_row, 0, parent);
        if (auto material = dynamic_cast<MaterialItem*>(m_materialModel->itemForIndex(changed)))
            identifiersToDelete.push_back(material->identifier());
    }

    // rewriting MaterialProperty in corresponding sample items
    for (auto sampleItem : relatedSampleItems()) {
        QString tag = MaterialItemUtils::materialTag(*sampleItem);
        ASSERT(!tag.isEmpty());

        ExternalProperty property = sampleItem->getItemValue(tag).value<ExternalProperty>();
        if (identifiersToDelete.contains(property.identifier())) {
            ExternalProperty undefined;
            sampleItem->setItemValue(tag, undefined.variant());
        }
    }
}

//! Returns vector of SessionItems having MaterialProperty on board.

QVector<SessionItem*> MaterialPropertyController::relatedSampleItems()
{
    static QStringList materialRelated = MaterialItemUtils::materialRelatedModelTypes();

    QVector<SessionItem*> result;
    ModelUtils::iterate(QModelIndex(), m_sampleModel, [&](const QModelIndex& index) {
        if (index.column() != 0)
            return;

        if (SessionItem* item = m_sampleModel->itemForIndex(index))
            if (materialRelated.contains(item->modelType()))
                result.push_back(item);
    });

    return result;
}
