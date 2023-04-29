#pragma once

#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

namespace legacy {
  int   digitsin(int number);
  int   sentencesin(const char* string);
  char* itoa(int number);
  char* count(const char* string, char word);
  char* substr(char* string, std::size_t start, std::size_t end);
  char* split(const char* string);

  void getfilenames(char filename_in[255], char filename_out[255]);
  void getsearchletter(char *sym);
  void fillfile(char filename[255]);
  void readfile(char filename[255], char** text);
  void writefile(char filename[255], char* text);
  void printfile(char filename[255]);
  
  FILE* createfile(char filename[255], const char* mode);
}
