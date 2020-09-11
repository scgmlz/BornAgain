// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerMimeData.h
//! @brief     Defines class DesignerMimeData
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_DESIGNERMIMEDATA_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_DESIGNERMIMEDATA_H

#include "Wrap/WinDllMacros.h"
#include <QMimeData>

class QDrag;
class QXmlStreamReader;

//! Mime data for use with SampleDesigner drag and drop operations
class BA_CORE_API_ DesignerMimeData : public QMimeData
{
    Q_OBJECT
public:
    DesignerMimeData(const QString& name, const QString& xmldescr, QDrag* drag);
    virtual ~DesignerMimeData() {}

    //! Execute a drag and drop operation.
    static Qt::DropAction execDrag(const QString& name, const QString& xmldescr,
                                   QWidget* dragSource);

    QString getClassName() const { return m_classname; }

private:
    void read_xmldescr(const QString& xmldescr);
    void read_widget(QXmlStreamReader& reader);

    QPixmap getPixmap(const QString& name);

    QString m_entryname;
    QString m_xmldescr;
    QString m_classname;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_DESIGNERMIMEDATA_H
