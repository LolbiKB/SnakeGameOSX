#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "ncurses.h"
#include "snake.hpp"
#include "environment.hpp"
#include "timer.hpp"
#include "dialogue.hpp"
#include "display_functions.hpp"
#include <cstdlib>
#include <time.h>
#include <string>

    class Player {
    private:    
        //object(s)
        Snake playerSnake; 
        Environment playerEnvironment;
        Coord foodCoord;

        //dialogue(s)
        Dialogue foodEatenDialogue;

        //timer(s)
        Timer foodTimer;
        Timer immunityTimer;
        Timer dialogueTimer;
        Timer flashingTimer;
        Timer srandTimer;

        //status
        int score;
        int level;
        int health;
        bool isImmune;
        bool isDead;

        //control
        char userInput;

        //settings
        int difficulty; 
        int borderLength;
        int borderWidth;

        //constants
        const int MAX_HEALTH = 100;
        const int MIN_HEALTH = 0;
    public:
        //constructors
        Player();

        //modifiers
        void increaseHealth(int);
        void decreaseHealth(int);

        //mechanics
        //gameplay
        void simulate(); //continue the game
        void genFood();  //generate food
        void ateFood(); //evaluate if ate food
        void evalSelfHit(); //evaluate if the Snake hit itself
        void selfDamage(); //call when self damage occured
        void foodMissDamage(); //call when food miss damage occured
        void foodEatenHeal(); //call when food is eaten to heal
        //diaglogue
        void genDialogue(); //call to generate dialogue

        //accessors
        bool deathStatus(); //return true if dead

        //control
        void detectUserInput();

        //display
        void display(); //print out Player's gameplay
        void displayStatus(); //print out Player's status
    };
#endif