#include "modernc.hh"
#include "plainc.hh"
#include <cstdlib>
#include <ios>
#include <sstream>
#include <stdexcept>
#include <cassert>

namespace modern {

void getfilenames(std::string& filename_in, std::string& filename_out) {
  std::cout << "Enter input file name: ";
  std::cin  >> filename_in;

  std::cout << "Enter output file name: ";
  std::cin  >> filename_out;
}

void getsearchletter(std::string &letter) {
  std::cout << "Enter letter to seatch in brackets: ";
  std::cin  >> letter;
}

void fillfile(std::string& filename) {
  std::fstream file;
  std::string input;

  file.open(filename, std::ios::out);
  assert(file.is_open());

  std::cout << "Please enter the data for the input file(type `END` to stop):" << std::endl;
  for(std::string line; std::getline(std::cin, line);) {
	if(line == "END")
	  break;
	file << input << "\n";
  }

  file.close();
}

void readfile(std::string& filename, std::string& text) {
  std::fstream      file;
  std::stringstream ss;

  file.open(filename, std::ios::in);
  ss << file.rdbuf();
  text = ss.str();
  file.close();
}

void count(std::string& text, std::string word) {
  bool     count = true;
  unsigned sum   = 0;
  
  for(unsigned i=0; i < text.length(); ++i) {
	if(text[i] == '{')
	  count = true;

	if(text[i] == '}') {
	  const std::string val = ":" + std::to_string(sum);
	  text.insert(i, val);
	  
	  count = false;
	  sum   = 0;
	  i    += val.length(); 
	}

	if(count && text[i] == word[0])
	  sum++;
  }
}

void split(std::string& text) {
  unsigned i = 0;
  while(i < text.length()) {
	if(text[i] == '.' && i + 1 < text.length()) {
	  text.insert(i+1, "\n");
	  i += 2;
	} else {
	  i++;
	}
  }
}

void writefile(std::string& filename, std::string& text) {
  std::fstream file;
  file.open(filename, std::ios::out);
  assert(file.is_open());
  file << text;
  file.close();
}
  
void printfile(std::string& filename) {
  std::fstream file;
  file.open(filename, std::ios::in);
  assert(file.is_open());
  std::cout << "\t== file " << filename << " contents ==" << std::endl;
  std::cout << file.rdbuf();
  file.close();
}
  
}
