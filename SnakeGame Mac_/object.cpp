#include "object.hpp"

//constructor(s)
Object::Object() 
{
    //init
    //coord
    coord.x = -1;
    coord.y = -1;
    //shape
    shape = 'x';
}
Object::Object(char style) 
{
    //init
    //coord
    coord.x = -1;
    coord.y = -1;
    //shape
    shape = style;
}

//modifier(s)
void Object::setCoord(int y, int x) 
{
    //set
    coord.x = x;
    coord.y = y;
}
void Object::setShape(char style) 
{
    //set
    shape = style;
}

//accessor(s)
char Object::getShape() 
{
    return shape;
}
Coord Object::getCoord() 
{
    return coord;
}