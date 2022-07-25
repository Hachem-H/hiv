#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum hiv_FileReadMode
{
    HIV_FILE_BINARY = 1 << 0,
    HIV_FILE_READ   = 1 << 1,
    HIV_FILE_WRITE  = 1 << 2,
};

static char* hiv_OpenFile(const char* filepath, enum hiv_FileReadMode readMode)
{
    char* mode = NULL;
    switch (readMode)
    {
        case HIV_FILE_READ:
            mode = "r"; 
            break;
        case HIV_FILE_WRITE: 
            mode = "w"; break;
        case HIV_FILE_READ |
             HIV_FILE_BINARY: 
            mode = "rb"; 
            break;
        case HIV_FILE_WRITE |
             HIV_FILE_BINARY: 
            mode = "wb"; 
            break;
        case HIV_FILE_READ |
             HIV_FILE_WRITE: 
            mode = "r+"; 
            break;
        case HIV_FILE_READ  |
             HIV_FILE_WRITE |
             HIV_FILE_BINARY: 
            mode = "rb+"; 
            break;
        default: fprintf(stderr, "[ERR]: Unrecognized read mode.\n"); break;
    }

    FILE* fileStream = fopen(filepath, mode);
    if (!fileStream)
        fprintf(stderr, "[ERR]: Could not open file @ %s.\n", filepath);
    
    fseek(fileStream, 0, SEEK_END);
    size_t size = ftell(fileStream);
    rewind(fileStream);

    char* buffer = (char*) malloc(size);
    fread(buffer, 1, size, fileStream);
    buffer[size] = 0;

    fclose(fileStream);
    return buffer;
}

static void hiv_CloseFile(char* buffer)
{
    if (buffer)
        free(buffer);
}
