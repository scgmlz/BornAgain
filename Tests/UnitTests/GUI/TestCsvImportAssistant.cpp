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

    void writeTestFile(int nRows, int nCols){
        remove(m_testFilename.c_str());
        std::ofstream myfile;
        myfile.open (m_testFilename);
        for(auto i = 0 ; i < nRows; i++){
            for(auto j = 0 ; j < nCols; j++){
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
 * It has ten columns, not four. While this way of counting the columns is desired
 * in the GUI importer (The separator is a space! AND we want to show the headers),
 * it's odd when a GUI is not available. Keeping this way of counting columns in
 * mind, we build a test setting the first column (0,4,8,12...) as intensity and the
 * 9th one (2,6,10,14...) as a coordinate with "degrees" as units.
 *
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
    assistant.setCoordinateColumn(9,AxesUnits::DEGREES);
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
    unsigned maxRows = 1000;
    unsigned maxCols = 1000;
    double_t millisec_tolerance = 2000.0;
    bool isTimeShort = true;

    for(auto nRows = 10 ; nRows <= maxRows; nRows*=10){
        for(auto nCols = 10 ; nCols <= maxCols; nCols*=10){

            //Write test file
            writeTestFile(nRows,nCols);

            //Time the process of reading and importing data:
            std::clock_t c_start = std::clock();

            //Reading and setting data to import:
            CsvImportAssistant assistant(testFilename());
            assistant.setIntensityColumn(1);
            assistant.setCoordinateColumn(9,AxesUnits::DEGREES);
            assistant.setFirstRow(5);
            assistant.setLastRow(7);

            //Importing of data:
            auto DataRank = assistant.getData().dataRank();
            auto AllocSize = assistant.getData().intensityData()->getAllocatedSize();
            auto RawDataVec = assistant.getData().intensityData()->getRawDataVector();
            auto UnitsLabel = assistant.getData().unitsLabel();
            auto AxisLabel0= assistant.getData().axisLabel(0);
            auto AxisLabel1= assistant.getData().axisLabel(1);

            std::clock_t c_end = std::clock();
            //The test fails if the time was not short:
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
