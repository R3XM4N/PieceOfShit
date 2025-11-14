#include <ncurses.h>
#include <string>
#include <sstream>
#include <iostream>

#include "headers/ncurses.hpp"
#include "headers/ui.hpp"

CLI* interface;

int main()
{
    interface = new CLI();
    interface->START_RUNTIME();
    delete(interface);

    // initscr();
    // cbreak();
    // noecho();
    // keypad(stdscr, TRUE);
    // curs_set(0);
    // NC_WINDOW window = NC_WINDOW("test", 4, 0, static_cast<unsigned short int>(COLS - 10) , LINES); 

    // refresh();
    // window.Box();
    // window.Refresh();   
    // char INPUT;
    // while (INPUT = getch(), INPUT != 'q')
    // {
        
    // }
    // endwin();

    return EXIT_SUCCESS;
}
/*
#include <ncurses.h>
#include <csignal>
#include <string>
#include <sstream>
#include <iostream>

#include "ncurses.hpp"

static ncurses_window main_win;

void handle_resize(int sig) {
    endwin();
    refresh();
    clear();

    // main_win.self.
    if (main_win.self) delwin(main_win.self);
    main_win = ncw_new_window("full_screen", 0, 0,
                              static_cast<unsigned short int>(COLS),
                              static_cast<unsigned short int>(LINES));

    ncw_box(main_win);
    ncw_print(main_win, "Full-screen window - press any key to exit",
              2, 2);
    ncw_refresh(main_win);
}

int main()
{
    initscr();          // start ncurses
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    std::signal(SIGWINCH, handle_resize);

    main_win = ncw_new_window("full_screen", 0, 0,
                              static_cast<unsigned short int>(COLS),
                              static_cast<unsigned short int>(LINES));

    ncw_box(main_win);
    ncw_print(main_win, "Full-screen window - press any key to exit", 2, 2);
    refresh();
    ncw_refresh(main_win);
    getch();            // wait for a key

    ncw_delete(main_win);
    endwin();
    return EXIT_SUCCESS;
}
*/