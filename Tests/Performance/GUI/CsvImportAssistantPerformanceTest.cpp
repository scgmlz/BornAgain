// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Performance/GUI/CsvImportAssistantPerformanceTest.cpp
//! @brief     Implements GUI performance functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Performance/GUI/CsvImportAssistantPerformanceTest.h"
#include "Core/InputOutput/OutputDataReadFactory.h"
#include "Core/InputOutput/OutputDataWriteFactory.h"
#include "Core/Intensity/ArrayUtils.h"
#include "GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/CsvImportAssistant.h"
#include <ctime>
#include <iostream>

void CsvImportAssistantPerformanceTest::writeTestFile()
{
    remove(m_testFilename.c_str());
    OutputDataWriter* writer = OutputDataWriteFactory::getWriter(m_testFilename);
    OutputData<double>* data = ArrayUtils::createData(m_testVector).release();
    writer->writeOutputData(*data);
}

void CsvImportAssistantPerformanceTest::writeTestFile(size_t nRows, size_t nCols)
{
    remove(m_testFilename.c_str());
    std::ofstream myfile;
    myfile.open(m_testFilename);
    for (size_t i = 0; i < nRows; i++) {
        for (size_t j = 0; j < nCols; j++) {
            myfile << nCols * i + j << " ";
        }
        myfile << "\n";
    }
    myfile.close();
}

OutputData<double>* CsvImportAssistantPerformanceTest::readTestFile()
{
    OutputDataReader* reader = OutputDataReadFactory::getReader(m_testFilename);
    OutputData<double>* data = reader->getOutputData();
    return data;
}

bool CsvImportAssistantPerformanceTest::runTest()
{
    std::cout << "CsvImportAssistantPerformanceTest -> Running ..." << std::endl;
    size_t maxRows = 1000;
    size_t maxCols = 1000;

    for (size_t nRows = 10; nRows <= maxRows; nRows *= 10) {
        for (size_t nCols = 10; nCols <= maxCols; nCols *= 10) {

            // Write test file
            writeTestFile(nRows, nCols);

            // Time the process of reading and importing data:
            std::clock_t c_start = std::clock();

            // Reading and setting data to import:
            CsvImportAssistant assistant(testFilename());
            assistant.setIntensityColumn(1);
            assistant.setCoordinateColumn(9, AxesUnits::DEGREES);
            assistant.setFirstRow(1);
            assistant.setLastRow(int(nRows));

            // Importing of data:
            // If something goes wrong, this line may make the test fail or even crash.
            // The correctness of the reading is tested in test_readFile.
            std::vector<double> RawDataVec =
                assistant.getData().intensityData()->getRawDataVector();
            if (RawDataVec.size() != nRows)
                return false;

            // Report on the test time:
            std::clock_t c_end = std::clock();
            double_t time_spent = 1000.0 * double_t(c_end - c_start) / double_t(CLOCKS_PER_SEC);
            std::cout << "nRows: " << nRows << "; nCols: " << nCols << "; time: " << time_spent
                      << " ms\n"
                      << std::flush;
        }
    }
    return true;
}

int main()
{
    return !CsvImportAssistantPerformanceTest().runTest();
}
