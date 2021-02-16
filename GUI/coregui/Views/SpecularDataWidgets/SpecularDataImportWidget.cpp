//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataImportWidget.cpp
//! @brief     Implements class SpecularDataImportWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/SpecularDataWidgets/SpecularDataImportWidget.h"
#include "GUI/coregui/DataLoaders/QREDataLoader.h"
#include "GUI/coregui/DataLoaders/AbstractDataLoader.h"
#include "GUI/coregui/DataLoaders/AbstractDataLoader1D.h"
#include "GUI/coregui/DataLoaders/DataLoaders1D.h"
#include "GUI/coregui/Models/DataItemUtils.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Models/SpecularDataItem.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/mainwindow/projectmanager.h"
#include "ui_SpecularDataImportWidget.h"
#include <QAction>
#include <QBoxLayout>
#include <QFileDialog>
#include <QMenu>
#include <QStringListModel>
#include <QTextStream>
#include <QTimer>

SpecularDataImportWidget::SpecularDataImportWidget(QWidget* parent)
    : SessionItemWidget(parent), m_ui(new Ui::SpecularDataImportWidget)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_ui->setupUi(this);

    if (DataLoaders1D::instance().loaders().isEmpty())
        DataLoaders1D::instance().initBuiltInLoaders();

    m_ui->tabWidget->removeTab(0);
    m_ui->tabWidget->removeTab(0);

    fillLoaderCombo();
    updatePropertiesEdits();

    connect(m_ui->formatSelectionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SpecularDataImportWidget::onFormatSelectionChanged);
    connect(m_ui->createNewFormatButton, &QPushButton::clicked, this,
            &SpecularDataImportWidget::onCreateNewFormatButton);

    connect(m_ui->originalRowCheckBox, &QCheckBox::stateChanged, this,
            &SpecularDataImportWidget::updatePreview);

    connect(m_ui->rawDataCheckBox, &QCheckBox::stateChanged, this,
            &SpecularDataImportWidget::updatePreview);

    connect(m_ui->calculatedDataCheckBox, &QCheckBox::stateChanged, this,
            &SpecularDataImportWidget::updatePreview);
}

void SpecularDataImportWidget::setItem(SessionItem* _realDataItem)
{
    SessionItemWidget::setItem(_realDataItem);
    updatePreview();

    QByteArray a = realDataItem()->importSettings();
    QDataStream s(a);
    QString filename;
    QString persistentLoaderClassName;
    QByteArray loaderSettings;
    s >> filename;
    s >> persistentLoaderClassName;
    s >> loaderSettings;

    for (auto loader : DataLoaders1D::instance().loaders())
        if (persistentLoaderClassName == loader->persistentClassName()) {
            m_ui->formatSelectionComboBox->setCurrentText(loader->name());
            m_loader.reset(
                DataLoaders1D::instance().createFromPersistentName(persistentLoaderClassName));
            m_loader->deserialize(loaderSettings);
        }

    m_ui->fileNameEdit->setText(QDir::toNativeSeparators(filename));

    QSignalBlocker b(m_ui->formatSelectionComboBox);
    m_ui->formatSelectionComboBox->setCurrentText(m_loader->name());

    updatePropertiesEdits();
    updatePreview();
    connect(m_loader.get(), &AbstractDataLoader::propertiesChanged, this,
            &SpecularDataImportWidget::onPropertiesChanged);
}

QList<QAction*> SpecularDataImportWidget::actionList()
{
    return {};
}

void SpecularDataImportWidget::onContextMenuRequest(const QPoint& point)
{
    QMenu menu;
    for (auto action : actionList())
        menu.addAction(action);
    menu.exec(point);
}

SpecularDataItem* SpecularDataImportWidget::specularDataItem()
{
    return DataItemUtils::specularDataItem(currentItem());
}

const RealDataItem* SpecularDataImportWidget::realDataItem() const
{
    return dynamic_cast<const RealDataItem*>(currentItem());
}

RealDataItem* SpecularDataImportWidget::realDataItem()
{
    return dynamic_cast<RealDataItem*>(currentItem());
}

