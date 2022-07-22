#include "../include/WindowManip.hpp"

WINDOW* create_window_wBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y)
{
    WINDOW* local_win = newwin(rows,cols, pos_x, pos_y); /* Create a window with lines, cols and start coords */
    wborder(local_win, 0, 0, 0, 0, 0, 0, 0, 0); /* Create a border, if 0 it will take defaults */
    wrefresh(local_win); /* Refresh the window, mandatory when changes occur */

    return local_win;
}

WINDOW* create_window_uBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y)
{
    auto local_win = newwin(rows,cols, pos_x, pos_y); /* Create a window with lines, cols and start coords */
    wrefresh(local_win); /* Refresh the window, mandatory when changes occur */

    return local_win;
}

WINDOW* create_new_window(const int &rows, const int &cols, const int &pos_x, const int &pos_y)
{
    auto new_window = newwin(rows, cols, pos_x, pos_y);
    box(new_window,0 ,0);
    wrefresh(new_window);

    return new_window;
}

void delete_current_window(WINDOW* win)
{
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(win);
    delwin(win);
}

void HorizontalPosition(WINDOW* win, int &y, int &x, const int &size, const int &NOHL, const int& HL, const bool &up)
{
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    mvwchgat(win, y, x, size,WA_HORIZONTAL,NOHL,NULL);
    
    getyx(win,y,x); /* TODO: Just getyx once */
    if (up && y == 1)
    {
        y = max_y - 2;
        wmove(win, y, max_x);
    }
    else if (up)
    {
        wmove(win, --y, x);
    }
    else if (!up && y == max_y-2)
    {
        y = 1;
        wmove(win, y, x);
    }
    else
    {
        wmove(win, ++y, x);
    }
    mvwchgat(win,y,x,size,WA_HORIZONTAL,HL,NULL);
}

void r_HorizontalPosition(WINDOW* win, int &y, int &x, const int &size, const int &NOHL, const int& HL)
{
    mvwchgat(win,y,x,size,WA_HORIZONTAL,HL,NULL);
    wmove(win, y, x);
}

void refresh_window(WINDOW* win, AssetManager& a_manager)
{
    wclear(win);
    auto assets = a_manager.get_assets();

    for (size_t i = 0; i < assets.size(); i++)
    {
        wmove(win,i+1,1);
        wprintw(win, a_manager.print_asset_info(i));
    }
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0); // after loop to avoid edge disappear
}