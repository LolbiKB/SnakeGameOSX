#include "coord.hpp"

//constructor
Coord::Coord() //default
{
    y = -1;
    x = -1;
}
Coord::Coord(int y, int x) 
{
    this->y = y;
    this->x = x;
}

//operator overload
bool Coord::operator==(Coord& rightSide) 
{
    return (y == rightSide.y && x == rightSide.x);
}