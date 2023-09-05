#ifndef OBJECT_HPP
#define OBJECT_HPP
#include "coord.hpp"
#include <iostream>
    class Object
    {
        private:
            Coord coord;
            char shape;
        public:
            //constructor(s)
            Object();
            Object(char style);

            //modifier(s)
            void setCoord(int y, int x);
            void setShape(char style);

            //accessor(s)
            char getShape();
            Coord getCoord();
    };
#endif