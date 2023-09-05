#include "player.hpp"

//helper functions
inline void clearScreen();
inline void updateScreen();
;
//main
int main() 
{
    //create Player(s)
    Player playerOne;

    //clear screen before game loop
    clearScreen();

    //game loop starts
    while (!playerOne.deathStatus()) 
    {
        //mechanics 
        playerOne.simulate();
        playerOne.display();
        playerOne.detectUserInput();

        updateScreen(); //update Screen
    }
    
    return 0; 
}

//implementation
inline void clearScreen() 
{
    initscr();
    clear();
    curs_set(0);
    noecho();
}

inline void updateScreen() 
{
    timeout(0);
    refresh();
    clear();
    usleep(10000 * 10);
}