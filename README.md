# hiv
hiv is a robust, header only standard library for C. Like the already prexisting standard library, its devided into modules; A module for `FileIO`, a module for `Dynamic Arrays and Buffers` and so on and so forth. Each header is included in the `include` directory, so in order to use it in your own project, all you have to do is add that directory in your include path and you would be good to go.

*_NOTE FOR WINDOWS USERS:_*: 
The `ConIO` module relies on ANSII escape codes for colours which are not natively supported. Most functions are implemented in the Win32 except for the ones which deal with colours. To fix this, run the following command:
```bat
reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f
```


## Modules
- `FileIO`: Contains everything which has to do with files, (_reading and writing_).
- `ConIO`: Contains everything which has to do terminal and console. (_clearing, setting text colors_)

## Contributing
This is quite a large project which will constantly be in development, whenever I want a new feature, I just add it in. Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. Please make sure to update tests as appropriate.
