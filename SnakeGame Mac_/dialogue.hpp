#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP
#include <ncurses.h>
#include <fstream>
#include <string>
#include "coord.hpp"
    class Dialogue
    {
        private:
            //data
            Coord coord;
            int numberOfOption;
            int option;
            std::string dialogueOption[50];
            bool flag;
        public:
            //constants
            int MAX_LENGTH = 10;
            //constructor(s)
            Dialogue();
            //modifier(s)
            void importFromFile(std::string filePath);
            void setCoord(int y, int x);
            void setOption(int option);
            void setFlag();
            void resetFlag();
            //accessor(s)
            int getNumberOfOption();
            bool getFlag();
            //print
            void printDialogue();
    };
#endif