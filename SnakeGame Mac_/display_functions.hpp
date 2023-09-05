//display tool(s)
#ifndef DISPLAY_FUNCTIONS_HPP
#define DISPLAY_FUNCTIONS_HPP
#include <ncurses.h>
#include <string>
#include "coord.hpp"
#include "timer.hpp"

void contentDisplay(Coord coord, std::string content);
void flashingDisplay(Coord coord, std::string content, Timer& timer);

#endif