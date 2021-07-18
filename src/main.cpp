#include <iostream>
#include <string>
#include <ncurses.h>
#include <curses.h>

#define LINES 25
#define COLS 100

int main() 
{
    initscr();                 /* Start curses mode     */
    refresh();  /* Part of init phase, mandatory */
    int row; int col = 1;

    WINDOW* win = newwin(LINES,COLS,0,0); /* Create a window with lines, cols and start coords */

    wmove(win, row, col); /* Moves cursor position? */
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); /* Create a border, if 0 it will take defaults */
    wprintw(win, "Hello mate!"); /* Print something to the window */
    wrefresh(win); /* Refresh the window, mandatory when changes occur */
    cbreak(); /* Break on key? */
    noecho(); /* Dont show key on terminal */
    while (true)
    {
        if ((getch()) != ERR)
        {
            std::cout << "Jey!";
            row += 1;
            wmove(win, row, col);
            refresh();
        }
    }

    endwin();                  /* End curses mode    */

    return 0;
}
