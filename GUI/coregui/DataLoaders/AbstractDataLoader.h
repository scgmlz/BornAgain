//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AbstractDataLoader.h
//! @brief     Defines class AbstractDataLoader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_DATALOADERS_ABSTRACTDATALOADER_H
#define BORNAGAIN_GUI_COREGUI_DATALOADERS_ABSTRACTDATALOADER_H

class QString;
class QByteArray;
class QGroupBox;
class QCustomPlot;
class QTableWidget;
class RealDataItem;

#include <QtCore>

class AbstractDataLoader : public QObject {
    Q_OBJECT
public:
    virtual ~AbstractDataLoader() = default;

    //! The name shown in the format selection combo
    virtual QString name() const = 0;

    //! Info about what this loader does. Is shown on the import dialog pane
    virtual QString info() const;

    //! Fills the widget on the import dialog pane. This base class does nothing (=> no editable
    //! properties)
    virtual void populatePropertiesWidget(QWidget* parent);

    //! Read all values from the properties UI into the internal variables
    virtual void applyProperties();

    virtual void initWithDefaultProperties();

    virtual QString persistentClassName() const = 0;

    virtual AbstractDataLoader* clone() const = 0;

    //! Returns every internal setting so it can be restored completely
    virtual QByteArray serialize() const;

    //! #baTODO: how to deliver errors? VersionException...?
    virtual void deserialize(const QByteArray& data);

    virtual QByteArray defaultProperties() const;

    //! Returns a Qt rich text formatted preview
    virtual QString preview(const QString& filepath, QCustomPlot* plotWidget) const = 0;

    virtual void importFile(const QString& filename, RealDataItem* item, QStringList* errors,
                            QStringList* warnings) const = 0;

    //! Fill the import details table with information from the last call to importFile
    //! return false if not supported.
    //! This base implementation returns false.
    virtual bool fillImportDetailsTable(QTableWidget* table, bool fileContent, bool rawContent,
                                        bool processedContent) const;
signals:
    void propertiesChanged();
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_ABSTRACTDATALOADER_H
