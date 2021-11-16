#include <iostream>
#include <memory>

#include <ncurses.h>
#include <curses.h>
#include "../include/WindowManip.hpp"
#include "../include/Asset.hpp"
#include "../include/Window.hpp"
#include "../include/AssetManager.hpp"

int ROWS, COLS;

int main() 
{
    Window window(WindowType::MAIN);
    int ch; // To store keystrokes
    AssetManager a_manager;
    a_manager.add_asset(std::make_shared<Asset>(AssetType::CRYPTO, "BTC"));
    a_manager.add_asset(std::make_shared<Asset>(AssetType::STOCK, "IBM"));

    for (size_t i = 0; i < a_manager.assets.size(); i++)
    {
        wmove(window.get_win(),i+1,1);
        wprintw(window.get_win(), (a_manager.assets[i]->getCurrency() + " " + std::to_string(a_manager.assets[i]->getExchangeRate()) + "\n").c_str());
    }
    
    //for (int i = 0; i < assets.size(); i++)
    //{
    //    wmove(win,i+1,1);
    //    whitespace = assets[i]->getCurrency() + " " + std::to_string(assets[i]->getExchangeRate()) + "\n";
    //    //wattron(win, COLOR_PAIR(UPTREND));
    //    //waddch(win,ACS_UARROW);
    //    //wattron(win, COLOR_PAIR(DOWNTREND));
    //    //waddch(win, ACS_DARROW);
    //    wprintw(win,whitespace.c_str());
    //}
    
    
    wmove(window.get_win(),window.c_y, window.c_x);
    mvwchgat(window.get_win(),window.c_y,window.c_x,COLS-2,WA_HORIZONTAL,CURRENT_ROW,NULL);

    wrefresh(window.get_win());

    while (true)
    {
        if ((ch = getch()) != ERR)
        {
            switch (ch)
            {
                case KEY_RESIZE:
                    getyx(window.get_win(), window.c_y, window.c_x);
                    werase(window.get_win());
                    getmaxyx(stdscr, ROWS, COLS);
                    wresize(window.get_win(), ROWS-1, COLS-1);
                    wborder(window.get_win(), 0, 0, 0, 0, 0, 0, 0, 0);
                    wmove(window.get_win(), window.c_y, window.c_x);
                    break;
                
                case KEY_UP:
                    HorizontalPosition(window.get_win(), window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW, true);
                    break;
                case KEY_DOWN:
                    HorizontalPosition(window.get_win(), window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW, false);
                    break;
                //case 10: // KEY_ENTER refers to numpad enter. ASCII 10 is "normal" enter
                //    current_window = create_new_window(ROWS, COLS, 0, 0);
                //    break;
                //case 23: // KEY_ESCAPE
                //    delete_current_window(current_window);
                //    break;

                {
                    break;
                }
            }
        }
        wrefresh(window.get_win());
    }

    //endloop:
    endwin();                  /* End curses mode    */

    return 0;
}
