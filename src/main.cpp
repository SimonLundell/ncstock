#include <iostream>
#include <ncurses.h>
#include <curses.h>

int main() 
{
    initscr();                 /* Start curses mode     */

    WINDOW* win = newwin(30,10,0,0);

    cbreak();
    noecho();
    int ch;
    
    //nodelay(stdscr, true);
    getch();
    while(true)
    {
        if ((ch = getch()) == ERR)
        {
            std::cout << "Something is wrong\n";
        }
        else
        {
            std::cout << "A key is pressed\n";
            //wrefresh(win);
        }
    }
    

    wrefresh(win);

    

    endwin();                  /* End curses mode    */

    return 0;
}
