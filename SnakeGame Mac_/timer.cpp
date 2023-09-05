#include "timer.hpp"

//constructors
Timer::Timer() 
{
    defaultCount = this->count = 0;
    evalIfOutOfTime();
}
Timer::Timer(int count) 
{
    defaultCount = this->count = count;
    evalIfOutOfTime();
}

//modifier
void Timer::increment(int num = 1) 
{
    count+=num;
    evalIfOutOfTime();
}
void Timer::decrement(int num = 1) 
{
    count-=num;
    evalIfOutOfTime();
}
void Timer::reset() 
{
    count = defaultCount;
    evalIfOutOfTime();
}
void Timer::changeTimer(int num) 
{
    defaultCount = count = num;
    evalIfOutOfTime();
}

//accessor
int Timer::getCount() 
{
    return count;
}
bool Timer::isTimeOut() 
{
    return isOutOfTime;
}

//helper func
void Timer::evalIfOutOfTime() 
{
    if (count <= MIN_TIME) 
    {
        count = MIN_TIME;
        isOutOfTime = true;
    } else 
    {
        isOutOfTime = false;
    }
}