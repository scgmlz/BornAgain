#ifndef CSVREADER_H
#define CSVREADER_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class CSVRow
{
    public:
        std::string const& operator[](std::size_t index) const;

        std::size_t size() const;

        void readNextRow(std::istream& str);


        void setSeparator(char sep);

        char getSeparator();

        void addCell(std::string str);

    private:
        std::vector<std::string>    m_data;
        char separator = '-';
};

inline std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}

class CSVIterator
{
    public:
        typedef std::input_iterator_tag     iterator_category;
        typedef CSVRow                      value_type;
        typedef std::size_t                 difference_type;
        typedef CSVRow*                     pointer;
        typedef CSVRow&                     reference;

        CSVIterator(std::istream& str, char sep)  :m_str( str.good() ? &str : NULL ) {m_sep=sep; ++(*this); }
        CSVIterator()                   :m_str(NULL) {}

        // Pre Increment
        CSVIterator& operator++()               {if (m_str) { m_row.setSeparator(m_sep); if (!((*m_str) >> m_row)){m_str = NULL;}}return *this;}
        // Post increment
        CSVIterator operator++(int)             {CSVIterator    tmp(*this);++(*this);return tmp;}
        CSVRow const& operator*()   const       {return m_row;}
        CSVRow const* operator->()  const       {return &m_row;}

        bool operator==(CSVIterator const& rhs) {return ((this == &rhs) || ((this->m_str == NULL) && (rhs.m_str == NULL)));}
        bool operator!=(CSVIterator const& rhs) {return !((*this) == rhs);}



    private:
        std::istream*       m_str;
        CSVRow              m_row;
        char                m_sep;
};

class CSVFile
{
    public:
        CSVFile(std::string path_to_file): filepath(path_to_file), separator('-'), headersRow(0) {Init();}
        CSVFile(std::string path_to_file, char sep): filepath(path_to_file), separator(sep), headersRow(0) {Init();}
        CSVFile(std::string path_to_file, char sep, uint headRow): filepath(path_to_file), separator(sep), headersRow(headRow) {Init();}


        void Init(){
            Read();
            EqualizeRowLengths();
        }

        void Read();


        void EqualizeRowLengths();


        CSVRow const operator[](std::size_t index_i) const;

        std::size_t NumberOfRows() const;

        std::size_t NumberOfColumns() const;

        void set_separator(char sep);

        char get_separator();

        CSVRow get_headers();

        CSVRow get_row(int i);

    private:
        std::string filepath;
        char separator = '-';
        uint headersRow = 0;
        uint numberOfColumns = 0;
        std::vector<CSVRow>    rows;

};

#endif // CSVREADER_H
