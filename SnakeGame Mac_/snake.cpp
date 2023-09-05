#include "snake.hpp"

//default constructor
Snake::Snake() 
{
    head = nullptr;
    length = 0;
    direction = 'l';
}

//accessor(s)
int Snake::getSnakeLength() 
{
    return length;
}

Coord Snake::getHeadCoord() 
{
    //return head's Coord
    Coord tmp;
    tmp.x = head->x;
    tmp.y = head->y;

    return tmp;
}
Coord* Snake::getSnakeCoord() 
{
    //return Coord of the whole Snake in term of array of Coord
    Coord* tmpCoordArray = new Coord[length];

    Node* tmp = head;
    //loop through every Node
    for(int i = 0; i < length; i++) 
    {
        tmpCoordArray[i].x = tmp->x;
        tmpCoordArray[i].y = tmp->y;

        //move tmp to the next Node
        tmp = tmp->next;
    }
    return tmpCoordArray;
}
char Snake::getDirection() 
{
    return direction;
}

//append a Node to Snake
void Snake::append(int x, int y)
{
    Node *newNode = new Node;
    newNode->x = x;
    newNode->y = y;
    newNode->next = nullptr;

    //check linkedList is not already empty
    if (head == nullptr) //if so
    {
        head = newNode; //set head = new Node
        return;
    }

    //otherwise find the last Node
    Node *tmp = head;

    while (tmp->next != nullptr) //if the current Node we're on (tmp) next is not a null
        tmp = tmp->next; //set current(tmp) to the next Node
    tmp->next = newNode;
    
    length++; //increase Snake's length
}

//determine Snake's motion
void Snake::move(int borderLength, int borderWidth)
{
    Node* tmp = head->next;
    Node pre;
    Node post;

    pre.x = post.x = head->x;
    pre.y = post.y = head->y;

    if (direction == 'l') //moving left
            head->x--;
        else if (direction == 'u') //moving up
            head->y--;
        else if (direction == 'r') //moving right
            head->x++;
        else if (direction == 'd') //moving down
            head->y++;
    
    while (tmp != nullptr) 
    {
        pre.x = tmp->x;
        pre.y = tmp->y;

        tmp->x = post.x;
        tmp->y = post.y;

        post.x = pre.x;
        post.y = pre.y;

        tmp = tmp->next;
    }

    //reset position if goes out of border
    if (head->x >= borderLength)
        head->x = 1;
    if (head->x <= 0)
        head->x = borderLength-1;
    if (head->y >= borderWidth)
        head->y = 1;
    if (head->y <= 0)
        head->y = borderWidth-1;
}

//grow Snake
void Snake::grow(int num) 
{
    for (int i = 0; i < num; i++)
    {
        //find the last Node
        Node *tmp = head;

        while (tmp->next != nullptr) //if the current Node we're on (tmp) next is not a null 
            tmp = tmp->next; //set current(tmp) to the next Node 
            
        //check direction
        if (direction == 'l') //moving left
            append(tmp->x+1,tmp->y); //new Node is lagging to the left(x+1)
        else if (direction == 'u') //moving up
            append(tmp->x,tmp->y-1); //new Node is lagging from above(y-1)
        else if (direction == 'r') //moving right
            append(tmp->x-1,tmp->y); //new Node is lagging from right(x-1)
        else if (direction == 'd') //moving down
            append(tmp->x,tmp->y+1); //new Node is lagging from below(y+1)
    }
}

//change direction of Snake
void Snake::changeDirection(char& newDirection) 
{
    //can't move directly to the opposite direction unless there is only one Node
    if ((newDirection == 'w' || newDirection == 'W') && (direction != 'd' || length == 0)) 
        direction = 'u'; 
    else if ((newDirection == 's' || newDirection == 'S') && (direction != 'u' || length == 0)) 
        direction = 'd';
    else if ((newDirection == 'd' || newDirection == 'D') && (direction != 'l' || length == 0)) 
        direction = 'r';
    else if ((newDirection == 'a' || newDirection == 'A') && (direction != 'r' || length == 0)) 
        direction = 'l';
}

//print Snake
void Snake::print() 
{
    Node *tmp = head;
    while (tmp != nullptr) 
    {
        mvprintw(tmp->y,tmp->x,"o");
        tmp = tmp->next;
    }
}