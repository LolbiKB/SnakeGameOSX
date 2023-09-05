#include "player.hpp"

//constructors
Player::Player() 
{
    //settings
    difficulty = 0;
    borderLength = 60;
    borderWidth = 30;

    //timer(s)
    foodTimer.changeTimer(60);
    immunityTimer.changeTimer(15);
    dialogueTimer.changeTimer(4);
    flashingTimer.changeTimer(100);
    srandTimer.changeTimer(30);

    //snake
    playerSnake.append((borderLength/2),(borderWidth/2)); //Append one Node at the start of the game

    //food location

    //environment
    playerEnvironment.setBorder(borderLength,borderWidth); //set border to default border 60*30
    playerEnvironment.setFlashingTimer(flashingTimer); //set flashing to Environment

    //dialogue(s)
    foodEatenDialogue.importFromFile("data/dialogue/foodEatenDialogue.txt");

    //status
    level = 0;
    score = 0;
    isImmune = false;
    health = MAX_HEALTH;
    isDead = false;
}

//mechanics
//gameplay
//simulate gameplay by one frame
void Player::simulate() 
{
    //seed RNG
    srand(time(0));

    //continue Snake's movement
    playerSnake.move(borderLength,borderWidth);

    //dealing with food
    ateFood();

    //check recieve damage
    evalSelfHit();

    //timer(s)
    //check foodTimer
    if (foodTimer.isTimeOut()) //relocate food after a certain ammount of time 
    {
        genFood();
        foodMissDamage();
        foodTimer.reset(); //reset timer
    }
    if (foodTimer.getCount() <= 14)
        playerEnvironment.food.setStatus(1);
    else
        playerEnvironment.food.setStatus(0);

    //check immunityTimer
    if (immunityTimer.isTimeOut()) 
    {
        isImmune = false;
    }
    
    //check dialogueTimer
    if (!dialogueTimer.isTimeOut() && foodEatenDialogue.getFlag()) 
    {
        foodEatenDialogue.printDialogue();
    }
    //check flashingTimer
    if(flashingTimer.isTimeOut()) 
    {
        flashingTimer.reset();
    }
    //check srandTimer()
    if(srandTimer.isTimeOut()) 
    {
        srand(time(0));
        srandTimer.reset();
    }

    //check if dead
    if (health == MIN_HEALTH)
        isDead = true;
    
    //timer(s) tick
    foodTimer.decrement(1);
    immunityTimer.decrement(1);
    dialogueTimer.decrement(1);
    flashingTimer.decrement(1);
    srandTimer.decrement(1);
}
//genFood
void Player::genFood() 
{
    //generate random number
    //Generate food coordinate
    foodCoord.y = ((rand() % (borderWidth-1)) + 1);
    foodCoord.x = ((rand() % (borderLength-1)) + 1);
    //generate chance for food option
    double val = (double)((rand() % 10000) / 100.0 );

    //check if generated food coord is at snake's body or head
    Coord snakeHeadCoord = playerSnake.getHeadCoord();
    Coord* snakeBodyCoord = playerSnake.getSnakeCoord();
    while (foodCoord == snakeHeadCoord) 
    {
        foodCoord.y = ((rand() % (borderWidth-1)) + 1);
        foodCoord.x = ((rand() % (borderLength-1)) + 1);
    }
    for (int i = 0; i < playerSnake.getSnakeLength(); i++) //loop through all the snake nodes
    {
        if (foodCoord == snakeBodyCoord[i])
        {
            foodCoord.y = ((rand() % (borderWidth-1)) + 1);
            foodCoord.x = ((rand() % (borderLength-1)) + 1);
        }
    }

    //chance of spawning different food
    if (val > 92.0) //08% chance spawning healing food
    {
        playerEnvironment.food.setOption(1);
    } else if (val > 87.0) //13% chance spawning point food
    {
        playerEnvironment.food.setOption(3);
    } else 
    {
        playerEnvironment.food.setOption(0);
    }

    playerEnvironment.setFoodCoord(foodCoord.y,foodCoord.x);
}
//ateFood
void Player::ateFood() 
{
    if (foodCoord.x == playerSnake.getHeadCoord().x && foodCoord.y == playerSnake.getHeadCoord().y) 
    {
        playerSnake.grow(1); //grow snake

        //status effects of eating
        int foodOption = playerEnvironment.food.getCurrentOption(); //get current food option from food Object
        int snakeLength = playerSnake.getSnakeLength(); //get current snake length from playerSnake

        //score
        if (foodOption == 0) 
        {
            score+=(snakeLength*3);
            foodEatenHeal();
        } else if (foodOption == 1) 
        {
            score+=(snakeLength*3);
            increaseHealth(40);
        } else if (foodOption == 3) 
        {
            score+=(snakeLength*5);
            foodEatenHeal();
        }

        //dialogue
        genDialogue();
        dialogueTimer.reset();
        foodEatenDialogue.setFlag();

        //update timer
        int addedTime = ((rand() %  15) + 28);
        foodTimer.increment(addedTime);
        genFood(); 
    }
}
//evalSelfHit
void Player::evalSelfHit()
{
    //get Snake's full Coord
    Coord* dangerCoord = playerSnake.getSnakeCoord();
    //tmp var
    Coord SnakeHead;
    SnakeHead.x = dangerCoord[0].x;
    SnakeHead.y = dangerCoord[0].y;
    int SnakeLength = playerSnake.getSnakeLength();

    //loop
    for (int i = 1; i < SnakeLength; i++) 
    {
        if (SnakeHead.x == dangerCoord[i].x && SnakeHead.y == dangerCoord[i].y && !isImmune) 
        {
            delete dangerCoord;
            //add damage
            selfDamage();
            //add immunity
            isImmune = true;
            immunityTimer.reset();
            return;
        }       
    }
    delete dangerCoord;
    return;
}
//selfDamage
void Player::selfDamage() 
{
    decreaseHealth(50);
}
//missFoodDamage
void Player::foodMissDamage() 
{
    decreaseHealth(20);
}
//foodEatenHeal
void Player::foodEatenHeal() 
{
    increaseHealth(5);
}

