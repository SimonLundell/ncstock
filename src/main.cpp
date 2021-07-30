#include <iostream>

#include <ncurses.h>
#include <curses.h>
#include "../include/WindowCreator.hpp"

#define DEFAULT 1
#define UPTREND 2
#define DOWNTREND 3
#define CURRENT_ROW 4

int ROWS, COLS;


int main() 
{
    int ch, x, y;
    int c_x, c_y;
    WINDOW* red_win = nullptr;

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
    /* Make color pairs */
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(DOWNTREND, COLOR_RED, COLOR_BLACK);
    init_pair(UPTREND, COLOR_GREEN, COLOR_BLACK);
    init_pair(CURRENT_ROW, COLOR_WHITE, COLOR_RED);
    
    
    cbreak(); /* Disable line buffer (raw() works similar) */
    noecho(); /* Dont show key on terminal */
    keypad(stdscr, TRUE); /* Enable keypad input (F-keys, arrows etc.) */

    /* Main Window creation */
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
    wmove(win,1,0);
    getyx(win, c_y, c_x);
    red_win = create_window_uBorder(1,COLS-2,c_y+1,c_x+1);
    wbkgd(red_win, COLOR_PAIR(CURRENT_ROW));

    wrefresh(win);
    wrefresh(red_win);

    while (true)
    {
        if ((ch = getch()) != ERR)
        {
            switch (ch)
            {
                case KEY_RESIZE:
                    getyx(win, c_y, c_x);
                    werase(win);
                    getmaxyx(stdscr, ROWS, COLS);
                    wresize(win, ROWS-1, COLS-1);
                    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
                    wmove(win, c_y, c_x);
                    break;
                
                case KEY_UP:
                    if (red_win != nullptr)
                    {
                        wbkgd(red_win, COLOR_PAIR(DEFAULT));
                        wrefresh(red_win);
                    }
                    getyx(win,c_y,c_x); /* TODO: Just getyx once */
                    wmove(win, --c_y, c_x);
                    wrefresh(win);
                    
                    red_win = create_window_uBorder(1,COLS-2,c_y+1,c_x+1);
                    wbkgd(red_win, COLOR_PAIR(CURRENT_ROW));

                    break;
                case KEY_DOWN:
                    if (red_win != nullptr)
                    {
                        wbkgd(red_win, COLOR_PAIR(DEFAULT));
                        wrefresh(red_win);
                    }
                    getyx(win,c_y,c_x);
                    wmove(win, ++c_y, c_x);
                    wrefresh(win);

                    red_win = create_window_uBorder(1,COLS-2,c_y+1,c_x+1);
                    wbkgd(red_win, COLOR_PAIR(CURRENT_ROW));

                    break;
            }
        }
        wrefresh(red_win);
        wrefresh(win);
    }

    //endloop:
    endwin();                  /* End curses mode    */

    return 0;
}
