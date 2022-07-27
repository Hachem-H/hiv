# FileIO

A module to interact with files, and basic operations such as writing or reading.

### `hiv_File`

A structure containing data about the file, such as the contents and the size.

```c
typedef struct hiv_File_t
{
    char* contents;
    size_t size;
    
    hiv_FileReadMode mode;
    FILE* fileStream;
    char* modeString;
} hiv_File;
```

### `hiv_OpenFile(const char* filepath, hiv_FileReadMode readMode)`

Reads a file and then returns it as a `hiv_File`,  the read mode can be a `HIV_FILE_BINARY`, `HIV_FILE_READ`, `HIV_FILE_WRITE`. To combine multiple read modes, we can use the `OR` operator: `[mode1] | [mode2] ...`. This functions allocates memory, so when the file is opened, it has to be closed using the `hiv_CloseFile` function, thus freeing the memory.

### `hiv_CloseFile(hiv_File* file)`
Closes a file stream and frees memory.

### `hiv_WriteFile(file, buffer)`
Writes a buffer into the file stream.

### `hiv_WriteFileF(file, format...)`
Writes a buffer into the file stream, using format string, for examle:
```c
hiv_WriteFileF(file, "Hello! My name is %s\n", name);
hiv_WriteFileF(file, "I am %d\n", age);
```

### `hiv_AppendFile(hiv_File* file, const char* buffer)`
Appends data to a file, warning this does recreate the contents of the file from scratch so there is a heap allocation overhead.
