#include <iostream>

#include <ncurses.h>
#include <curses.h>
#include "../include/WindowCreator.hpp"

#define UPTREND 1
#define DOWNTREND 2
#define CURRENT_ROW 3

int ROWS, COLS;


int main() 
{
    int ch, x, y;
    int c_x, c_y;
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
    mvwprintw(stdscr, 0, 0, "Quit: quit. Bold text: bold. Clear attributes: clear");
    wrefresh(stdscr);

    if (has_colors() == FALSE) 
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    init_pair(DOWNTREND, COLOR_RED, COLOR_BLACK);
    init_pair(UPTREND, COLOR_GREEN, COLOR_BLACK);
    init_pair(CURRENT_ROW, COLOR_WHITE, COLOR_RED);
    
    cbreak(); /* Disable line buffer (raw() works similar) */
    noecho(); /* Dont show key on terminal */
    keypad(stdscr, TRUE); /* Enable keypad input (F-keys, arrows etc.) */

    /* Window creation */
    WINDOW* win = create_window_wBorder(ROWS-1, COLS, 1, 0);
    /*
    for (int i = 1; i < ROWS-2; i++)
    {
        wmove(win,i,1);
        wattron(win, COLOR_PAIR(UPTREND));
        waddch(win,ACS_UARROW);
        wattroff(win, COLOR_PAIR(UPTREND));
        wattron(win, COLOR_PAIR(DOWNTREND));
        waddch(win, ACS_DARROW);
        wattroff(win, COLOR_PAIR(DOWNTREND));
    }
    */

    wrefresh(win);
    getyx(win, c_y, c_x);
    while (true)
    {
        if ((ch = getch()) != ERR)
        {
            switch (ch)
            {
                case KEY_RESIZE:
                    werase(win);
                    getmaxyx(stdscr, ROWS, COLS);
                    wresize(win, ROWS-1, COLS-1);
                    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
                    break;
                case KEY_UP:
                    getyx(win,c_y,c_x);
                    c_y -= 1;
                    wmove(win, c_y, c_x);
                    break;
                case KEY_DOWN:
                    getyx(win,c_y,c_x);
                    c_y += 1;
                    wmove(win, c_y, c_x);
                    break;
                case KEY_LEFT:
                    getyx(win,c_y,c_x);
                    c_x -= 1;
                    wmove(win, c_y, c_x);
                    break;
                case KEY_RIGHT:
                    getyx(win,c_y,c_x);
                    c_x += 1;
                    wmove(win, c_y, c_x);
                    break;
            }
        }
        wrefresh(win);
    }

    //endloop:
    endwin();                  /* End curses mode    */

    return 0;
}
