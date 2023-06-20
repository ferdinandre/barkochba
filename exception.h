//
// Created by Ferdinand on 2022. 05. 14..
//

#ifndef BKOBA4_EXCEPTION_H
#define BKOBA4_EXCEPTION_H




//Sajat Index_OutOFRange kivetel osztaly
class Index_OutOFRange : public std::logic_error {
public:
    explicit Index_OutOFRange(const std::string& s) :std::logic_error(s) {}
};


//Sajat FileNotFound kivetel osztaly
class FileNotFound : public std::runtime_error {

public:
    explicit FileNotFound(const std::string& s):std::runtime_error(s) {}

};
#endif //BKOBA4_EXCEPTION_H