void SpecularDataImportWidget::fillLoaderCombo()
{
    QSignalBlocker b(m_ui->formatSelectionComboBox);
    m_ui->formatSelectionComboBox->clear();
    for (auto loader : DataLoaders1D::instance().recentlyUsedLoaders()) {
        m_ui->formatSelectionComboBox->addItem(loader->name());
    }
    for (auto loader : DataLoaders1D::instance().loaders()) {
        m_ui->formatSelectionComboBox->addItem(loader->name());
    }
}

void SpecularDataImportWidget::updatePropertiesEdits()
{
    for (auto child : m_ui->propertiesWidget->children()) {
        delete child;
    }

    if (m_ui->propertiesWidget->layout())
        delete m_ui->propertiesWidget->layout();

    if (m_loader) {
        m_loader->populatePropertiesWidget(m_ui->propertiesWidget);
    }

    const bool hasChildren = !m_ui->propertiesWidget->children().empty();

    m_ui->propertiesWidget->setVisible(hasChildren);
}

AbstractDataLoader* SpecularDataImportWidget::selectedLoader()
{
    const QString name = m_ui->formatSelectionComboBox->currentText();

    for (auto loader : DataLoaders1D::instance().loaders())
        if (name == loader->name())
            return loader;

    return nullptr;
}

void SpecularDataImportWidget::onFormatSelectionChanged()
{
    // #TODO: disconnect() old loader?
    m_loader.reset(dynamic_cast<AbstractDataLoader1D*>(selectedLoader()->clone()));

    m_loader->initWithDefaultProperties();
    updatePropertiesEdits();
    updatePreview();
    applyProperties();
    connect(m_loader.get(), &AbstractDataLoader::propertiesChanged, this,
            &SpecularDataImportWidget::updatePreview);
}

void SpecularDataImportWidget::updatePreview()
{
    m_ui->infoBrowser->clear();
    m_ui->fileContent->clear();
    m_ui->plotWidget->clearGraphs();

    if (m_loader && !currentFileName().isEmpty()) {
        m_ui->infoBrowser->setHtml(m_loader->preview(currentFileName(), m_ui->plotWidget));

        QFile file(currentFileName());
        if (file.open(QFile::ReadOnly))
            m_ui->fileContent->setText(QTextStream(&file).readAll());
    }

    m_ui->plotWidget->replot();

    fillPreviewOnlyForPresentation();
}

void SpecularDataImportWidget::onCreateNewFormatButton()
{
    bool ok;
    QString name = QInputDialog::getText(
        this, "New format", "Please enter a name for the new format", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty())
        return;

    DataLoaders1D::instance().cloneAsUserDefinedLoader(m_loader.get(), name);

    fillLoaderCombo();
    m_ui->formatSelectionComboBox->setCurrentText(name);
    onFormatSelectionChanged();
}

void SpecularDataImportWidget::onPropertiesChanged()
{
    m_loader->applyProperties(); // #TODO: may be duplicate
    applyProperties();
    updatePreview();
}

QString SpecularDataImportWidget::currentFileName() const
{
    QByteArray a = realDataItem()->importSettings();
    QDataStream s(a);
    QString filename;
    s >> filename;
    return filename;
}

void SpecularDataImportWidget::applyProperties()
{
    QByteArray a1 = realDataItem()->importSettings();
    QDataStream s1(a1);
    QString filename;
    s1 >> filename;

    QByteArray a;
    QDataStream s(&a, QIODevice::WriteOnly);
    s << filename;
    s << m_loader->persistentClassName();
    s << m_loader->serialize();
    realDataItem()->setImportSettings(a);
}

