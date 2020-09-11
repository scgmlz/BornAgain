// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionXML.cpp
//! @brief     Implements reader and writer classes for SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ComboProperty.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/GroupItemController.h"
#include "GUI/coregui/Models/ItemFactory.h"
#include "GUI/coregui/Models/SessionItemTags.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include "GUI/coregui/utils/MessageService.h"
#include <QtCore/QXmlStreamWriter>

namespace
{
const QString bool_type_name = "bool";
const QString double_type_name = "double";
const QString int_type_name = "int";
const QString uint_type_name = "uint";
const QString qstring_type_name = "QString";

void report_error(MessageService* messageService, SessionItem* item, const QString& message);

SessionItem* createItem(SessionItem* item, const QString& modelType, const QString& tag);
} // namespace

void SessionXML::writeTo(QXmlStreamWriter* writer, SessionItem* parent)
{
    writer->writeStartElement(parent->model()->getModelTag());
    writer->writeAttribute(SessionXML::ModelNameAttribute, parent->model()->getModelName());

    writeItemAndChildItems(writer, parent);

    writer->writeEndElement(); // m_model_tag
}

void SessionXML::writeItemAndChildItems(QXmlStreamWriter* writer, const SessionItem* item)
{
    if (item->parent()) {
        writer->writeStartElement(SessionXML::ItemTag);
        writer->writeAttribute(SessionXML::ModelTypeAttribute, item->modelType());
        QString tag = item->parent()->tagFromItem(item);
        writer->writeAttribute(SessionXML::TagAttribute, tag);
        writer->writeAttribute(SessionXML::DisplayNameAttribute,
                               item->roleProperty(SessionFlags::DisplayNameRole).toString());
        for (int role : item->getRoles()) {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
                SessionXML::writeVariant(writer, item->value(), role);
        }
    }

    for (auto child : item->children())
        writeItemAndChildItems(writer, child);

    if (item->parent())
        writer->writeEndElement(); // ItemTag
}

void SessionXML::writeVariant(QXmlStreamWriter* writer, QVariant variant, int role)
{
    if (variant.isValid()) {
        writer->writeStartElement(SessionXML::ParameterTag);
        QString type_name = variant.typeName();
        writer->writeAttribute(SessionXML::ParameterTypeAttribute, type_name);
        writer->writeAttribute(SessionXML::ParameterRoleAttribute, QString::number(role));

        if (type_name == double_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toDouble(), 'e', 12));
        } else if (type_name == int_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toInt()));
        } else if (type_name == uint_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toUInt()));
        } else if (type_name == bool_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toBool()));
        } else if (type_name == qstring_type_name) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute, variant.toString());
        } else if (type_name == "ExternalProperty") {
            ExternalProperty prop = variant.value<ExternalProperty>();
            writer->writeAttribute(SessionXML::ExternalPropertyTextAtt, prop.text());

            QString tcol = prop.color().isValid() ? prop.color().name(QColor::HexArgb) : "";
            writer->writeAttribute(SessionXML::ExternalPropertyColorAtt, tcol);
            writer->writeAttribute(SessionXML::ExternalPropertyIdentifierAtt, prop.identifier());
        } else if (type_name == "ComboProperty") {
            ComboProperty combo = variant.value<ComboProperty>();
            writer->writeAttribute(SessionXML::ParameterValueAttribute, combo.stringOfSelections());
            writer->writeAttribute(SessionXML::ParameterExtAttribute, combo.stringOfValues());

        } else {
            throw GUIHelpers::Error("SessionXML::writeVariant: Parameter type not supported "
                                    + type_name);
        }

        writer->writeEndElement(); // end ParameterTag
    }
}

