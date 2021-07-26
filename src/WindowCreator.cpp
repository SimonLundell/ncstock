#include "../include/WindowCreator.hpp"

WINDOW* create_window_wBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y)
{
    WINDOW* local_win = newwin(rows,cols, pos_x, pos_y); /* Create a window with lines, cols and start coords */
    wborder(local_win, 0, 0, 0, 0, 0, 0, 0, 0); /* Create a border, if 0 it will take defaults */
    wrefresh(local_win); /* Refresh the window, mandatory when changes occur */

    return local_win;
}

WINDOW* create_window_uBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y)
{
    WINDOW* local_win = newwin(rows,cols, pos_x, pos_y); /* Create a window with lines, cols and start coords */
    wrefresh(local_win); /* Refresh the window, mandatory when changes occur */

    return local_win;
}