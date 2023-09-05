#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include <ncurses.h>
#include "object.hpp"
#include "coord.hpp"
#include "food.hpp"
#include "timer.hpp"
#include "string"
#include "display_functions.hpp"

class Environment
{
    private:
        //setting(s)
        int borderLength; //length of border
        int borderWidth; //width of border
        int borderPerimeter; //border Perimenter
        char borderChar; //border shape in char

        Timer* flashingTimer;
    public:
        //data
        //objects
        Food food;

        //functions
        //constructors
        Environment();
        Environment(int length, int width);

        //modifiers
        void setBorder(int length, int width); //set border
        void setFoodCoord(int y, int x); //set food Coord
        void setFlashingTimer(Timer& timer); //set flashingTimer to point to a timer

        //print
        void printBorder(char style);
        void printFood(char shape);
        void print(); //print Environment
};
    
#endif