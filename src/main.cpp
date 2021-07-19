#include <iostream>
#include <string>
#include <map>
#include <ncurses.h>
#include <curses.h>

enum attrib {quit, 
            bold, 
            unbold};

std::map<std::string, attrib> queries{{"quit", quit},{"bold", bold},{"clear", unbold}};

int hashtable(const std::string &inp) {
    std::map<std::string, attrib>::iterator it;
    it = queries.find(inp);
    if (it != queries.end())
    {
        return it->second;
    }
}

std::string getString()
{
    std::string msg;
    int n = getch();
    while (n != '\n')
    {
        msg.push_back(n); /* Push back character from getch() to msg while it is not newline */ 
        n = getch();
    }
    return msg;
}

int main() 
{
    /*
        \* Inititialization of ncurses window
    */
    initscr();                 /* Start curses mode     */
    refresh();  /* Part of init phase, mandatory */
    int ch, ROWS, COLS, x, y;
    getmaxyx(stdscr, ROWS, COLS); /* get size of stdscr (terminal) and return to ROWS, COLS */

    WINDOW* win = newwin(ROWS,COLS,0,0); /* Create a window with lines, cols and start coords */

    //wmove(win, 1, 1); /* Moves cursor position? */
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); /* Create a border, if 0 it will take defaults */
    mvwprintw(win, 1, 1, "Hello mate!"); /* Move cursor to 1,1 and print something to the window */
    wrefresh(win); /* Refresh the window, mandatory when changes occur */
    cbreak(); /* Disable line buffer (raw() works similar) */
    noecho(); /* Dont show key on terminal */
    keypad(stdscr, TRUE); /* Enable keypad input (F-keys, arrows etc.) */
    
    while (true)
    {
        if (ch != ERR)
        {
            getyx(win,y,x);
            wmove(win,y+1,1);
            if ((wprintw(win,"%s","Now I'm here")) == ERR)
            {
                std::cout << "Error";
            }
        }
        switch (hashtable(getString()))
        {
            case(0):
                goto endloop;
            case(1):
                wattron(win, A_BOLD);
                break;
            case(2):
                wattroff(win, A_BOLD);
                break;
        }

        wrefresh(win);
    }

    endloop:
        endwin();                  /* End curses mode    */

    return 0;
}
