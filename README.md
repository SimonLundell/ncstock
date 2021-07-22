# ncstock
Track stock

## Samplecode 1 ##

/*std::string messageToPrint = getString();
switch (hashtable(messageToPrint))
{
    case(0):
        goto endloop;
    case(1):
        wattron(win, A_BOLD);
        break;
    case(2):
        wattron(win, A_UNDERLINE);
        break;
    case(3):
        wattroff(win, A_BOLD);
        wattroff(win, A_UNDERLINE);
        break;
        
}*/

## Samplecode 2 ##

/*
getyx(win,y,x);
wmove(win,y+1,1);
auto msg = messageToPrint.c_str();

if (wprintw(win,"%s", msg) == ERR)
{
    std::cout << "Error";
}
*/