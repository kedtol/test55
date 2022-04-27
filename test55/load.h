#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int strtruelen(char* str);
bool strendw(char* str,const char* strend);
bool strstartw(char* str, const char* strstart);
char* strAppend(const char* o, char* a);

char* readLine(FILE* stream, bool* eof);



#endif // LOAD_H_INCLUDED
