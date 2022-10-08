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

## Jenkins ##
Jenkins will now check the builds