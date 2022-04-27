#include "load.h"

bool strendw(char* str,const char* end)
{
    int i = strlen(str)-strlen(end);
    int j = 0;

    if (i < 0)
        return false;

    while (str[i] != 0)
    {
        if (str[i] != end[j])
            return false;
        i++;
        j++;
    }

    return true;
}

bool strstartw(char* str, const char* start)
{
    int i = 0;

    if (strlen(str) < strlen(start))
        return false;

    while (i < strlen(start))
    {
        if (str[i] != start[i])
            return false;
        i++;
    }

    return true;
}
int strtruelen(char* str)
{
    int len = 0;
    while (str[len] != 0)
    {
        len++;
    }
    return len+1;
}

char* strAppend(const char* o, char* a)
{
    int sizeO = strtruelen(o);
    int sizeA = strtruelen(a);

    char* out = malloc((sizeO+sizeA-1)*sizeof(char));

    for (int i = 0; i < sizeO-1; i++)
    {
        out[i] = o[i];
    }

    for (int i = 0; i < sizeA; i++)
    {
        out[i+sizeO-1] = a[i];
    }

    return out;
}


char* readLine(FILE* stream, bool* eof)
{
    char* out = malloc(sizeof(char));
    int bufferSize = 1;

    char readC = fgetc(stream);

    while (readC != '\n')
    {
        out[bufferSize-1] = readC;
        bufferSize++;
        out = realloc(out,sizeof(char)*bufferSize);

        if (readC == EOF)
        {
            out[bufferSize-1] = 0;
            *eof = true;
            return out;
        }

        readC = fgetc(stream);
    }
    out[bufferSize-1] = 0;
    return out;
}

