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
        HANDLE stdOutHandle;
        DWORD count;

        stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdOutHandle == INVALID_HANDLE_VALUE) 
            return;

        cellCount = csbi.dwSize.X*csbi.dwSize.Y;

        if (!FillConsoleOutputCharacter(stdOutHandle, (TCHAR) ' ', 
                                        cellCount, homeCoords, &count)) 
            return;
        if (!FillConsoleOutputAttribute(stdOutHandle, csbi.wAttributes, 
                                        cellCount, homeCoords, &count)) 
            return;

        SetConsoleCursorPosition( hStdOut, homeCoords );
    }

    static void hiv_GetTermSize(uint32_t* columns, uint32_t* rows)
    {
        CONSOLE_SCREEN_BUFFER csbi;
        HANDLE stdOutHandle;

        stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdOutHandle == INVALID_HANDLE_VALUE) 
            return;

        GetConsoleScreenBufferInfo(stdOutHandle, &csbi);
        *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    static void hiv_SetCursorPosition(uint32_t x, uint32_t y)
    {
        COORD position = { x, y };
        HANDLE stdOutHandle;

        stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdOutHandle == INVALID_HANDLE_VALUE) 
            return;
        
        SetCursorPosition(output, position);
    }

    static void hiv_GetCursorPosition(uint32_t* x, uint32_t* y)
    {
        POINT point;
        GetCursorPos(&point);

        *x = point.x;
        *y = point.y;
    }
#else
    #include <sys/ioctl.h>
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>
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

    static void hiv_GetTermSize(uint32_t* columns, uint32_t* rows)
    {
        struct winsize max;
        ioctl(0, TIOCGWINSZ, &max);
        *colums = max.ws_column;
        *rows   = max.ws_row;
    }

    static void hiv_SetCursorPosition(uint32_t x, uint32_t y)
    {
        printf("\033[%d;%dH", y, x);
    }

    static void hiv_GetCursorPosition(uint32_t* x, uint32_t* y)
    {
        char buffer[30] = 0;

        struct termios term;
        struct termios restore;

        tcgetattr(0, &term);
        tcgetattr(0, &restore);
        term.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(0, TCSANOW, &term);
        write(1, "\033[6n", 4);
    
        int ret, pow, i = 0; char character = 0;
        for (; character != 'R'; i++)
        {
            ret = read(0, &character, 1);
            if (!ret) 
            {
                tcsetattr(0, TCSANOW, &restore);
                fprintf(stderr, "[ERR: hiv_GetCursorPosition]: Error reading response.\n");
                return;
            }
            buffer[i] = character;

            if (i < 2) 
            {
                tcsetattr(0, TCSANOW, &restore);
                return;
            }

            for (i -= 2, pow = 1; buffer[i] != ';'; i--, pow *= 10)
                *x = *x + (buffer[i] - '0') * pow;
            for (i -= 1, pow = 1; buffer[i] != '['; i--, pow *= 10)
                *y = *y + (buffer[i] - '0') * pow;

            tcsetattr(0, TCSANOW, &restore);
        }
    }
#endif
