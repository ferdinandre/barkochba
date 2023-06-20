//
// Created by Ferdinand on 2022. 05. 06..
//

#ifndef NHF4_IO_H
#define NHF4_IO_H



//Absztrakt Writer osztaly
class Writer {
public:
    Writer() {}
    virtual ~Writer() {}
    //pure virtual wrtie
    virtual void write(const std::string&) const = 0;
};
//ConsoleWriter osztaly
class ConsoleWriter : public Writer {
public:
    ConsoleWriter() {}
    //write
    void write(const std::string& s) const;
};
//FileWriter osztaly
class FileWriter : public Writer {
    std::string fname;
public:
    FileWriter(std::string fname) : fname(fname) {}
    //write
    void write(const std::string& s) const;
};
//Virtualis Reader osztaly
class Reader {
public:
    Reader() {}
    virtual ~Reader() {}
    //pure virtual read fuggveny
    virtual std::string read() const = 0;
};
//FileReader osztlay
class FileReader : public Reader {
    std::string fname;
public:
    FileReader(std::string fname) : fname(fname) {}
    //read
    std::string read() const;
};
//ConsoleReader osztaly
class ConsoleReader : public Reader {
public:
    ConsoleReader() {}
    //read
    std::string read() const;
};
#endif