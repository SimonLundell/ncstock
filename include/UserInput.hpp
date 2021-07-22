#include <string>
#include <map>
#include <ncurses.h>

enum attrib {quit, 
            bold,
            underline,
            unbold,};

std::map<std::string, attrib> queries{{"quit", quit},{"bold", bold},{"underline", underline},{"clear", unbold}};

int hashtable(const std::string &inp);

std::string getString();