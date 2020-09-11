// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeUtils.cpp
//! @brief     Implements ParameterTreeUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/ParameterTreeUtils.h"
#include "GUI/coregui/Models/FitParameterHelper.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/ModelPath.h"
#include "GUI/coregui/Models/MultiLayerItem.h"
#include "GUI/coregui/Models/ParameterTreeItems.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QStack>

namespace
{

QString removeLeadingSlash(const QString& name)
{
    return name.indexOf('/') == 0 ? name.mid(1) : name;
}

#ifndef NDEBUG

//! For every ParameterItem in a container creates a link to the domain.

void populateDomainLinks(SessionItem* container)
{
    if (container->modelType() != "Parameter Container")
        throw GUIHelpers::Error("ParameterTreeUtils::populateParameterContainer() -> Error. "
                                "Not a ParameterContainerType.");

    ParameterTreeUtils::visitParameterContainer(container, [container](ParameterItem* parItem) {
        QString translation =
            "*/" + ModelPath::itemPathTranslation(*parItem->linkedItem(), container->parent());
        parItem->setItemValue(ParameterItem::P_DOMAIN, translation);
    });
}

#endif

void handleItem(SessionItem* tree, const SessionItem* source);

} // namespace

void ParameterTreeUtils::createParameterTree(JobItem* jobItem)
{
    SessionItem* container = jobItem->model()->insertNewItem(
        "Parameter Container", jobItem->index(), -1, JobItem::T_PARAMETER_TREE);

    populateParameterContainer(container, jobItem->getItem(JobItem::T_MATERIAL_CONTAINER));

    populateParameterContainer(container, jobItem->getItem(JobItem::T_SAMPLE));

    populateParameterContainer(container, jobItem->getItem(JobItem::T_INSTRUMENT));

#ifndef NDEBUG
    // Provides all items in "JobItem/Parameter Tree Container" with domain links already
    // at the stage of ParameterTree creation. It is necessary for validation, in Release mode
    // it will lead for unnecessary large project files.
    populateDomainLinks(container);
#endif
}

//! Populates ParameterContainer with ParameterItem's corresponding to all properties found
//! in a source item.

void ParameterTreeUtils::populateParameterContainer(SessionItem* container,
                                                    const SessionItem* source)
{
    if (container->modelType() != "Parameter Container")
        throw GUIHelpers::Error("ParameterTreeUtils::populateParameterContainer() -> Error. "
                                "Not a ParameterContainerType.");

    SessionItem* sourceLabel =
        container->model()->insertNewItem("Parameter Label", container->index());

    handleItem(sourceLabel, source);
}

//! Visit all ParameterItem in container and execute user function.

void ParameterTreeUtils::visitParameterContainer(SessionItem* container,
                                                 std::function<void(ParameterItem*)> fun)
{
    SessionItem* current(container);
    QStack<SessionItem*> stack;
    stack.push(current);
    while (!stack.empty()) {
        current = stack.pop();
        if (current->modelType() == "Parameter Label"
            || current->modelType() == "Parameter Container") {
            for (SessionItem* child : current->getItems())
                stack.push(child);
        } else {
            if (ParameterItem* parItem = dynamic_cast<ParameterItem*>(current))
                fun(parItem);
        }
    }
}

//! Creates list with parameter names of source item.

QStringList ParameterTreeUtils::parameterTreeNames(const SessionItem* source)
{
    QStringList result;

    for (auto pair : parameterDictionary(source))
        result << pair.first;

    return result;
}

//! Creates domain translated list of parameter names for source item.

QStringList ParameterTreeUtils::translatedParameterTreeNames(const SessionItem* source)
{
    QStringList result;

    for (auto pair : parameterDictionary(source))
        result << pair.second;

    return result;
}

//! Correspondance of parameter name to translated name for all properties found in source
//! in its children.

