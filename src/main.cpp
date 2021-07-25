#include <iostream>

#include <ncurses.h>
#include <curses.h>

int ROWS, COLS;


int main() 
{
    int ch, x, y;
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

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    
    cbreak(); /* Disable line buffer (raw() works similar) */
    noecho(); /* Dont show key on terminal */
    keypad(stdscr, TRUE); /* Enable keypad input (F-keys, arrows etc.) */

    /* Window inits */
    WINDOW* win = newwin(ROWS-1,COLS,1,0); /* Create a window with lines, cols and start coords */
    wmove(win, 1, 1); /* Moves cursor position? */
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); /* Create a border, if 0 it will take defaults */
    wrefresh(win); /* Refresh the window, mandatory when changes occur */

    for (int i = 1; i < ROWS-2; i++)
    {
        wmove(win,i,1);
        wattron(win, COLOR_PAIR(2));
        waddch(win,ACS_UARROW);
        wattroff(win, COLOR_PAIR(2));
        wattron(win, COLOR_PAIR(1));
        waddch(win, ACS_DARROW);
        wattroff(win, COLOR_PAIR(1));
        
    }

    wrefresh(win);
    
    while (true)
    {
        if ((ch = getch()) != ERR)
        {
           if (ch == KEY_RESIZE)
           {
                werase(win);
                getmaxyx(stdscr, ROWS, COLS);
                wresize(win, ROWS-1,COLS);
                wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
           }
        }

        wrefresh(win);
    }

    //endloop:
    endwin();                  /* End curses mode    */

    return 0;
}
