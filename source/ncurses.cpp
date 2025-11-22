#include "../headers/ncurses.hpp"

ncurses_window ncw_new_window(const std::string& name, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height){
    ncurses_window win{ name, nullptr, x, y, width, height };
    win.self = newwin(height, width, y, x);
    return win;
}

void ncw_delete(ncurses_window& window) {
    if (window.self) delwin(window.self);
}

void ncw_print(ncurses_window& window, const std::string& text, unsigned short int offset_x, unsigned short int offset_y){
    mvwprintw(window.self, offset_y, offset_x, "%s", text.c_str());
}

void ncw_print(ncurses_window& window, std::ostringstream& text_steamed, unsigned short int offset_x, unsigned short int offset_y){
    mvwprintw(window.self, offset_y, offset_x, "%s", text_steamed.str().c_str());
}

void ncw_refresh(ncurses_window& window) { wrefresh(window.self); }

void ncw_box(ncurses_window& window, unsigned int chtype, unsigned int chtype_){
    box(window.self, chtype, chtype_);
}

void ncw_rebuild(ncurses_window& window, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height){
    if (window.self){
        ncw_delete(window);
        window.self = newwin(height, width, y, x);
        window.x = x;
        window.y = y;
        window.height = height;
        window.width = width;
    }
}

void NC_WINDOW::Draw(){
    ncw_refresh(*this->self);
}
void NC_WINDOW::Print(const std::string& text, unsigned short int offset_x, unsigned short int offset_y){
    ncw_print(*this->self, text, offset_x, offset_y);
}
void NC_WINDOW::Print(std::ostringstream& text_streamed, unsigned short int offset_x, unsigned short int offset_y){
    std::string text = text_streamed.str();
    this->Print(text, offset_x, offset_y);    
}
void NC_WINDOW::CPrint(const std::string& text, unsigned short int offset_x, unsigned short int offset_y, unsigned short int color_pair){
    wattron(this->self->self, COLOR_PAIR(color_pair));
    ncw_print(*this->self, text, offset_x, offset_y);
    wattroff(this->self->self, COLOR_PAIR(color_pair));
}
void NC_WINDOW::CPrint(std::ostringstream& text_streamed, unsigned short int offset_x, unsigned short int offset_y, unsigned short int color_pair){
    std::string text = text_streamed.str();
    this->CPrint(text, offset_x, offset_y, color_pair);    
}

void NC_WINDOW::Refresh(){
    ncw_refresh(*this->self);
}

void NC_WINDOW::Box(unsigned int chtype, unsigned int chtype_){
    ncw_box(*this->self, chtype, chtype_);
}

void NC_WINDOW::ReBuild(unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height){
    ncw_rebuild(*this->self, x, y, width, height);
}

NC_WINDOW::NC_WINDOW(const std::string& name, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height){
    this->self = new ncurses_window;
    *this->self = ncw_new_window(name, x, y, width, height);
}

NC_WINDOW::~NC_WINDOW(){
    ncw_delete(*this->self);
    delete this->self;
}
void NC_WINDOW::ConsoleLog(){
    std::cout << "NCURSE WINDOW: " << this->self->name << "\n"
    << "x: " <<  this->self->x << "\n"
    << "y: " <<  this->self->y << "\n"
    << "_width: " <<  this->self->width << "\n"
    << "_height: " <<  this->self->height << "\n";
}
unsigned short int NC_WINDOW::GetX(){return this->self->x;}
unsigned short int NC_WINDOW::GetY(){return this->self->y;}
unsigned short int NC_WINDOW::GetWidth(){return this->self->width;}
unsigned short int NC_WINDOW::GetHeigth(){return this->self->height;}

void sprintstd(int x, int y, const char* text){
    mvprintw(y, x, text);
}