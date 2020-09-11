// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ItemTreeView.cpp
//! @brief     Implements class ItemTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/ItemTreeView.h"
#include "GUI/coregui/Models/SessionModel.h"
#include <QDragMoveEvent>
#include <QMimeData>
#include <QtCore/QXmlStreamWriter>

ItemTreeView::ItemTreeView(QWidget* parent) : QTreeView(parent)
{

    setAllColumnsShowFocus(true);
    setWindowTitle("Sample Tree View");
    setObjectName("ObjectTree");
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragDropMode(QAbstractItemView::InternalMove);
}

ItemTreeView::~ItemTreeView() {}

void ItemTreeView::dragMoveEvent(QDragMoveEvent* event)
{
    QTreeView::dragMoveEvent(event);
    SessionModel* model = static_cast<SessionModel*>(this->model());
    model->setDraggedItemType(QString());
    QByteArray xml_data = qUncompress(event->mimeData()->data(SessionXML::ItemMimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type =
                    reader.attributes().value(SessionXML::ModelTypeAttribute).toString();
                model->setDraggedItemType(model_type);
                break;
            }
        }
    }
}
