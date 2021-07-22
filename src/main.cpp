#include <iostream>

#include <ncurses.h>
#include <curses.h>

int ROWS, COLS;


int main() 
{
    int ch, x, y;
    /*
        \* Inititialization of ncurses window
    */
    initscr();                 /* Start curses mode     */
    refresh();  /* Part of init phase, mandatory */
    
    /* stdscr inits */
    getmaxyx(stdscr, ROWS, COLS); /* get size of stdscr (terminal) and return to ROWS, COLS */
    mvwprintw(stdscr, 0, 0, "Quit: quit. Bold text: bold. Clear attributes: clear");
    wrefresh(stdscr);

    /* Window inits */
    WINDOW* win = newwin(ROWS-1,COLS,1,0); /* Create a window with lines, cols and start coords */
    wmove(win, 1, 1); /* Moves cursor position? */
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); /* Create a border, if 0 it will take defaults */
    wrefresh(win); /* Refresh the window, mandatory when changes occur */

    cbreak(); /* Disable line buffer (raw() works similar) */
    noecho(); /* Dont show key on terminal */
    keypad(stdscr, TRUE); /* Enable keypad input (F-keys, arrows etc.) */
    
    while (true)
    {
        if ((ch = getch()) != ERR)
        {
           if (ch == KEY_RESIZE)
           {
                werase(win);
                getmaxyx(stdscr, ROWS, COLS);
                wrefresh(stdscr);
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
