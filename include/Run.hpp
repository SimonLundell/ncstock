
#include <iostream>
#include <memory>
#include <chrono>

#include <ncurses.h>
#include <curses.h>
#include "../include/UserInput.hpp"
#include "../include/WindowManip.hpp"
#include "../include/Asset.hpp"
#include "../include/Window.hpp"
#include "../include/AssetManager.hpp"

int ROWS, COLS;

struct Run
{
    static void run()
    {
        auto now = std::chrono::system_clock::now();
        [[maybe_unused]]auto timer = now + std::chrono::seconds(10);
        int ch; // To store keystrokes

        // Initialize window with border
        Window window(WindowType::MAIN);

        // Asset setup
        AssetManager a_manager;
        auto win = window.get_win();

        for (size_t i = 0; i < a_manager.assets.size(); i++)
        {
            wmove(win,i+1,1);
            wprintw(win, a_manager.print_asset_info(i));
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
        
        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); // Draw border again to avoid edge disappear due to loop
        wmove(win, window.c_y, window.c_x);
        mvwchgat(win, window.c_y, window.c_x, COLS-2, WA_HORIZONTAL, CURRENT_ROW,NULL);

        wrefresh(win);

        while (true)
        {
            /*now = std::chrono::system_clock::now();
            if (now > timer)
            {
                a_manager.update_assets();
                timer = now + std::chrono::seconds(10);
            }
            */
            if ((ch = getch()) != ERR)
            {
                switch (ch)
                {
                    case KEY_RESIZE:
                        getyx(win, window.c_y, window.c_x);
                        werase(win);
                        getmaxyx(stdscr, ROWS, COLS);
                        wresize(win, ROWS-1, COLS-1);
                        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
                        wmove(win, window.c_y, window.c_x);
                        break;
                    
                    case KEY_UP:
                        HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW, true);
                        break;
                    case KEY_DOWN:
                        HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW, false);
                        break;
                    case 330: // Delete
                        getyx(win, window.c_y, window.c_x);
                        a_manager.remove_asset(window.c_y);
                        wclear(win);
                        
                        for (size_t i = 0; i < a_manager.assets.size(); i++)
                        {
                            wmove(win,i+1,1);
                            wprintw(win, a_manager.print_asset_info(i));
                        }
                        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); // after loop to avoid edge disappear
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW);
                        wmove(win, window.c_y, window.c_x);
                        
                        break;
                    case 97:
                        getyx(win, window.c_y, window.c_x);
                        std::string asset_type = Input::getString(window);
                        std::string new_asset = Input::getString(window);
                        AssetType type;

                        (asset_type == "crypto") ? type = CRYPTO : type = STOCK;
                        a_manager.add_asset(type, new_asset);

                        wclear(win);
                        
                        for (size_t i = 0; i < a_manager.assets.size(); i++)
                        {
                            wmove(win,i+1,1);
                            wprintw(win, a_manager.print_asset_info(i));
                        }
                        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); // after loop to avoid edge disappear
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW);
                        wmove(win, window.c_y, window.c_x);
                        
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
            wrefresh(win);
        }

        //endloop:
        endwin();                  /* End curses mode    */
    } // void.run
}; // Struct Run