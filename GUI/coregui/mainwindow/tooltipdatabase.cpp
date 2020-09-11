// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/tooltipdatabase.cpp
//! @brief     Implements class ToolTipDataBase
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/mainwindow/tooltipdatabase.h"
#include "Core/Basics/Assert.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <QFile>
#include <QXmlStreamReader>

namespace
{
const QString modelTag = "ToolTipsData";
const QString contextTag = "context";
const QString categoryTag = "category";
const QString propertyTag = "property";
const QString tooltipTag = "tooltip";
const QString whatsthisTag = "whatsthis";
const QString nameAttribute = "name";
const QString sampleViewContext = "SampleView";
const QString titleProperty = "Title";
const QString descriptionProperty = "Description";
} // namespace

ToolTipDataBase* ToolTipDataBase::m_instance = 0;
QMap<QString, QString> ToolTipDataBase::m_tagToToolTip = QMap<QString, QString>();

ToolTipDataBase::ToolTipDataBase(QObject* parent) : QObject(parent)
{
    ASSERT(!m_instance);
    m_instance = this;

    initDataBase();
}

ToolTipDataBase::~ToolTipDataBase()
{
    m_instance = 0;
}

QString ToolTipDataBase::widgetboxToolTip(const QString& className)
{
    ASSERT(m_instance);
    QString modelName(className);
    modelName.remove("FormFactor");
    return m_instance->this_getToolTip(sampleViewContext, modelName, titleProperty);
}

void ToolTipDataBase::initDataBase()
{
    QFile file(":/mainwindow/tooltips.xml");
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamReader reader(&file);

    QString contextName, className, propertyName;
    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement: {
            const QStringRef tag = reader.name();
            if (tag == modelTag) {
                continue;
            }
            if (tag == contextTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                contextName = attributes.value(nameAttribute).toString();
                continue;
            }
            if (tag == categoryTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                className = attributes.value(nameAttribute).toString();
                continue;
            }
            if (tag == propertyTag) {
                const QXmlStreamAttributes attributes = reader.attributes();
                propertyName = attributes.value(nameAttribute).toString();
                continue;
            }
            if (tag == tooltipTag) {
                reader.readNext();
                QString toolTip = reader.text().toString();
                addToolTip(contextName, className, propertyName, toolTip);
                continue;
            }
            break;
        }
        case QXmlStreamReader::EndElement: {
            break;
        }
        default:
            break;
        }
    }

    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
}

QString ToolTipDataBase::getTag(const QString& contextName, const QString& categoryName,
                                const QString& propertyName)
{
    return QString("/%1/%2/%3").arg(contextName, categoryName, propertyName);
}

void ToolTipDataBase::addToolTip(const QString& contextName, const QString& categoryName,
                                 const QString& propertyName, const QString& tooltip)
{
    if (!tooltip.isEmpty())
        m_tagToToolTip[getTag(contextName, categoryName, propertyName)] = tooltip;
}

QString ToolTipDataBase::this_getToolTip(const QString& contextName, const QString& categoryName,
                                         const QString& propertyName)
{
    return m_tagToToolTip[getTag(contextName, categoryName, propertyName)];
}
