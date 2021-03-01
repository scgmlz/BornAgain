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

//! Base class for all data loaders (classes which can import real data)

class AbstractDataLoader : public QObject {
    Q_OBJECT
public:
    virtual ~AbstractDataLoader() = default;

    //! The name shown in the format selection combo
    virtual QString name() const = 0;

    //! Info about what this loader does. Is shown on the import dialog pane
    virtual QString info() const;

    //! Fills the widget on the import dialog pane. This base class' implementation does nothing
    //! (meaning "no editable properties")
    virtual void populatePropertiesWidget(QWidget* parent);

    //! Read all values from the properties UI into the internal variables
    virtual void applyProperties();

    //! Set import settings to defaults
    virtual void initWithDefaultProperties();

    //! A name which can be used for save/load purposes (which will not change ever more)
    virtual QString persistentClassName() const = 0;

    //! Create a complete clone, including all internal states
    virtual AbstractDataLoader* clone() const = 0;

    //! Returns every internal setting so it can be restored completely
    virtual QByteArray serialize() const;

    //! Initialize from serialization data
    // #baimport: how to deliver errors? VersionException...?
    virtual void deserialize(const QByteArray& data);

    //! Return the default import settings
    // #baimport Rename?
    virtual QByteArray defaultProperties() const;

    //! Plots the graph as a preview
    virtual void previewOfGraph(QCustomPlot* plotWidget) const = 0;

    //! Import the given file, write the imported data in the realDataItem
    virtual void importFile(const QString& filename, RealDataItem* item, QStringList* errors,
                            QStringList* warnings) const = 0;

    //! Fill the import details table with information from the last call to importFile
    //! return false if not supported.
    //! This base implementation returns false.
    virtual bool fillImportDetailsTable(QTableWidget* table, bool fileContent, bool rawContent,
                                        bool processedContent) const;
signals:
    //! Emitted whenever an import setting changed
    // #baimport Rename?
    void propertiesChanged();
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_ABSTRACTDATALOADER_H
