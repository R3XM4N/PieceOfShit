#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>

struct ncurses_window {
    std::string name;
    WINDOW*   self;
    unsigned short int x, y, width, height;
};

ncurses_window ncw_new_window(const std::string& name, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);

void ncw_delete(ncurses_window& window);
void ncw_print(ncurses_window& window, const std::string& text, unsigned short int offset_x, unsigned short int offset_y);
void ncw_print(ncurses_window& window, std::ostringstream& text_steamed, unsigned short int offset_x, unsigned short int offset_y);
void ncw_refresh(ncurses_window& window);
void ncw_box(ncurses_window& window, unsigned int chtype = 0, unsigned int chtype_ = 0);
void ncw_rebuild(ncurses_window& window, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);

class NC_WINDOW
{
private:
    ncurses_window* self;
public:
    void Draw();
    void Print(const std::string& text, unsigned short int offset_x, unsigned short int offset_y);
    void Print(std::ostringstream& text_streamed, unsigned short int offset_x, unsigned short int offset_y); //for ss cuz string builder deez nutz
    void CPrint(const std::string& text, unsigned short int offset_x, unsigned short int offset_y, unsigned short int color_pair);
    void CPrint(std::ostringstream& text_streamed, unsigned short int offset_x, unsigned short int offset_y, unsigned short int color_pair);
    void Refresh();
    void Box(unsigned int chtype = 0, unsigned int chtype_ = 0);
    void ReBuild(unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);
    void ConsoleLog();
    unsigned short int GetX();
    unsigned short int GetY();
    unsigned short int GetWidth();
    unsigned short int GetHeigth();

    NC_WINDOW(const std::string& name, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);
    ~NC_WINDOW();
};

#endif