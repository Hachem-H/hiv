#include <hiv/FileIO.h>

int main()
{
    char* fileBuffer = hiv_OpenFile("res/HelloWorld.txt", HIV_FILE_READ);
    printf("%s\n", fileBuffer);
    hiv_CloseFile(fileBuffer);
}
