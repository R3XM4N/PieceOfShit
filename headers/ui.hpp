#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <csignal>
#include <ncurses.h>
#include "../headers/ncurses.hpp"
#include "../headers/network.hpp"

void RESIZER(int sig);

struct ncursor{
    uint x;
    uint y;
};

class CLI
{
private:
    NC_WINDOW* device_ui = nullptr;
    NC_WINDOW* device_mode_ui = nullptr;
    NC_WINDOW* device_atributes_ui = nullptr;
    unsigned short int MAX_X, MAX_Y;
    ncursor cursor = {0,0}; //location
    unsigned int CURSOR_X_MAX = 1;
    unsigned int CURSOR_Y_MAX = 1;

    void HandleCursor();
    /* data */
public:
    void Resize();
    void START_RUNTIME();
    CLI(/* args */);
    ~CLI();
};

extern CLI* ACTIVE_CLI; 





#endif