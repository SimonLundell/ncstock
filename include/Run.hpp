
#include <iostream>
#include <memory>
#include <chrono>

#include <ncurses.h>
#include <curses.h>
#include "../include/Window.hpp"
#include "../include/WindowManip.hpp"
#include "../include/UserInput.hpp"
#include "../include/Asset.hpp"
#include "../include/AssetManager.hpp"
#include "../include/Keyboard.hpp"

int ROWS, COLS;

struct Run
{
    static void run()
    {
        std::string asset_type;
        std::string new_asset;
        auto now = std::chrono::system_clock::now();
        [[maybe_unused]]auto timer = now + std::chrono::seconds(10);
        int ch; // To store keystrokes

        // Initialize window with border
        Window window(WindowType::MAIN);

        // Asset setup
        AssetManager a_manager;
        auto win = window.get_win();

        //a_manager.populate_assets();
        auto raw_info = a_manager.get_raw_info();

        for (size_t i = 0; i < raw_info.size(); i++)
        {
            wmove(win,i+1,1);
            wprintw(win, raw_info[i]);
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
        mvwchgat(win, window.c_y, window.c_x, COLS-2, WA_HORIZONTAL, CURRENT_ROW, NULL);

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
                    
                    case KEY::del : // Delete
                        getyx(win, window.c_y, window.c_x);
                        a_manager.remove_asset(window.c_y);

                        refresh_window(win, a_manager);
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW);

                        break;

                    case KEY::a : // a
                        getyx(win, window.c_y, window.c_x);

                        asset_type = Input::getString(window);
                        new_asset = Input::getString(window);
                        
                        AssetType type;
                        (asset_type == "crypto") ? type = CRYPTO : type = STOCK;
                        a_manager.add_asset(type, new_asset);

                        break;
                    
                    case KEY::b : // b
                        getyx(win, window.c_y, window.c_x);
                        a_manager.populate_assets();
                        refresh_window(win, a_manager);
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW);
                        break;

                    case KEY::c : // c
                        a_manager.save_cache();
                        refresh_window(win, a_manager);
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-2, DEFAULT, CURRENT_ROW);
                        break;

                    //case 10: // KEY_ENTER refers to numpad enter. ASCII 10 is "normal" enter
                    //    break;
                    
                    //case 23: // KEY_ESCAPE
                    //    break;
                }
            }
            wrefresh(win);
        }

        //endloop:
        endwin();                  /* End curses mode    */
    } // void.run
}; // Struct Run