#include "display_functions.hpp"
//display tools
//implementation

void contentDisplay(Coord coord, std::string content) 
{
    //convert string to char* 
    int length = content.length();
    char* tmp = new char[length]; //for content
    for (int i = 0; i < length; i++) 
    {
        tmp[i] = content[i]; //copy from content string
    }
    mvprintw(coord.y, coord.x, "%s", tmp);
    //clear memory
    delete [] tmp;
}

void flashingDisplay(Coord coord, std::string content, Timer& timer) 
{
    //convert string to char* 
    int length = content.length();
    char* tmp = new char[length]; //for content
    char* blank = new char[length]; //for blank
    for (int i = 0; i < length; i++) 
    {
        tmp[i] = content[i]; //copy from content string
        blank[i] = ' '; //make a blank list
    }
    //flashing
    //print content
    mvprintw(coord.y, coord.x, "%s", tmp);
    if((timer.getCount() % 5 ) == 0) 
    {
        //print blank
        mvprintw(coord.y, coord.x, "%s", blank);
    }
    //clear memory
    delete [] tmp;
    delete [] blank;
}