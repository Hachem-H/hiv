#include <hiv/ConIO.h>

#include <stdio.h>
#include <stdbool.h>

int main()
{
    size_t counter = 0;
    while (true)
    {
        hiv_SetTermColor(HIV_TERM_RED, HIV_TERM_GREEN);    printf("red/green.\n");
        hiv_SetTermColor(HIV_TERM_BLUE, HIV_TERM_RED);     printf("blue/red.\n");
        hiv_SetTermColor(HIV_TERM_BLACK, HIV_TERM_WHITE);  printf("black/white.\n");
        hiv_ClearTermColors();

        printf("\n\ncounter = %d\n", counter);
        counter++;

        int temp = getchar();
        hiv_TermClear();
    }
}
