#ifndef TIMER_HPP
#define TIMER_HPP
class Timer
{
    private:
        //data
        int defaultCount;
        int count;
        bool isOutOfTime;

        //constant(s)
        const int MIN_TIME = 0;

    public:
        //constructors
        Timer(); //default
        Timer(int count);

        //modifier
        void decrement(int);
        void increment(int);
        void reset(); //reset Timer to default count
        void changeTimer(int num); //change default count

        //accessor
        int getCount();
        bool isTimeOut();

        //helper func
        void evalIfOutOfTime();
};
    
#endif