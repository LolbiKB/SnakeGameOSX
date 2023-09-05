#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "coord.hpp"

class Snake
{
    public:
        struct Node
        {
            int x; //x-position
            int y; //y-position
            Node* next;
        };
    private:
        Node* head; //Snake head
        int length; //length of the Snake (how many nodes it has)
        char direction;
    public:
        Snake(); //default constructor

        //accessor(s)
        int getSnakeLength();
        Coord getHeadCoord();
        Coord* getSnakeCoord();
        char getDirection();

        //Snake's physicality
        void append(int x, int y); //add a Node to Snake at postion (x,y)
        void grow(int num); //add int number of nodes with location lagging behind the head

        //print functions
        void print(); //print out Snake

        //Snake's movement
        void move(int borderLength, int borderWidth); //call to propagate Snake's motion by 1 unit
        void changeDirection(char& newDirection);

};
#endif