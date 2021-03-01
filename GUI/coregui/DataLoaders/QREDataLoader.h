//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/QREDataLoader.h
//! @brief     Defines class QREDataLoader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef GUI_COREGUI_DATALOADERS_QREDATALOADER_H
#define GUI_COREGUI_DATALOADERS_QREDATALOADER_H

#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"
#include <QVector>

class QString;
class QREDataLoaderProperties;

//! Real data loader for Q/R/E reflectometry CSV files

class QREDataLoader : public AbstractDataLoader1D {
public:
    QREDataLoader();
    virtual QString name() const override;
    virtual QString info() const override;
    virtual QString persistentClassName() const override;
    virtual void previewOfGraph(QCustomPlot* plotWidget) const override;
    virtual void populatePropertiesWidget(QWidget* parent) override;
    virtual void initWithDefaultProperties() override;
    virtual void applyProperties() override;
    virtual QByteArray serialize() const override;
    virtual void deserialize(const QByteArray& data) override;
    virtual AbstractDataLoader* clone() const override;
    virtual void importFile(const QString& filename, RealDataItem* item, QStringList* errors,
                            QStringList* warnings) const override;
    virtual bool fillImportDetailsTable(QTableWidget* table, bool fileContent, bool rawContent,
                                        bool processedContent) const override;
    void guessSettings(const QString& filename);

private:
    void parseFile(QString& fileContent) const;
    void calculateFromParseResult() const;
    void createOutputDataFromParsingResult(RealDataItem* item) const;

private:
    enum class UnitInFile { none, perNanoMeter, perAngstrom, other };

    struct ColumnDefinition {
        bool enabled;    //< shall data type be used
        int column;      //< read the value from this raw column
        UnitInFile unit; //< the unit of the data in the file
        double factor;   //< in case the raw data shall be multiplied

        bool operator==(const ColumnDefinition& other) const;
    };

    enum class DataType { Q, R, dR };

    //! Settings for importing the file
    struct ImportSettings {
        QString separator;    //!< column separator
        QString headerPrefix; //!< prefix denoting header line
        QString linesToSkip;  //!< pattern denoting line to skip (i.e. '1,10-12,42')
        QMap<DataType, ColumnDefinition> columnDefinitions;

        bool operator!=(const ImportSettings& other) const;
        QByteArray toByteArray() const;
        bool fromByteArray(const QByteArray& data);
    } m_importSettings;

    //! Result of the file parsing.
    struct ParsingResult {
        void clear();
        void clearCalculatedValues();
        QVector<QPair<bool, QString>> lines; // bool describes whether line is skipped
        QVector<QPair<int, QVector<double>>> originalEntriesAsDouble;
        QVector<QPair<int, double>> qValues;
        QVector<QPair<int, double>> rValues;
        QVector<QPair<int, double>> eValues;
        int maxColumnCount;
        QByteArray hashOfFile;
        QMap<int, QString> calculationErrors; // calculation error per line
        QStringList warnings;
        ImportSettings importSettings;
    };
    mutable ParsingResult m_importResult;

    QPointer<QREDataLoaderProperties> m_propertiesWidget;
};

#endif // GUI_COREGUI_DATALOADERS_QREDATALOADER_H
