#include "CsvReader.h"
#include <fstream>
#include <iostream>

std::string const& CSVRow::operator[](std::size_t index) const
{
    return m_data[index];
}

std::size_t CSVRow::size() const
{
    return m_data.size();
}

void CSVRow::readNextRow(std::istream& str)
{
    std::string         line;
    std::getline(str, line);
    std::replace(std::begin(line),std::end(line),'\t',' ');

    std::stringstream   lineStream(line);
    std::string         cell;

    m_data.clear();
    while(std::getline(lineStream, cell, separator))
    {
        m_data.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        m_data.push_back("");
    }
}

void CSVRow::setSeparator(char sep){
    this->separator = sep;
    return;
}

char CSVRow::getSeparator(){
    return this->separator;
}

void CSVRow::addCell(std::string str){
    m_data.push_back(str);
}

void CSVFile::Read()
{
    //try{
        std::ifstream file(filepath);
        if(!file.is_open()){throw std::ios_base::failure("Unable to open file \"" + filepath + "\"");}
        for(CSVIterator loop(file, separator); loop != CSVIterator(); ++loop){
            rows.push_back((*loop));
            numberOfColumns = (*loop).size() > numberOfColumns ? (*loop).size() : numberOfColumns;
        }
   // }catch(const std::exception& e){
   //     std::cout << e.what() << std::endl;
    //}
}

void CSVFile::EqualizeRowLengths()
{
    for(uint i = 0; i < NumberOfRows(); i++){
        while(rows[i].size() < NumberOfColumns()) {
            rows[i].addCell("");
        }
    }

}


CSVRow const CSVFile::operator[](std::size_t index_i) const
{
    return rows[index_i];
}

std::size_t CSVFile::NumberOfRows() const
{
    return rows.size();
}

std::size_t CSVFile::NumberOfColumns() const
{
    return this->numberOfColumns;
}

void CSVFile::set_separator(char sep){
    this->separator = sep;
    return;
}

char CSVFile::get_separator(){
    return this->separator;
}

CSVRow CSVFile::get_headers(){
    if(headersRow > 0){
        return this->rows[headersRow-1];
    }else{
        CSVRow dummy;
        while (dummy.size() < NumberOfColumns())
            dummy.addCell("");
        return dummy;
    }
}

CSVRow CSVFile::get_row(int i){
    return this->rows[i];
}




