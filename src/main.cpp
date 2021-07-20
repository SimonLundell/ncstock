#include <iostream>
#include <string>
#include <map>
#include <ncurses.h>
#include <curses.h>

int ROWS, COLS;

enum attrib {quit, 
            bold,
            underline,
            unbold};

std::map<std::string, attrib> queries{{"quit", quit},{"bold", bold},{"underline", underline},{"clear", unbold}};

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
        if (n == KEY_RESIZE)
        {
            std::cout << "Resizing...";
        }
    }
    return msg;
}

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
        std::string messageToPrint = getString();
        switch (hashtable(messageToPrint))
        {
            case(0):
                goto endloop;
            case(1):
                wattron(win, A_BOLD);
                break;
            case(2):
                wattron(win, A_UNDERLINE);
                break;
            case(3):
                wattroff(win, A_BOLD);
                wattroff(win, A_UNDERLINE);
                break;
        }

        if (ch != ERR)
        {
            getyx(win,y,x);
            wmove(win,y+1,1);
            if ((wprintw(win,"%s", messageToPrint.c_str())) == ERR)
            {
                std::cout << "Error";
            }
        }

        wrefresh(win);
    }

    endloop:
        endwin();                  /* End curses mode    */

    return 0;
}
