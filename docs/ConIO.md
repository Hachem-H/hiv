# ConIO

A module to interact with the terminal and the console. It features functions to move the cursor around, and change colors. For windows platforms, most functions are implemented using the `Win32 API`,  for unix based platfroms (_Linux, MacOS_), standard ANSII escape codes are used in conjunction with `termios` and `ioctl` and a couple more libraries.

### `hiv_TermColors`
ASCII codes for colors and color manipulation.

```c
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
```
### `hiv_SetTermColor(fg, bg)`
Sets color for output of characters, `fg` and `bg` are both numbers defined in the `hiv_TermColors` enum.

### `hiv_ClearTermColors(fg, bg)`
Resets colors being used. Usually called after `hiv_SetTermColor`

### `hiv_TermClear()`
Clears the terminal buffer

### `hiv_GetTermSize(unsigned int* columns, unsigned int* rows)`
Gets the terminal size in columns and rows, then puts them in their respective fields.

### `hiv_SetCursorPosition(unsigned int x, unsigned int y)`
Set the cursor position to `x, y`

### `hiv_GetCursorPosition(unsigned int* x, unsigned int* y)`
Gets the cursor's `x` and `y` coordinate, then puts them in their respective fields.
