#ifndef COORD_HPP
#define COORD_HPP
    struct Coord
    {
        int x;
        int y;

        //constructor
        Coord(); //default
        Coord(int y, int x);

        //operator overload
        bool operator==(Coord& rightSide);
    };
#endif