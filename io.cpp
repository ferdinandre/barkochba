//
// Created by Ferdinand on 2022. 05. 06..
//
#include "memtrace.h"
#include "exception.h"
#include <fstream>
#include "io.h"

void FileWriter::write(const std::string &s) const  {
    std::ofstream FileOut(fname);
    if(!FileOut.is_open()) {
        std::string errmsg = "File could not be opened: " + fname;
        throw(FileNotFound(errmsg));
    }else {
        for(char i : s) {
            FileOut.put(i);
        }
        FileOut.close();
    }

}



void ConsoleWriter::write(const std::string &s)const  {
    std::cout << s << std::endl;
}



std::string FileReader::read()const  {
    std::ifstream FileIn(fname);
    std::string temp;
    if(!FileIn.is_open()) {
        std::string errmsg = "File could not be opened: " + fname;
        throw(FileNotFound(errmsg));
    }else {
        int c  = FileIn.get();
        do {
            temp += (char)c;
            c = FileIn.get();
        }while(c != EOF);
        FileIn.close();
        return temp;
    }

}

std::string ConsoleReader::read() const {
    std::string line;
    std::getline(std::cin, line);
    return line;
}
