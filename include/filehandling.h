#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <iostream>
#include <fstream>

class File{
    private:
        std::fstream f;
        std::string fn;
        bool has_filename = false;
        bool new_file = false;
    public:
        File(std::string);
        void setFileName(std::string);
        void check();
        bool changeMode(std::string);
        bool is_new_file();
        std::fstream& expose();
};

#endif