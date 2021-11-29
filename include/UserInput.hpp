#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <string>
#include <map>
#include <ncurses.h>

namespace Input
{
    enum attrib {quit, 
                bold,
                underline,
                unbold,};


    int hashtable(const std::string &inp);

    std::string getString();
} // Input

#endif