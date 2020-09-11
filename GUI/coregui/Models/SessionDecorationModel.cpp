// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionDecorationModel.cpp
//! @brief     Defines class SessionDecorationModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/SessionDecorationModel.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include <QColor>
#include <QIcon>
#include <QPixmap>

namespace
{

struct IconCatalog {
    QIcon gisasIcon;
    QIcon offspecIcon;
    QIcon specularIcon;
    QIcon depthIcon;

    IconCatalog()
    {
        gisasIcon.addPixmap(QPixmap(":/images/gisas_instrument.svg"), QIcon::Selected);
        gisasIcon.addPixmap(QPixmap(":/images/gisas_instrument_shaded.svg"), QIcon::Normal);
        offspecIcon.addPixmap(QPixmap(":/images/offspec_instrument.svg"), QIcon::Selected);
        offspecIcon.addPixmap(QPixmap(":/images/offspec_instrument_shaded.svg"), QIcon::Normal);
        specularIcon.addPixmap(QPixmap(":/images/specular_instrument.svg"), QIcon::Selected);
        specularIcon.addPixmap(QPixmap(":/images/specular_instrument_shaded.svg"), QIcon::Normal);
        depthIcon.addPixmap(QPixmap(":/images/depth_instrument.svg"), QIcon::Selected);
        depthIcon.addPixmap(QPixmap(":/images/depth_instrument_shaded.svg"), QIcon::Normal);
    }
};

IconCatalog& iconCatalog()
{
    static IconCatalog result;
    return result;
}

QIcon materialIcon(const QColor& color)
{
    QIcon result;
    QPixmap pixmap(10, 10);
    pixmap.fill(color);
    result.addPixmap(pixmap);
    return result;
}

QVariant itemIcon(const SessionItem* item)
{
    QVariant result;

    auto modelType = item->modelType();

    auto& icons = iconCatalog();

    if (modelType == "GISASInstrument") {
        return QVariant(icons.gisasIcon);

    } else if (modelType == "OffSpecInstrument") {
        return QVariant(icons.offspecIcon);

    } else if (modelType == "SpecularInstrument") {
        return QVariant(icons.specularIcon);

    } else if (modelType == "DepthProbeInstrument") {
        return QVariant(icons.depthIcon);

    } else if (modelType == "Material") {
        auto materialItem = dynamic_cast<const MaterialItem*>(item);
        return QVariant(materialIcon(materialItem->color()));
    }

    return result;
}
} // namespace

SessionDecorationModel::SessionDecorationModel(QObject* parent, SessionModel* model)
    : QIdentityProxyModel(parent), m_model(nullptr)
{
    setSessionModel(model);
}

void SessionDecorationModel::setSessionModel(SessionModel* model)
{
    QIdentityProxyModel::setSourceModel(model);
    m_model = model;
}

QVariant SessionDecorationModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DecorationRole) {
        QVariant result = createIcon(index);
        if (result.isValid())
            return result;
    }

    if (role == Qt::TextColorRole) {
        QVariant result = textColor(index);
        if (result.isValid())
            return result;
    }

    return QIdentityProxyModel::data(index, role);
}

QVariant SessionDecorationModel::createIcon(const QModelIndex& index) const
{
    if (SessionItem* item = m_model->itemForIndex(index))
        return itemIcon(item);

    return QVariant();
}

//! Returns text color. Disabled SessionItem's will appear in gray.

QVariant SessionDecorationModel::textColor(const QModelIndex& index) const
{
    QVariant result;

    if (SessionItem* item = m_model->itemForIndex(index)) {
        if (item->isEnabled() == false)
            return QColor(Qt::gray);
    }

    return result;
}
