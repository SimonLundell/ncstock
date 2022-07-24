#include <iostream>
#include <memory>
#include <chrono>
#include <future>

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
        int ch; // To store keystrokes

        int choice;
        int highlight = 0;

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
        
        wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); // Draw border again to avoid edge disappear due to loop
        wmove(win, window.c_y, window.c_x);
        mvwchgat(win, window.c_y, window.c_x, COLS-3, WA_HORIZONTAL, CURRENT_ROW, NULL);

        wrefresh(win);

        auto now = std::chrono::system_clock::now();
        [[maybe_unused]]auto timer = now + std::chrono::seconds(10);

        while (true)
        {
            // now = std::chrono::system_clock::now();
            
            if ((ch = getch()) != ERR && now < timer)
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
                        HorizontalPosition(win, window.c_y, window.c_x, COLS-3, DEFAULT, CURRENT_ROW, true);
                        break;
                    
                    case KEY_DOWN:
                        HorizontalPosition(win, window.c_y, window.c_x, COLS-3, DEFAULT, CURRENT_ROW, false);
                        break;
                    
                    case KEY::del : // Delete
                        getyx(win, window.c_y, window.c_x);
                        a_manager.remove_asset(window.c_y);

                        // wrefresh(win);
                        refresh_window(win, a_manager);
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-3, DEFAULT, CURRENT_ROW);

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
                        while(true)
                        {
                            for (int i = 0; i < 2; i++)
                            {
                                if (i == highlight)
                                    wattron(stdscr, A_REVERSE);
                                mvwprintw(stdscr, i, COLS-(window.get_asset_options(0).size()+8), window.get_asset_options(i).c_str());
                                wattroff(stdscr, A_REVERSE);
                            }
                            choice = wgetch(stdscr);

                            switch(choice)
                            {
                                case KEY_UP:
                                    highlight--;
                                    if (highlight == -1)
                                        highlight = 0;
                                    break;
                                case KEY_DOWN:
                                    highlight++;
                                    if (highlight == 2)
                                        highlight = 1;
                                    break;
                                default:
                                    break;
                            }
                            if (choice == 10)
                            {
                                std::string asset_type = window.get_asset_options(highlight);
                                std::string msg;
                                wmove(stdscr, highlight, COLS-(window.get_asset_options(highlight).size()+1));
                                int c_y, c_x;
                                
                                getyx(stdscr, c_y, c_x);

                                int n = getch();
                                mvwaddch(stdscr, c_y, c_x, n);
                                c_x++;
                                
                                wmove(stdscr, c_y, c_x);
                                while (n != '\n')
                                {
                                    msg.push_back(n); /* Push back character from getch() to msg while it is not newline */ 
                                    n = getch();
                                    mvwaddch(stdscr, c_y, c_x, n);
                                    c_x++;
                                    wmove(stdscr, c_y, c_x);
                                    wrefresh(stdscr);
                                }
                                AssetType type;
                                (asset_type == "Crypto") ? type = CRYPTO : type = STOCK;
                                a_manager.add_asset(type, msg);
                                for (unsigned int j = 0; j < msg.size()+2; j++)
                                    mvwdelch(stdscr, c_y, c_x-j);
                                wattroff(stdscr, A_REVERSE);
                                mvwprintw(stdscr, highlight, COLS-(window.get_asset_options(0).size()+8), window.get_asset_options(highlight).c_str());
                                wrefresh(stdscr);
                                refresh_window(win, a_manager);
                                r_HorizontalPosition(win, window.c_y, window.c_x, COLS-3, DEFAULT, CURRENT_ROW);
                                break;
                            }
                        }
                        break;

                    case KEY::c : // c
                        a_manager.save_cache();
                        refresh_window_and_update(win, a_manager);
                        r_HorizontalPosition(win, window.c_y, window.c_x, COLS-3, DEFAULT, CURRENT_ROW);
                        break;

                    //case 10: // KEY_ENTER refers to numpad enter. ASCII 10 is "normal" enter
                    //    break;
                    
                    //case 23: // KEY_ESCAPE
                    //    break;
                }
            }
            else if (now > timer)
            {
                a_manager.save_cache();
                refresh_window(win, a_manager);
                r_HorizontalPosition(win, window.c_y, window.c_x, COLS-3, DEFAULT, CURRENT_ROW);

                timer = now + std::chrono::seconds(10);
            }
            wrefresh(win);
        }

        //endloop:
        endwin();                  /* End curses mode    */
    } // void.run
}; // Struct Run