#ifndef WINDOW_MANIP_H
#define WINDOW_MANIP_H
#include <ncurses.h>
#include <curses.h>

WINDOW* create_window_wBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y);

WINDOW* create_window_uBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y);

void HorizontalPosition(WINDOW* win, int &x, int &y, const int &size, const int &NOHL, const int& HL,const bool &up);

#endif