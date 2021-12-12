#include <Window.hpp>

Window::Window(WindowType type)
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
    mvwprintw(stdscr, 0, 0, "Add asset: \"a\": type -> name");
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
    _win = create_window_wBorder(ROWS-1, COLS, 1, 0);

    curs_set(0); // Hide cursor
}

WINDOW* Window::get_win()
{
    return _win;
}
