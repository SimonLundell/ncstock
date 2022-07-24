#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <string>
#include <memory>

#include <ncurses.h>
#include <curses.h>

#include <WindowManip.hpp>

#define DEFAULT 1
#define UPTREND 2
#define DOWNTREND 3
#define CURRENT_ROW 4

extern int ROWS, COLS;

enum WindowType
{
    MAIN = 0,
    OPTIONS
};

class Window
{
    public:
        Window(WindowType type);
        WINDOW* get_win();
        std::string get_asset_options(const int& idx) { return _asset_option[idx]; };

        int c_x = 1;
        int c_y = 1;
    private:
        WindowType _type;
        WINDOW* _win;

        std::string _infotxt = "Add asset: \"a\"";
        std::string _asset_option[2] = {"Crypto", "Stock"};

};


#endif