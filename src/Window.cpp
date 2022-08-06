#include <Window.hpp>

Window::Window(WindowType type) : 
    _offset(3), 
    _buffer(0), 
    _column_texts({"Asset", "Latest SEK USD", "Market cap MSEK", "P/E", "Trend"})
{
    if (type == WindowType::MAIN)
    {
        setlocale(LC_ALL, "");
        /*
            \* Inititialization of ncurses window
        */
        initscr();                 /* Start curses mode     */
        start_color();
        assume_default_colors(COLOR_WHITE, COLOR_BLACK);
        refresh();  /* Part of init phase, mandatory */
        
        /* stdscr inits */
        getmaxyx(stdscr, ROWS, COLS); /* get size of stdscr (terminal) and return to ROWS, COLS */
        init_text(); /* Set starting texts */

        wrefresh(stdscr);

        if (has_colors() == FALSE) 
        {
            endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }
        /* Make color pairs */
        init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
        init_pair(DOWNTREND, COLOR_RED, COLOR_BLACK);
        init_pair(UPTREND, COLOR_GREEN, COLOR_BLACK);
        init_pair(CURRENT_ROW, COLOR_BLACK, COLOR_RED);
        
        
        cbreak(); /* Disable line buffer (raw() works similar) */
        noecho(); /* Dont show key on terminal */
        keypad(stdscr, TRUE); /* Enable keypad input (F-keys, arrows etc.) */

        /* Main Window creation */
        _win = create_window_wBorder(ROWS-_offset, COLS, _offset, 0);

        curs_set(0); // Hide cursor
    }
    else
    {
        exit(-1);
    }
}

void Window::init_text()
{
    mvwprintw(stdscr, 0, 0, _infotxt.c_str());
    mvwprintw(stdscr, 0, _infotxt.size()+2, _asset_option[0].c_str());
    mvwprintw(stdscr, 1, _infotxt.size()+2, _asset_option[1].c_str());
    mvwprintw(stdscr, 2, 0, _column_texts[0].c_str());

    const size_t increment = std::round(COLS / _column_texts.size());
    _buffer += increment;

    for (size_t i = 1; i < _column_texts.size(); i++)
    {
        _buffer += increment;
        mvwprintw(stdscr, 2, _buffer - _column_texts[i].size(), _column_texts[i].c_str());
    }
}

WINDOW* Window::get_win()
{
    return _win;
}

void Window::add_column_texts(const std::string text)
{
    _column_texts.push_back(text);
}

void Window::remove_column_text(const int index)
{
    _column_texts.erase(_column_texts.begin() + index);
}
