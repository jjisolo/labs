#pragma once

#include <string>
#include <fstream>
#include <iostream>


namespace modern {

void getsearchletter(std::string &letter);
void getfilenames(std::string& filename_in, std::string& filename_out);
void readfile(std::string& filename, std::string& text);
void fillfile(std::string& filename);
void count(std::string& text, std::string word);
void split(std::string& text);
void writefile(std::string& filename, std::string& text);
void printfile(std::string& filename);
}
