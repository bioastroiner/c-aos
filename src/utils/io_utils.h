#include<stdio.h>
#define _FILESIZE_LIMIT 30000 // max size allowed is 30KB

//  library that generalizes reading input files line by line and giving them
//  to a processor function to be specefically prcoessed

// provide a file and it parses its line into an array of elements
// then it processes them in a func*
//  nLn:
//  number of lines to read, throws exception if it excedes linenmbr
//  it will discart any leftover lines
// old func do not use!
void parseln(const char *_Filename,const int _nLn,void (*func_)(char* elm_[],size_t));

// General Parsing Method
// uses fget so parses line by line till end
void parseFile(const char *_Filename,const int _line_size_max,void (*_processor)(char* buf));