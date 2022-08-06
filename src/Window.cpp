#include <Window.hpp>

Window::Window(WindowType type) : 
    _offset(3), 
    _text_buffer(0), 
    _column_texts({"Asset", "Latest", "Market cap MIL", "Currency","P/E", "Trend"}),
    _text_buffer_tracker(std::vector<size_t>(_column_texts.size(), 0))
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
    size_t r_offset = 1;
    _text_buffer += r_offset;
    _text_buffer_tracker[0] = r_offset;
    const size_t increment = std::round(COLS / _column_texts.size());

    mvwprintw(stdscr, 0, r_offset, _infotxt.c_str());
    mvwprintw(stdscr, 0, _infotxt.size()+r_offset+2, _asset_option[0].c_str());
    mvwprintw(stdscr, 1, _infotxt.size()+r_offset+2, _asset_option[1].c_str());
    mvwprintw(stdscr, 2, r_offset, _column_texts[0].c_str());

    for (size_t i = 1; i < _column_texts.size(); i++)
    {
        _text_buffer += increment;
        if (i == _column_texts.size() - 1)
        {
            _text_buffer = COLS;
        }
        const int text_x_pos = _text_buffer - _column_texts[i].size() - r_offset;
        mvwprintw(stdscr, 2, text_x_pos, _column_texts[i].c_str());
        _text_buffer_tracker[i] = text_x_pos; 
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

std::vector<size_t> Window::get_text_buffer_tracker() const
{
    return _text_buffer_tracker;
}
