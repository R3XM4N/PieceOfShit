#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <csignal>
#include <ncurses.h>
#include "../headers/ncurses.hpp"
#include "../headers/network.hpp"

void RESIZER(int sig);

class CLI
{
private:
    std::vector<NET_DEVICE> devices;
    NC_WINDOW* device_ui = nullptr;
    NC_WINDOW* device_mode_ui = nullptr;
    NC_WINDOW* device_atributes_ui = nullptr;
    unsigned short int MAX_X, MAX_Y;
    unsigned short int ACTIVE_COLL = 0;
    unsigned short int Active[3] = {0,0,0}; 
    bool DISPLAY_MODE = 0;
    bool AddDevice(NET_DEVICE_TYPE type);
    void DrawTextDevices();
    void ChangeActive(bool change_coll, bool increase);
    void LoadData();
    /* data */
public:
    void Resize();
    void START_RUNTIME();
    CLI(/* args */);
    ~CLI();
};

extern CLI* ACTIVE_CLI; 





#endif