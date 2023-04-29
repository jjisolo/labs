#include "plainc.hh"
#include <cstdio>
#include <cstdlib>

#define TRUE  1
#define FALSE 0

namespace legacy {

void getfilenames(char filename_in[255], char filename_out[255]) {
  printf("Enter input file name: ");
  scanf("%s", filename_in);

  printf("Enter output file name: ");
  scanf("%s", filename_out);
}

void getsearchletter(char *sym) {
  printf("Enter the letter to search in brackets: ");
  scanf("%c", sym);
}

FILE *createfile(char filename[255], const char* mode) {
  char input[1024];

  FILE *file = fopen(filename, mode);
  if(ferror(file)) {
	printf("Cannot create file %s with mode %s!\n", filename, mode);
	exit(1);
  }

  return file;
}

void readfile(char filename[255], char **text) {
  long  bytes;
  FILE* file;

  file = createfile(filename, "rb");
  if(!ferror(file)) {
	fseek(file, 0, SEEK_END);
	bytes = ftell(file);
	fseek(file, 0, SEEK_SET);
	*text = (char *)malloc(bytes+1);

	if(text)
	  fread(*text, 1, bytes, file);
	else
	  perror("Unable to allocate text for the file contents\n");

	(*text)[bytes] = '\0';

  } else {
	perror("Unable to create file!");
	exit(EXIT_FAILURE);
  }

  fclose(file);
}

void printfile(char filename[255]) {
  FILE* file = createfile(filename, "r");

  printf("\n\n\t == Contents of file %s == \n", filename);
  char ch = fgetc(file);
  while(ch != EOF) {
	printf("%c", ch);
	ch = fgetc(file);
  }

  fclose(file);
}
  
void writefile(char filename[255], char* text) {
  FILE* file = createfile(filename, "w");
  fputs(text, file);
  fclose(file);
}
 
void fillfile(char filename[255]) {
  char          input[1024];
  FILE*         file;

  file = createfile(filename, "w");

  printf("Enter the data to the file(type `END` to stop):\n");
  do {
	scanf("%s", input);
	if(strcmp(input, "END") == 0)
	  break;

	fprintf(file, "%s\n", input);
  } while(TRUE);
 

  fclose(file);
}
  
char* substr(char* string, std::size_t start, std::size_t end) {
  const std::size_t length = strlen(string);
  const std::size_t range  = end - start;
  char *sub                = (char *)malloc(range+1);

  memset(sub, '\0', range+1);
  for(unsigned i = 0; i < range; ++i)
	sub[i] = string[start+i];

  #ifdef CW_DEBUG
	fprintf(stderr, "\nInput string:\t%s\nStart position:\t%d\nEnd position:\t%d\n", string, start, end);
    fprintf(stderr, "Result:\t%s\n\n", sub);
  #endif

  return sub;
}

int digitsin(int number) {
  int digits = 0;
  
  while(number != 0) {
	number /= 10;
	++digits;
  }

  if(digits == 0)
	digits = 1;

  return digits;
}

char* itoa(int number) {
  int   digits = digitsin(number);
  char* string = (char *)malloc(digits + 2);

  sprintf(string, ":%d", number);
  string[digits+1] = '\0';

  return string;
}
  
char* count(const char* string, char word) {
  char*       res = (char*) malloc(strlen(string)); strcpy(res, string);
  std::size_t len = strlen(res);
  std::size_t sum = 0;

  strcpy(res, string);
  bool count=false;
  for(unsigned i=0; i < strlen(res); ++i) {
	if(res[i] == '{') {
	  count = true;
	}
	
	if(res[i] == '}') {
	  std::size_t digits  = digitsin(sum);
	  char       *sum_str = itoa(sum);

	  // Split the string into the two parts
	  char *start = substr(res, 0, i);
	  char *end   = substr(res, i, strlen(res)+1);
	  
	  // Alocate space for the new string
	  len = strlen(res);
	  free(res); res = (char*)malloc(len+digits+2); // plus space for semicolon and null terminator
	  memset(res, '\0', len+digits+2);

	  // Commit the insert
	  strcpy(res,                               start);
	  strcpy(res+strlen(start),               sum_str);
	  strcpy(res+strlen(start)+strlen(sum_str),   end);

	  // Release the memory
	  free(sum_str);
	  free(start);
	  free(end);

	  count = false;
	  sum   = 0;
	  i    += digits+1;
	}

	if(count && res[i] == word){
	  sum++;
	}
  }
  return res;
}

int sentencesin(const char* string) {
  int counter = 0;
  for(unsigned i=0; i < strlen(string); ++i)
	if(string[i] == '.') ++counter;
  return counter;
}
  
char* split(const char* string) {
  char *result = (char *)malloc(strlen(string) + sentencesin(string) + 1); strcpy(result, string);

  for(unsigned i=0; i < strlen(result); ++i) {
	if(result[i] == '.') {
	  result[i+1] = '\n';
	  ++i;
	}
  }

  return result;
}
  
}
