#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <string>
#include <memory>
#include <cmath>

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
        // Constructor
        Window() = default;
        Window(WindowType type);

        // Init
        void init_text();

        // Getters
        WINDOW* get_win();
        std::string get_asset_options(const int& idx) { return _asset_option[idx]; };
        size_t get_infotxt_size() { return _infotxt.size(); };
        std::vector<size_t> get_text_buffer_tracker() const;
        
        // Modifiers
        void remove_column_text(const int index);
        void add_column_texts(const std::string text);

        // Make private with getters and setters?
        int c_x = 1;
        int c_y = 1;
    private:
        WindowType _type;
        WINDOW* _win;

        std::string _infotxt = "Add asset (a): ";
        std::string _asset_option[2] = {"Crypto", "Stock"};
        const int _asset_text_buffer = _asset_option[0].size() + 8;

        int _offset;
        size_t _text_buffer;
        std::vector<std::string> _column_texts;
        std::vector<size_t> _text_buffer_tracker;
};


#endif