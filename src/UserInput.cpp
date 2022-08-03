#include "../include/UserInput.hpp"

namespace Input
{
    int hashtable(const std::string &inp) 
    {
        std::map<std::string, attrib> queries{{"quit", quit},{"bold", bold},{"underline", underline},{"clear", unbold}};
        std::map<std::string, attrib>::iterator it;
        it = queries.find(inp);
        if (it != queries.end())
        {
            return it->second;
        }
        return 0;
    }

    std::string getString(Window& window)
    {
        std::string msg;
        int c_y, c_x;
        
        getyx(window.get_win(), c_y, c_x);

        int n = getch();
        mvwaddch(window.get_win(), c_y, c_x, n);
        c_x++;
        
        wmove(window.get_win(), c_y, c_x);
        wrefresh(window.get_win());
        while (n != '\n')
        {
            msg.push_back(n); /* Push back character from getch() to msg while it is not newline */ 
            n = getch();
            mvwaddch(window.get_win(), c_y, c_x, n);
            c_x++;
            wmove(window.get_win(), c_y, c_x);
            wrefresh(window.get_win());
        }
        return msg;
    }
    
    void highlight_choice(Window &window, int &highlight, int &choice)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
                wattron(stdscr, A_REVERSE);
            mvwprintw(stdscr, i, window.get_infotxt_size()+2, window.get_asset_options(i).c_str());
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
    }
    
    // std::string getString_stdscr()
    // {
    //     std::string asset_type = window.get_asset_options(highlight);
    //     std::string msg;
    //     wmove(stdscr, highlight, window.get_infotxt_size() + 2 + window.get_asset_options(highlight).size()+1);
    //     int c_y, c_x;
        
    //     getyx(stdscr, c_y, c_x);

    //     int n = getch();
    //     mvwaddch(stdscr, c_y, c_x, n);
    //     c_x++;
        
    //     wmove(stdscr, c_y, c_x);
    //     while (n != '\n')
    //     {
    //         msg.push_back(n); /* Push back character from getch() to msg while it is not newline */ 
    //         n = getch();
    //         mvwaddch(stdscr, c_y, c_x, n);
    //         c_x++;
    //         wmove(stdscr, c_y, c_x);
    //         wrefresh(stdscr);
    //     }
    //     AssetType type;
    //     (asset_type == "Crypto") ? type = CRYPTO : type = STOCK;
    //     a_manager.add_asset(type, msg);
    //     for (unsigned int j = 0; j < msg.size()+2; j++)
    //         mvwdelch(stdscr, c_y, c_x-j);
    //     wattroff(stdscr, A_REVERSE);
    // }
    
} // input