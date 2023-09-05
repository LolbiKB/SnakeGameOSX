#ifndef FOOD_HPP
#define FOOD_HPP
#include "object.hpp"
#include "display_functions.hpp"

    class Food : public Object 
    {
        private:
            char shapeOptions[5] = {'*','+','@','$','?'};
            int currentOption;
            int status;
        public:
            //constructor
            Food();

            //accessor(S)
            int getCurrentOption();
            int getStatus();

            //modifier(s)
            void setOption(int option);
            void setStatus(int status);
    };
#endif
