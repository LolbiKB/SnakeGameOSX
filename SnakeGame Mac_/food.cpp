#include "food.hpp"
#include "string"
#include <ncurses.h>

//constructors
Food::Food() 
{
    status = 0;
}
//accessor(s)
int Food::getCurrentOption() 
{
    return currentOption;
}
int Food::getStatus() 
{
    return status;
}

//modifier(s)
void Food::setOption(int option) 
{
    //set option
    currentOption = option;
    //set option to shape
    try
    {
        if (option >= 0 && option <= 4)
            setShape(shapeOptions[option]);
        else
            throw("Food Option Out of Range");
    }
    catch(char* error)
    {
        mvprintw(15,15,"%s",error);
    }
}
void Food::setStatus(int status) 
{
    //set
    this->status = status;
}
