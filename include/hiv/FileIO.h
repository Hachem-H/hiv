#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum hiv_FileReadMode_t
{
    HIV_FILE_BINARY = 1 << 0,
    HIV_FILE_READ   = 1 << 1,
    HIV_FILE_WRITE  = 1 << 2,
} hiv_FileReadMode;

typedef struct hiv_File_t
{
    char* contents;
    size_t size;
    
    hiv_FileReadMode mode;
    FILE* fileStream;
    char* modeString;
} hiv_File;

static hiv_File* hiv_OpenFile(const char* filepath, hiv_FileReadMode readMode)
{
    char* modeString = NULL;
    switch (readMode)
    {
        case HIV_FILE_READ:
            modeString = "r"; 
            break;
        case HIV_FILE_WRITE: 
            modeString = "w+"; 
            break;
        case HIV_FILE_READ |
             HIV_FILE_BINARY: 
            modeString = "rb"; 
            break;
        case HIV_FILE_WRITE |
             HIV_FILE_BINARY: 
            modeString = "wb"; 
            break;
        case HIV_FILE_READ |
             HIV_FILE_WRITE: 
            modeString = "r+"; 
            break;
        case HIV_FILE_READ  |
             HIV_FILE_WRITE |
             HIV_FILE_BINARY: 
            modeString = "rb+"; 
            break;
        default: fprintf(stderr, "[ERR]: Unrecognized read mode.\n"); break;
    }

    FILE* fileStream = fopen(filepath, modeString);
    if (!fileStream)
        fprintf(stderr, "[ERR]: Could not open file @ %s.\n", filepath);
    
    fseek(fileStream, 0, SEEK_END);
    size_t size = ftell(fileStream);
    rewind(fileStream);

    char* buffer = (char*) malloc(size);
    fread(buffer, 1, size, fileStream);
    buffer[size] = 0;

    hiv_File* file = (hiv_File*) malloc(sizeof(hiv_File));
    {
        file->contents = buffer;
        file->size = size;

        file->fileStream = fileStream;
        file->modeString = modeString;
        file->mode = readMode;
    } return file;
}

#define hiv_WriteFile(file, buffer) \
    fwrite(buffer, 1, strlen(buffer), file->fileStream);
#define hiv_WriteFileF(file, ...) \
    fprintf(file->fileStream, __VA_ARGS__)

static void hiv_AppendFile(hiv_File* file, const char* buffer)
{
    size_t newSize = strlen(file->contents) + strlen(buffer);
    char* newBuffer = (char*) malloc(newSize);
    strcpy(newBuffer, file->contents);
    strcpy(newBuffer + strlen(file->contents), buffer);
    free(file->contents);

    file->contents = newBuffer;
    file->size = newSize;
}

static void hiv_CloseFile(hiv_File* file)
{
    fclose(file->fileStream);
    free(file->contents);
    free(file);
}