void SpecularDataImportWidget::fillPreviewOnlyForPresentation()
{
    /*
    try {
        bool showErrorColumn = false;
        double f1 = 1;
        double f2 = 1;
        double f3 = 1;
        auto loader = dynamic_cast<QREDataLoader*>(m_loader.get());
        QString qUnit = "";

        if (loader != nullptr) {
            showErrorColumn =
                loader->m_columnDefinitions[QREDataLoader::DataType::dR].enabled;
            f1 = loader->m_columnDefinitions[QREDataLoader::DataType::Q].factor;
            f2 = loader->m_columnDefinitions[QREDataLoader::DataType::R].factor;
            f3 = loader->m_columnDefinitions[QREDataLoader::DataType::dR].factor;
            qUnit =
                " ["
                + loader->m_columnDefinitions[QREDataLoader::DataType::Q].unit
                + "]";
        }

        auto t = m_ui->dataTable;
        t->clear();

        int colCount = 0;
        if (m_ui->originalRowCheckBox->isChecked())
            colCount++;

        if (m_ui->rawDataCheckBox->isChecked())
            colCount += 4;

        if (m_ui->calculatedDataCheckBox->isChecked())
            colCount += showErrorColumn ? 3 : 2;

        t->setColumnCount(colCount);
        t->setRowCount(m_ui->originalRowCheckBox->isChecked() ? 7 : 5);

        const auto fillColumn = [t](int col, QStringList content) {
            int row = 0;
            for (auto s : content) {
                t->setItem(row++, col, new QTableWidgetItem(s));
            }
        };

        const auto cell = [t](int row, int col, double s) {
            t->setItem(row, col, new QTableWidgetItem(QString::number(s)));
        };

        QStringList o;
        o << "// This file is for testing only"
          << "// Q[1/nm]   R   error"
          << "1 10.1 0.1 30.1"
          << "2 15 0.5 30.2"
          << "3 9.3 0.3 30.3"
          << "4 8.4 0.4 30.4"
          << "5 8.4 0.1 30.4";

        QVector<QVector<double>> values;
        values << QVector<double>({
            1,
            10.1,
            0.1,
            30.1,
        });
        values << QVector<double>({
            2,
            15,
            0.5,
            30.2,
        });
        values << QVector<double>({
            3,
            9.3,
            0.3,
            30.3,
        });
        values << QVector<double>({
            4,
            8.4,
            0.4,
            30.4,
        });
        values << QVector<double>({
            5,
            8.4,
            0.1,
            30.4,
        });

        int dataCol = 0;
        int dataRow = 0;
        if (m_ui->originalRowCheckBox->isChecked()) {
            t->setHorizontalHeaderItem(0, new QTableWidgetItem("File content (text)"));
            fillColumn(0, o);
            dataRow = 2;
            dataCol = 1;
        }

        if (m_ui->rawDataCheckBox->isChecked()) {
            t->setHorizontalHeaderItem(dataCol + 0, new QTableWidgetItem("Column 1 raw"));
            t->setHorizontalHeaderItem(dataCol + 1, new QTableWidgetItem("Column 2 raw"));
            t->setHorizontalHeaderItem(dataCol + 2, new QTableWidgetItem("Column 3 raw"));
            t->setHorizontalHeaderItem(dataCol + 3, new QTableWidgetItem("Column 4 raw"));
            for (auto rowContent : values) {
                for (auto v : rowContent)
                    cell(dataRow, dataCol++, v);
                dataRow++;
                dataCol -= rowContent.size();
            }
            dataRow -= values.size();
            dataCol += values.first().size();
        }

        if (m_ui->calculatedDataCheckBox->isChecked()) {
            t->setHorizontalHeaderItem(dataCol, new QTableWidgetItem("Q" + qUnit));
            t->setHorizontalHeaderItem(dataCol + 1, new QTableWidgetItem("R"));
            if (showErrorColumn)
                t->setHorizontalHeaderItem(dataCol + 2, new QTableWidgetItem("E"));

            if (loader) {
                for (auto rowContent : values) {
                    double Q = rowContent
                        [loader->m_columnDefinitions[QREDataLoader::DataType::Q]
                             .column];
                    Q *= loader->m_columnDefinitions[QREDataLoader::DataType::Q]
                             .factor;

                    double R = rowContent
                        [loader->m_columnDefinitions[QREDataLoader::DataType::R]
                             .column];
                    R *= loader->m_columnDefinitions[QREDataLoader::DataType::R]
                             .factor;

                    double E = rowContent
                        [loader->m_columnDefinitions[QREDataLoader::DataType::dR]
                             .column];
                    E *= loader->m_columnDefinitions[QREDataLoader::DataType::dR]
                             .factor;

                    cell(dataRow, dataCol, Q);
                    cell(dataRow, dataCol + 1, R);
                    if (showErrorColumn)
                        cell(dataRow, dataCol + 2, E);

                    dataRow++;
                }
            }
        }

        t->resizeColumnsToContents();
    } catch (...) {
    }
    */
}
