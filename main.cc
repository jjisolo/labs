#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cassert>

#include "plainc.hh"
#include "modernc.hh"

static constexpr const unsigned CMD_EXEC_FP  = 1u;
static constexpr const unsigned CMD_EXEC_FS  = 2u;
static constexpr const unsigned CMD_EXEC_ERR = 0u;

static constexpr auto USAGE =
  R"(Lab 1

     Usage:
        lab [options]

     Options:
        --mode [filePointer|fileStream]
)";

int legacy_main() {
  char filename_in[255], filename_out[255];
  char letter, *file_in_txt;

  legacy::getsearchletter(&letter);
  legacy::getfilenames(filename_in, filename_out);

  // Create files if they do not exists
  FILE* file_in  = legacy::createfile(filename_in, "w");
  FILE* file_out = legacy::createfile(filename_out, "w");
  fclose(file_in);
  fclose(file_out);

  legacy::fillfile(filename_in);
  legacy::readfile(filename_in, &file_in_txt);

  char *result_legacy   = legacy::count(file_in_txt, letter);
  char *result_splitted = legacy::split(result_legacy);
  legacy::writefile(filename_out, result_splitted);

  legacy::printfile(filename_in);
  legacy::printfile(filename_out);
  
  free(file_in_txt);
  free(result_legacy);
  free(result_splitted);

  return 0;
}

int modern_main() {
  std::string filename_in, filename_out, letter;
  std::string file_in_txt;
  std::ofstream file_in, file_out;

  modern::getsearchletter(letter);
  modern::getfilenames(filename_in, filename_out);
  file_in.open(filename_in);
  assert(file_in.is_open());
  file_in.close();
  
  file_out.open(filename_out);
  assert(file_out.is_open());
  file_out.close();

  modern::fillfile(filename_in);
  modern::readfile(filename_in, file_in_txt);
  modern::count(file_in_txt, letter);
  modern::split(file_in_txt);
  modern::writefile(filename_out, file_in_txt); 

  modern::printfile(filename_in);
  modern::printfile(filename_out);

  return 0;
}

int parse_cmd(int argc, char* argv[]) {
  for(unsigned i = 1; i < argc; ++i) {
	std::string arg = argv[i];

	if(arg == "--mode") {
	  if(i + 1 >= argc) {
		std::cout << "No program mode specified after the --mode flag" << std::endl;
		return CMD_EXEC_ERR;
	  } else if(std::string(argv[i+1]) == "filePointer") {
		return CMD_EXEC_FP;
	  } else if(std::string(argv[i+1]) == "fileStream") {
		return CMD_EXEC_FS;
	  } else {
		std::cout << "Invalid option: " << argv[i+1] << std::endl;
		std::cout << "See help message(--help)" << std::endl;
		return CMD_EXEC_ERR;
	  }
	} else if(arg == "--help") {
	  std::cout << USAGE << std::endl;
	  return CMD_EXEC_ERR;
	} else {
		std::cout << "The specified mode is invalid" << std::endl;
		std::cout << "See help message(--help)" << std::endl;
		return CMD_EXEC_ERR;
	}
  }

  std::cout << USAGE << std::endl;
  return CMD_EXEC_ERR;
}

int execute_cmd(int cmd_res) {
  switch(cmd_res) {
  case CMD_EXEC_FP:
	std::cout << "Using legacy C code.." << std::endl;
	return legacy_main();
  case CMD_EXEC_FS:
	std::cout << "Using modern C++ code.." << std::endl;
	return modern_main();
  default:
	return EXIT_FAILURE;
  }
}

int main(int argc, char* argv[]) {
  return execute_cmd(parse_cmd(argc, argv));
}