//dialogue
void Player::genDialogue() 
{
    //determine dialogue coord
    Coord headCoord = playerSnake.getHeadCoord(); //get head coord
    char snakeDirection = playerSnake.getDirection(); //get snake's direction
    //loop
    if (snakeDirection == 'l' || snakeDirection == 'r') //if snake is moving horizonally
    {
        int distance = (borderWidth - headCoord.y); //distance from max-y (width)
        if (distance >= (borderWidth / 2)) //head is closer to the top 
            foodEatenDialogue.setCoord(headCoord.y + 4, headCoord.x); //dialogue coord is at head + 4 in the y-axis
        else if (distance < (borderWidth / 2))
            foodEatenDialogue.setCoord(headCoord.y - 4, headCoord.x); //dialogue coord is at head + 4 in the y-axis
    }
    if (snakeDirection == 'u' || snakeDirection == 'd') //if snake is moving vertically
    {
        int distance = (borderLength - headCoord.x); //distance from max-y (width)
        if (distance >= (borderLength / 2)) //head is closer to the top 
            foodEatenDialogue.setCoord(headCoord.y, headCoord.x + 7); //dialogue coord is at head + 4 in the y-axis
        else if (distance < (borderWidth / 2))
            foodEatenDialogue.setCoord(headCoord.y, headCoord.x - 7); //dialogue coord is at head + 4 in the y-axis
    }

    foodEatenDialogue.setOption(rand() % foodEatenDialogue.getNumberOfOption());
}

//modifiers
//increaseDamage
void Player::increaseHealth(int num) 
{
    health+=num;
    if (health >= MAX_HEALTH)
        health = MAX_HEALTH;
}
//decreaseHealth
void Player::decreaseHealth(int num) 
{
    health-=num;
    if (health <= MIN_HEALTH)
        health = MIN_HEALTH;
}


//accessor
bool Player::deathStatus() 
{
    return isDead;
}

//display
void Player::display() 
{
    //print Environment
    playerEnvironment.print();

    //print Snake
    playerSnake.print();

    //print status 
    displayStatus();
}
void Player::displayStatus() 
{
    //variable(s)
    int yCoord = borderWidth+1;

    //print score
    Coord scoreStatusCoord;
    scoreStatusCoord.y = yCoord;
    scoreStatusCoord.x = 1;
    contentDisplay(scoreStatusCoord, "Score: " + std::to_string(score));

    //print health 
    //create content
    Coord healthStatusCoord;
    std::string healthStatusContent = "Health: " + std::to_string(health);
    healthStatusCoord.y = yCoord;
    healthStatusCoord.x = 20;
    //check if health is low(less than 20)
    if (health <= 20) 
        flashingDisplay(healthStatusCoord, healthStatusContent, flashingTimer);
    else
        contentDisplay(healthStatusCoord, healthStatusContent);

    //immunity
    if (isImmune) 
    {
        Coord immunityStatusCoord;
        immunityStatusCoord.y = borderWidth+1;
        immunityStatusCoord.x = 35;
        flashingDisplay(immunityStatusCoord, "immune", flashingTimer);
    }

}

//control
void Player::detectUserInput() 
{
    userInput = getch();
    playerSnake.changeDirection(userInput);
}