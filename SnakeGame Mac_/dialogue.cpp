#include "dialogue.hpp"

//constructor(s)
Dialogue::Dialogue() //default
{
    //init
    coord.x = -1;
    coord.y = -1;
    numberOfOption = 0;
    option = 0;
    flag = false; //default state
}

//modifier(s)
void Dialogue::importFromFile(std::string filePath) 
{
    //create a file stream
    std::fstream in; //create a file stream
    in.open(filePath, std::ios::in);

    int i = 0; //index counter
    while (!in.eof()) 
    {
        std::getline(in,dialogueOption[i]); //each line in the file is a dialogue
        numberOfOption++; //append available option
        i++;
    }
    in.close(); //close fstream
}
void Dialogue::setCoord(int y, int x) 
{
    //set coord
    coord.y = y;
    coord.x = y;
}
void Dialogue::setOption(int option) 
{
    this->option = option;
}
void Dialogue::setFlag() 
{
    flag = true;
}
void Dialogue::resetFlag() 
{
    flag = false;
}
//accessor(s)
int Dialogue::getNumberOfOption() 
{
    return numberOfOption;
}
bool Dialogue::getFlag() 
{
    return flag;
}

//print
void Dialogue::printDialogue() 
{
    //print out dialogue at option
    //convert string to char* 
    int length = dialogueOption[option].length();
    char* tmp = new char[length];
    for (int i = 0; i < length; i++) 
    {
        tmp[i] = dialogueOption[option][i];
    }
    //print
    mvprintw(coord.y, coord.x, "%s", tmp);
}

