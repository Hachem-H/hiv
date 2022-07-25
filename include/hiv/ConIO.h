#pragma once

typedef enum hiv_TermColors_t
{
    HIV_TERM_CLEAR         = 00,

    HIV_TERM_BLACK         = 30,
    HIV_TERM_RED           = 31,
    HIV_TERM_GREEN         = 32,
    HIV_TERM_YELLOW        = 33,
    HIV_TERM_BLUE          = 34,
    HIV_TERM_MAGENTA       = 35,
    HIV_TERM_CYAN          = 36,
    HIV_TERM_WHITE         = 37,

    HIV_TERM_LIGHT_BLACK   = 90,
    HIV_TERM_LIGHT_RED     = 91,
    HIV_TERM_LIGHT_GREEN   = 92,
    HIV_TERM_LIGHT_YELLOW  = 93,
    HIV_TERM_LIGHT_BLUE    = 94,
    HIV_TERM_LIGHT_MAGENTA = 95,
    HIV_TERM_LIGHT_CYAN    = 96,
    HIV_TERM_LIGHT_WHITE   = 97,
} hiv_TermColors;

#define hiv_SetTermColor(fg, bg) \
    printf("\x1B[%dm\x1B[%dm", fg, bg+10);
#define hiv_ClearTermColors() \
    printf("\x1B[0m");

static char* hiv_ColorToEscapeCode(hiv_TermColors color, int isBG)
{
    if (isBG >= 1)
    {
        switch (color)
        {
            case HIV_TERM_CLEAR:         return "\x1B[00m";

            case HIV_TERM_BLACK:         return "\x1B[40m";
            case HIV_TERM_RED:           return "\x1B[41m";
            case HIV_TERM_GREEN:         return "\x1B[42m";
            case HIV_TERM_YELLOW:        return "\x1B[43m";
            case HIV_TERM_BLUE:          return "\x1B[44m";
            case HIV_TERM_MAGENTA:       return "\x1B[45m";
            case HIV_TERM_CYAN:          return "\x1B[46m";
            case HIV_TERM_WHITE:         return "\x1B[47m";

            case HIV_TERM_LIGHT_BLACK:   return "\x1B[100m";
            case HIV_TERM_LIGHT_RED:     return "\x1B[101m";
            case HIV_TERM_LIGHT_GREEN:   return "\x1B[102m";
            case HIV_TERM_LIGHT_YELLOW:  return "\x1B[130m";
            case HIV_TERM_LIGHT_BLUE:    return "\x1B[104m";
            case HIV_TERM_LIGHT_MAGENTA: return "\x1B[105m";
            case HIV_TERM_LIGHT_CYAN:    return "\x1B[106m";
            case HIV_TERM_LIGHT_WHITE:   return "\x1B[107m";
            default: return "";
        }
    } else
    {
        switch (color)
        {
            case HIV_TERM_CLEAR:         return "\x1B[00m";

            case HIV_TERM_BLACK:         return "\x1B[30m";
            case HIV_TERM_RED:           return "\x1B[31m";
            case HIV_TERM_GREEN:         return "\x1B[32m";
            case HIV_TERM_YELLOW:        return "\x1B[33m";
            case HIV_TERM_BLUE:          return "\x1B[34m";
            case HIV_TERM_MAGENTA:       return "\x1B[35m";
            case HIV_TERM_CYAN:          return "\x1B[36m";
            case HIV_TERM_WHITE:         return "\x1B[37m";

            case HIV_TERM_LIGHT_BLACK:   return "\x1B[90m";
            case HIV_TERM_LIGHT_RED:     return "\x1B[91m";
            case HIV_TERM_LIGHT_GREEN:   return "\x1B[92m";
            case HIV_TERM_LIGHT_YELLOW:  return "\x1B[93m";
            case HIV_TERM_LIGHT_BLUE:    return "\x1B[94m";
            case HIV_TERM_LIGHT_MAGENTA: return "\x1B[95m";
            case HIV_TERM_LIGHT_CYAN:    return "\x1B[96m";
            case HIV_TERM_LIGHT_WHITE:   return "\x1B[97m";
            default: return "";
        }
    }
}

#ifdef _WIN32
    #include <windows.h>

    static void hiv_TermClear()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        COORD homeCoords = {0,0};
        DWORD cellCount;
        HANDLE hStdOut;
        DWORD count;

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE)             return;
        if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;

        cellCount = csbi.dwSize.X*csbi.dwSize.Y;

        if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ',      cellCount, homeCoords, &count)) return;
        if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

        SetConsoleCursorPosition( hStdOut, homeCoords );
    }
#else
    #include <unistd.h>
    #include <term.h>

    static void hiv_TermClear()
    {
        if (!cur_term)
        {
            int result;
            setupterm(NULL, STDOUT_FILENO, &result);

            if (result <= 0)
                return;
        }

        putp(tigetstr( "clear" ));
    }
#endif
