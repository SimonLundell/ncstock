# ncstock
Track stock

## ncurses ##

## POCO ##
To get Poco to work, have to:
- In cmake:

```
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lncursesw -lPocoNet")
```

```
target_link_libraries(ncstock PRIVATE ncursesw PocoNet
```

If error "./ncstock: error while loading shared libraries: libPocoNet.so.80: cannot open shared object file: No such file or directory"

Do:

```
LD_LIBRARY_PATH=/usr/local/lib
export LD_LIBRARY_PATH
make
./ncstock
```

## Samplecode 1 ##

/*std::string messageToPrint = getString();
switch (hashtable(messageToPrint))
{
    case(0):
        goto endloop;
    case(1):
        wattron(win, A_BOLD);
        break;
    case(2):
        wattron(win, A_UNDERLINE);
        break;
    case(3):
        wattroff(win, A_BOLD);
        wattroff(win, A_UNDERLINE);
        break;
        
}*/

## Samplecode 2 ##

/*
getyx(win,y,x);
wmove(win,y+1,1);
auto msg = messageToPrint.c_str();

if (wprintw(win,"%s", msg) == ERR)
{
    std::cout << "Error";
}
*/