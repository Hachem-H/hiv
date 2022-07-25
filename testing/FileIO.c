#include <hiv/FileIO.h>

int main()
{
    hiv_File* helloFile = hiv_OpenFile("res/HelloWorld.txt", HIV_FILE_READ);
    printf("%s\n\n", helloFile->contents);
    hiv_CloseFile(helloFile);

    const char* text = "This is going to create a new a file I hope\n"
                       "I wonder if this is going to work first try\n"
                       "If it does i will update this text\n\n"
                       "Yooooooo first try, i am a great programmer mhmm\n";
    const char* fileWritePath = "res/WriteFile.txt";

    hiv_File* file = hiv_OpenFile(fileWritePath, HIV_FILE_WRITE);
    hiv_WriteFile(file, text);
    printf("Wrote text @ %s\n", fileWritePath);
    hiv_CloseFile(file);

    file = hiv_OpenFile(fileWritePath, HIV_FILE_READ);
    printf("Rereading written file @ %s:\n\n%s\n", fileWritePath, file->contents);
    hiv_CloseFile(file);
}
