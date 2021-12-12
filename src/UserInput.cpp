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
} // input