#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <numeric>
#include <optional>
#include <vector>
#include <map>
#include <exception>

struct loadtxt {
    // Mandatory arguments
    loadtxt(std::string fname) : _fname(fname) {}

    loadtxt& comments(std::string comments) { _comments = comments; return *this; }
    loadtxt& delimiter(std::string delimiter) { _delimiter = delimiter; return *this; }
    loadtxt& skiprows(int skiprows) { _skiprows = skiprows; return *this; }
    loadtxt& usecols(std::vector<int> usecols) { _usecols = usecols; return *this; }
    loadtxt& max_rows(int max_rows) { _max_rows = max_rows; return *this; }

    std::vector<std::vector<std::string>> operator()()
    {
        if (_fname.empty()) {
            std::string msg = "loadtxt: filename is empty";
            throw std::invalid_argument(msg);
        }

        std::ifstream infile( _fname );

        if (infile.fail()) {
            std::string msg = "loadtxt: could not read file (" + _fname + ")!";
            throw std::runtime_error(msg);
        }
        
        // ignore first `skiprows` lines
        static const int max_line = 65536;
        for (int i = 0 ; i < _skiprows ; i++)
            infile.ignore(max_line, '\n');

        std::vector<std::string> record;

        while (true)
        {
            // clear the record before reading
            record.clear();

            // read the entire line into a string (a record is terminated by a newline)
            std::string line;
            std::getline(infile, line);

            if (infile.eof() && line.empty())
                break;
            
            if (line.find(_comments, 0) == 0)
                continue;

            // use a stringstream to separate the fields out of the line
            std::stringstream ss(line);

            std::string f;

            while (std::getline(ss, f, '|'))
                record.push_back(f);

//            for (int i = 0; i < record.size(); i++){
//                std::cout << " ## " << record[i];
//            }
//            std::cout << std::endl;

            _filedata.push_back(record);
        }
        
        // complain if something went wrong
        if (!infile.eof())
        {
            std::cout << "Could not read file (" << _fname << ")!\n";
            exit(1);
        }

        infile.close();

        int nlines = _filedata.size();

        // only read _max_rows of content
        if (_max_rows != 0)
            nlines = std::min(nlines, _max_rows);

        int ncols = _filedata[0].size();

        std::vector<int> cols;
        if (_usecols.size() == 0)
        {
            data.resize(ncols);
            cols.resize(ncols);
            std::iota(cols.begin(), cols.end(), 0);
        }
        else
        {
            data.resize(_usecols.size());
            cols = _usecols;
            //! usecols starts from 1!
            for (auto& j : cols)
                j--;
        }

        for (size_t i = 0; i < data.size(); i++)
            data[i].reserve(nlines);
        
        for (int i = 0; i < nlines; i++)
        {
            int k = 0;
            for (auto j : cols)
            {
                data[k].push_back(_filedata[i][j]);
                k++;
            }
        }
        
        return data;
    }

    ~loadtxt(){};

    public:
        std::vector<std::vector<std::string>> data;

    private:
        std::string _fname;
        std::string _comments = "#";
        std::string _delimiter = " ";
        int _skiprows = 0;
        std::vector<int> _usecols;
        int _max_rows = 0;
        std::vector<std::vector<std::string>> _filedata;
};