QVector<QPair<QString, QString>> ParameterTreeUtils::parameterDictionary(const SessionItem* source)
{
    ASSERT(source);

    QVector<QPair<QString, QString>> result;

    // Create container with ParameterItem's of given source item
    SampleModel model;
    SessionItem* container = model.insertNewItem("Parameter Container");
    populateParameterContainer(container, source);

    // Iterate through all ParameterItems and retrieve necessary data.
    visitParameterContainer(container, [&](ParameterItem* parItem) {
        // TODO replace with the method from ModelPath
        QString parPath = FitParameterHelper::getParameterItemPath(parItem);

        QString relPath =
            source->displayName() + "/" + parItem->getItemValue(ParameterItem::P_LINK).toString();
        SessionItem* linkedItem = ModelPath::getItemFromPath(relPath, source);
        QString translation = ModelPath::itemPathTranslation(*linkedItem, source->parent());

        result.push_back(QPair<QString, QString>(parPath, translation));
    });
    std::reverse(result.begin(), result.end());

    return result;
}

//! Converts domain name to parameterItem name. Parameter name should belong to item or
//! one of its children.

QString ParameterTreeUtils::domainNameToParameterName(const QString& domainName,
                                                      const SessionItem* source)
{
    QString domain = removeLeadingSlash(domainName);
    for (auto pair : parameterDictionary(source)) { // parName, domainName
        if (pair.second == domain)
            return pair.first;
    }

    return {};
}

//! Converts parameter name to domain name. Parameter name should belong to item or
//! one of its children.

QString ParameterTreeUtils::parameterNameToDomainName(const QString& parName,
                                                      const SessionItem* source)
{
    for (auto pair : parameterDictionary(source)) // parName, domainName
        if (pair.first == parName)
            return "/" + pair.second;

    return {};
}

//! Converts parameter item name to the corresponding item in the tree below the source.

SessionItem* ParameterTreeUtils::parameterNameToLinkedItem(const QString& parName,
                                                           const SessionItem* source)
{
    SampleModel model;
    SessionItem* container = model.insertNewItem("Parameter Container");
    populateParameterContainer(container, source);

    // Iterate through all ParameterItems and retrieve necessary data.
    SessionItem* result(nullptr);
    visitParameterContainer(container, [&](ParameterItem* parItem) {
        // TODO replace with the method from ModelPath
        QString parPath = FitParameterHelper::getParameterItemPath(parItem);
        if (parPath == parName) {
            QString relPath = source->displayName() + "/"
                              + parItem->getItemValue(ParameterItem::P_LINK).toString();
            result = ModelPath::getItemFromPath(relPath, source);
        }
    });

    return result;
}

namespace
{

void handleItem(SessionItem* tree, const SessionItem* source)
{
    if (tree->modelType() == "Parameter Label") {
        tree->setDisplayName(source->itemName());

    }

    else if (tree->modelType() == "Parameter") {
        tree->setDisplayName(source->itemName());

        double sourceValue = source->value().toDouble();
        tree->setValue(QVariant(sourceValue));
        QString path = ModelPath::getPathFromIndex(source->index());
        int firstSlash = path.indexOf('/');
        path = path.mid(firstSlash + 1);
        tree->setItemValue(ParameterItem::P_LINK, path);
        tree->setItemValue(ParameterItem::P_BACKUP, sourceValue);
        return;
    }

    else {
        return;
    }

    for (SessionItem* child : source->children()) {
        if (child->isVisible() && child->isEnabled()) {
            if (child->modelType() == "Property") {
                if (child->value().type() == QVariant::Double) {
                    SessionItem* branch = tree->model()->insertNewItem("Parameter", tree->index());
                    handleItem(branch, child);
                }

            } else if (child->modelType() == "GroupProperty") {
                SessionItem* currentItem = dynamic_cast<GroupItem*>(child)->currentItem();
                if (currentItem && currentItem->numberOfChildren() > 0) {
                    SessionItem* branch =
                        tree->model()->insertNewItem("Parameter Label", tree->index());
                    handleItem(branch, currentItem);
                }
            } else {
                SessionItem* branch =
                    tree->model()->insertNewItem("Parameter Label", tree->index());
                handleItem(branch, child);
            }
        }
    }
}

} // namespace
