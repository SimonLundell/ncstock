#ifndef WINDOW_MANIP_H
#define WINDOW_MANIP_H
#include <ncurses.h>
#include <curses.h>
#include <future>

#include "AssetManager.hpp"
#include "Window.hpp"


WINDOW* create_window_wBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y);

WINDOW* create_window_uBorder(const int &rows, const int &cols, const int &pos_x, const int &pos_y);

WINDOW* create_new_window(const int &rows, const int &cols, const int &pos_x, const int &pos_y);

void delete_current_window(WINDOW* win);

void HorizontalPosition(WINDOW* win, int &y, int &x, const int &size, const int &NOHL, const int& HL,const bool &up);

void r_HorizontalPosition(WINDOW* win, int &y, int &x, const int &size, const int &NOHL, const int& HL);

void refresh_window_and_update(WINDOW* win, AssetManager& a_manager);

void refresh_window(WINDOW* win, AssetManager& a_manager);


#endif