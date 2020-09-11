// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/tooltipdatabase.h
//! @brief     Defines class ToolTipDataBase
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MAINWINDOW_TOOLTIPDATABASE_H
#define BORNAGAIN_GUI_COREGUI_MAINWINDOW_TOOLTIPDATABASE_H

#include "Wrap/WinDllMacros.h"
#include <QMap>
#include <QObject>

//! The MaterialEditor is the main class to access materials.
class BA_CORE_API_ ToolTipDataBase : public QObject
{
    Q_OBJECT
public:
    explicit ToolTipDataBase(QObject* parent = nullptr);
    virtual ~ToolTipDataBase();

    static QString widgetboxToolTip(const QString& className);

private:
    void initDataBase();
    QString getTag(const QString& contextName, const QString& categoryName,
                   const QString& propertyName);
    void addToolTip(const QString& contextName, const QString& categoryName,
                    const QString& propertyName, const QString& tooltip);
    QString this_getToolTip(const QString& contextName, const QString& categoryName,
                            const QString& propertyName);

    static ToolTipDataBase* m_instance;

    static QMap<QString, QString> m_tagToToolTip;
};

#endif // BORNAGAIN_GUI_COREGUI_MAINWINDOW_TOOLTIPDATABASE_H
