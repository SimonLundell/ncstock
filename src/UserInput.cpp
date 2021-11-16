#include "../include/UserInput.hpp"

int hashtable(const std::string &inp) 
{
    std::map<std::string, attrib>::iterator it;
    it = queries.find(inp);
    if (it != queries.end())
    {
        return it->second;
    }
    return 0;
}

std::string getString()
{
    std::string msg;
    int n = getch();
    while (n != '\n')
    {
        msg.push_back(n); /* Push back character from getch() to msg while it is not newline */ 
        n = getch();
    }
    return msg;
}