void SessionXML::readItems(QXmlStreamReader* reader, SessionItem* parent, QString topTag,
                           MessageService* messageService)
{
    ASSERT(parent);
    const QString start_type = parent->model()->getModelTag();
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                const QString model_type =
                    reader->attributes().value(SessionXML::ModelTypeAttribute).toString();
                QString tag = reader->attributes().value(SessionXML::TagAttribute).toString();
                QString displayName =
                    reader->attributes().value(SessionXML::DisplayNameAttribute).toString();

                if (!topTag.isEmpty()) {
                    // to handle copying of item to another parent
                    tag = topTag;
                    topTag.clear();
                }
                auto newItem = createItem(parent, model_type, tag);
                if (!newItem) {
                    QString message = QString("Error while parsing XML. Can't create item of "
                                              "modelType '%1' for tag '%2'")
                                          .arg(model_type, tag);
                    report_error(messageService, parent, message);
                    // risky attempt to recover the rest of the project
                    reader->skipCurrentElement();
                } else {
                    parent = newItem;
                    parent->setDisplayName(displayName);
                }
            } else if (reader->name() == SessionXML::ParameterTag) {
                SessionXML::readProperty(reader, parent, messageService);
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag && parent)
                parent = parent->parent();

            if (reader->name() == start_type)
                break;
        }
    }
}

QString SessionXML::readProperty(QXmlStreamReader* reader, SessionItem* item,
                                 MessageService* messageService)
{
    const QString parameter_name =
        reader->attributes().value(SessionXML::ParameterNameAttribute).toString();
    const QString parameter_type =
        reader->attributes().value(SessionXML::ParameterTypeAttribute).toString();
    const int role = reader->attributes().value(SessionXML::ParameterRoleAttribute).toInt();

    if (!item) {
        QString message =
            QString("Attempt to set property '%1' for non existing item").arg(parameter_name);
        report_error(messageService, item, message);
        return parameter_name;
    }

    QVariant variant;
    if (parameter_type == double_type_name) {
        double parameter_value =
            reader->attributes().value(SessionXML::ParameterValueAttribute).toDouble();
        variant = parameter_value;
    } else if (parameter_type == int_type_name) {
        int parameter_value =
            reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        variant = parameter_value;
    } else if (parameter_type == uint_type_name) {
        unsigned parameter_value =
            reader->attributes().value(SessionXML::ParameterValueAttribute).toUInt();
        variant = parameter_value;
    } else if (parameter_type == bool_type_name) {
        bool parameter_value =
            reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        variant = parameter_value;
    } else if (parameter_type == qstring_type_name) {
        QString parameter_value =
            reader->attributes().value(SessionXML::ParameterValueAttribute).toString();
        variant = parameter_value;
    } else if (parameter_type == "ExternalProperty") {
        QString text = reader->attributes().value(SessionXML::ExternalPropertyTextAtt).toString();
        QString colorName =
            reader->attributes().value(SessionXML::ExternalPropertyColorAtt).toString();
        QString identifier =
            reader->attributes().value(SessionXML::ExternalPropertyIdentifierAtt).toString();

        ExternalProperty property;
        property.setText(text);
        property.setColor(QColor(colorName));
        property.setIdentifier(identifier);
        variant = property.variant();
    } else if (parameter_type == "ComboProperty") {
        QString selections =
            reader->attributes().value(SessionXML::ParameterValueAttribute).toString();
        QString values = reader->attributes().value(SessionXML::ParameterExtAttribute).toString();

        ComboProperty combo_property;
        combo_property.setStringOfValues(values);
        combo_property.setStringOfSelections(selections);

        variant = combo_property.variant();
    } else {
        QString message = QString("SessionModel::readProperty: parameter type not supported '"
                                  + parameter_type + "'");
        throw GUIHelpers::Error(message);
    }

    if (variant.isValid()) {
        item->setRoleProperty(role, variant);
    }

    return parameter_name;
}

namespace
{
void report_error(MessageService* messageService, SessionItem* item, const QString& message)
{
    if (messageService) {
        messageService->send_warning(item->model(), message);
    } else {
        throw GUIHelpers::Error(QString("Warning: ") + message);
    }
}

SessionItem* createItem(SessionItem* item, const QString& modelType, const QString& tag)
{
    SessionItem* result(nullptr);

    if (item->modelType() == "GroupProperty") {
        if (auto groupItem = dynamic_cast<GroupItem*>(item))
            result = groupItem->getItemOfType(modelType);
    } else {
        if (item->sessionItemTags()->isSingleItemTag(tag)) {
            result = item->getItem(tag);
        } else {
            try {
                result = item->model()->insertNewItem(modelType, item->index(), -1, tag);
            } catch (const std::exception&) {
                result = nullptr; // error will be reported later
            }
        }
    }
    return result;
}
} // namespace
