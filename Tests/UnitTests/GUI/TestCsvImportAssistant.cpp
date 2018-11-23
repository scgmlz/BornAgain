#include "google_test.h"
#include "ArrayUtils.h"
#include "JobItemUtils.h"
#include "SpecularDataItem.h"
#include "AxisNames.h"
#include "OutputDataWriteFactory.h"
#include "OutputDataReadFactory.h"
#include "CsvImportAssistant.h"
#include <vector>

class TestCsvImportAssistant :  public ::testing::Test
{
protected:
    ~TestCsvImportAssistant();

    const std::string m_testFilename= "tmp_TestCsvImportAssistant.txt";
    const std::vector<std::vector<double>> m_testVector = {
             {0.0,   1.0,  2.0,  3.0}
            ,{4.0,   5.0,  6.0,  7.0}
            ,{8.0,   9.0, 10.0, 11.0}
            ,{12.0, 13.0, 14.0, 15.0}
            ,{16.0, 17.0, 18.0, 19.0}
            ,{20.0, 21.0, 22.0, 23.0}
    };


    const QString testFilename(){return QString::fromStdString(m_testFilename);}

    void writeTestFile(){
        remove(m_testFilename.c_str());
        OutputDataWriter* writer = OutputDataWriteFactory::getWriter(m_testFilename);
        OutputData<double>* data = ArrayUtils::createData2D(m_testVector).release();
        writer->writeOutputData(*data);
    }

    void writeTestFile(size_t nRows, size_t nCols){
        remove(m_testFilename.c_str());
        std::ofstream myfile;
        myfile.open (m_testFilename);
        for(size_t i = 0 ; i < nRows; i++){
            for(size_t j = 0 ; j < nCols; j++){
                myfile << nCols*i+j << " ";
            }
            myfile << "\n";
        }
        myfile.close();
    }


    OutputData<double>* readTestFile(){
        OutputDataReader* reader = OutputDataReadFactory::getReader(m_testFilename);
        OutputData<double>* data = reader->getOutputData();
        return data;
    }
};

TestCsvImportAssistant::~TestCsvImportAssistant() = default;

//! Testing component items of particle item.
TEST_F(TestCsvImportAssistant, test_readFile)
{
/*
 * The file to read looks like this ['-' symbols added to clarify what is going on].
 * It has originaly ten columns, not four (The separator is a space).
 * When the separator is a space, repeated spaces will be merged into one.
 * Thus, the ImportAssistant will read this file as a four-column file.
# - BornAgain - Intensity - Data -  -  -  -  -  -  -
# - Simple - 2D - array - suitable - for - numpy, - matlab - etc. -  -
# - [nrows=6, - ncols=4] -  -  -  -  -  -  -  -
0.000000000000e+00 -  -  -  - 1.000000000000e+00 -  -  -  - 2.000000000000e+00 - 3.000000000000e+00 -
4.000000000000e+00 -  -  -  - 5.000000000000e+00 -  -  -  - 6.000000000000e+00 - 7.000000000000e+00 -
8.000000000000e+00 -  -  -  - 9.000000000000e+00 -  -  -  - 1.000000000000e+01 - 1.100000000000e+01 -
1.200000000000e+01 -  -  -  - 1.300000000000e+01 -  -  -  - 1.400000000000e+01 - 1.500000000000e+01 -
1.600000000000e+01 -  -  -  - 1.700000000000e+01 -  -  -  - 1.800000000000e+01 - 1.900000000000e+01 -
2.000000000000e+01 -  -  -  - 2.100000000000e+01 -  -  -  - 2.200000000000e+01 - 2.300000000000e+01 -
Number of Columns: 10
Separator: >>> <<<
*/
    writeTestFile();

    CsvImportAssistant assistant(testFilename());

    assistant.setIntensityColumn(1);
    assistant.setCoordinateColumn(3,AxesUnits::DEGREES);
    assistant.setFirstRow(5);
    assistant.setLastRow(7);

    auto DataRank = assistant.getData().dataRank();
    auto AllocSize = assistant.getData().intensityData()->getAllocatedSize();
    auto RawDataVec = assistant.getData().intensityData()->getRawDataVector();
    auto UnitsLabel = assistant.getData().unitsLabel();
    auto AxisLabel0= assistant.getData().axisLabel(0);
    auto AxisLabel1= assistant.getData().axisLabel(1);

    const std::vector<double> expected = { 4.0, 8.0, 12.0};

    EXPECT_EQ(DataRank, 1u);
    EXPECT_EQ(AllocSize, 3u);
    EXPECT_EQ(RawDataVec, expected);
    EXPECT_EQ(UnitsLabel, JobItemUtils::nameFromAxesUnits(AxesUnits::DEGREES));
    EXPECT_EQ(AxisLabel0, QString::fromStdString(AxisNames::InitSpecAxis()[AxesUnits::DEGREES]));
    EXPECT_EQ(AxisLabel1, SpecularDataAxesNames::y_axis_default_name);
}

TEST_F(TestCsvImportAssistant, test_speedReadFile)
{
    size_t maxRows = 1000;
    size_t maxCols = 1000;
    double_t millisec_tolerance = 2000.0;
    bool isTimeShort = true;

    for(size_t nRows = 10 ; nRows <= maxRows; nRows*=10){
        for(size_t nCols = 10 ; nCols <= maxCols; nCols*=10){

            //Write test file
            writeTestFile(nRows,nCols);

            //Time the process of reading and importing data:
            std::clock_t c_start = std::clock();

            //Reading and setting data to import:
            CsvImportAssistant assistant(testFilename());
            assistant.setIntensityColumn(1);
            assistant.setCoordinateColumn(9,AxesUnits::DEGREES);
            assistant.setFirstRow(1);
            assistant.setLastRow(nRows);

            //Importing of data:
            //If something goes wrong, this line may make the test fail or even crash.
            //The correctness of the reading is tested in test_readFile.
            std::vector<double> RawDataVec = assistant.getData().intensityData()->getRawDataVector();
            EXPECT_EQ(RawDataVec.size(), nRows);

            //The test fails if the time was not short:
            std::clock_t c_end = std::clock();
            double_t time_spent = 1000.0 * double_t(c_end-c_start) / double_t(CLOCKS_PER_SEC);
            isTimeShort = millisec_tolerance - time_spent > 0;
            //std::cout << "nRows: " << nRows << "; nCols: " << nCols << "; time: " << time_spent << " ms\n" << std::flush;
            if(!isTimeShort)
                break;
        }
        if(!isTimeShort)
            break;
    }
    EXPECT_TRUE(isTimeShort);
}
