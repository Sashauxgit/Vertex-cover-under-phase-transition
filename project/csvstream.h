#ifndef CSVS_H
#define CSVS_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>

using namespace std;

class dataWriter {
    ofstream fout;
    string fileName;
    bool entryWork;
    class endOfEntryLine {};
    void openEntry() {
        if (!entryWork) {
            fout.open(fileName, ios::app);
            if (!fout) throw std::runtime_error("file open error");
            entryWork = true;
        } else fout << ";";
    }
public:
    static const endOfEntryLine endentry;
    dataWriter(std::string fileName):fileName(fileName), entryWork(false) {
        fout.open(fileName, ios::out);
        if (!fout) throw std::runtime_error("file open error");
        fout.close();
    }
    ~dataWriter() {fout.close();}

    template<typename T>
    friend dataWriter& operator << (dataWriter& out, T obj);
    friend dataWriter& operator << (dataWriter& out, double obj);
    friend dataWriter& operator << (dataWriter& out, const endOfEntryLine& obj);
};

inline const dataWriter::endOfEntryLine dataWriter::endentry = dataWriter::endOfEntryLine();

template<typename T>
dataWriter& operator << (dataWriter& dw, T obj) {
    dw.openEntry();
    dw.fout << obj;
    return dw;
}

inline dataWriter& operator << (dataWriter& dw, double value) {
    dw.openEntry();

    std::string strVal = std::to_string(value);
    try {strVal.at(strVal.find(".")) = ',';} catch (std::out_of_range& e){}
    
    dw.fout << strVal;

    return dw;
}

inline dataWriter& operator << (dataWriter& dw, const dataWriter::endOfEntryLine& obj) {
    dw.fout << "\n";
    dw.fout.close();
    dw.entryWork = false;
    return dw;
}

#endif