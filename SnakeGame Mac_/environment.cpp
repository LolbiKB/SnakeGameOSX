#include "environment.hpp"

//default constructor
Environment::Environment()
{
    //initialize
    //settings
    borderLength = 0;
    borderWidth = 0;
    borderPerimeter = 0;
    borderChar = ':';

    //timer
    flashingTimer = nullptr;

    //objects
    food.setOption(0);
}
Environment::Environment(int length, int width)
{
    //initialize
    borderLength = length;
    borderWidth = width;
    borderPerimeter = (2 * (borderWidth + borderLength));

    //objects
    food.setShape('*');
}

//modifier(s)
//set border
void Environment::setBorder(int length, int width) 
{
    borderLength = length;
    borderWidth = width;
    borderPerimeter = (2 * (borderWidth + borderLength));
}

//setFoodCoord
void Environment::setFoodCoord(int y, int x)
{
    food.setCoord(y,x);
}
//set flashingTmer
void Environment::setFlashingTimer(Timer& timer) 
{
    flashingTimer = &timer;
}

//print 
void Environment::printBorder(char style) 
{
    //loop through print 
    for (int i = 0; i < borderWidth; i++) 
    {
        for (int j = 0; j < borderLength; j++) 
        {
            if (i == 0 || i == borderWidth-1 || j == 0 || j == borderLength-1) //print border
                mvprintw(i,j,"%c",style);
        }
    }
}
void Environment::printFood(char shape)
{
    //create a string version of shape
    std::string shapeString = "";
    shapeString += shape;
    //print food at food's Coord
    int foodStatus = food.getStatus();
    if (foodStatus == 0)
        mvprintw(food.getCoord().y,food.getCoord().x, "%c" ,shape);
    else if (foodStatus == 1) 
        flashingDisplay(food.getCoord(),shapeString,*flashingTimer);
}
void Environment::print() 
{
    //print every objects and borders
    printBorder('.'); //border
    printFood(food.getShape()); //food   
}
   