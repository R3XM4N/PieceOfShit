#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <ncurses.h>
#include <sstream>
#include <string>
#include <iostream>

void sprintstd(int x, int y, const char* text);
/**
 * @brief A struct representing an ncurse window
 * @param name Descriptive name of the element
 * @param self The ncurse window itself
 * @param x, y Position of the window relative to the entire display enviroment (The terminal size)
 * @param width, height The size proportions of the window
 */
struct ncurses_window {
    std::string name;
    WINDOW*   self;
    unsigned short int x, y, width, height;
};

/**
 * @brief Kind of a "Constructor" for ncurses_window type that sets up the struct for use recommended to use to set up ncurses_windows 
 * 
 * @param name The name the return window will have
 * @param x X position of the window relative to the entire display enviroment
 * @param y Y position of the window relative to the entire display enviroment
 * @param width Width of the return window
 * @param height Heigth of the return window
 * @return ncurses_window 
 */
ncurses_window ncw_new_window(const std::string& name, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);
/**
 * @brief Deletes the ncurses_window element
 * @param window Reference to the window to be deleted
 */
void ncw_delete(ncurses_window& window);
/**
 * @brief Prints text into the selected window
 * @param window The window to be printed into
 * @param text The text to be printed as a string
 * @param offset_x X position in the window
 * @param offset_y Y position in the window
 */
void ncw_print(ncurses_window& window, const std::string& text, unsigned short int offset_x, unsigned short int offset_y);
/**
 * @brief Prints text into the selected window while using sstream, uses string ncw_print as base
 * @param window The window to be printed into
 * @param text The text to be printed as a stream
 * @param offset_x X position in the window
 * @param offset_y Y position in the window
 */
void ncw_print(ncurses_window& window, std::ostringstream& text_steamed, unsigned short int offset_x, unsigned short int offset_y);
/**
 * @brief wrefreshes() the selected window
 * @param window The selected window to be refreshed
 */
void ncw_refresh(ncurses_window& window);
/**
 * @brief Draws the box around the ncurses_window element with the selected character
 * @param window The window to be boxed
 * @param chtype character type
 * @param chtype_ character type
 */
void ncw_box(ncurses_window& window, unsigned int chtype = 0, unsigned int chtype_ = 0);
/**
 * @brief Deletes selected windows ncurses window (.self) and remakes it with new parameters
 * @param window ncurses_window element to be edited
 * @param x New position x
 * @param y New position y
 * @param width New width
 * @param height New Height
 */
void ncw_rebuild(ncurses_window& window, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);

/**
 * @brief A class based representation of a ncurses window 
 */
class NC_WINDOW
{
private:
    ncurses_window* self;
public:
    /**
     * @brief Calls refresh on self
     */
    void Draw();
    /**
     * @brief Prints the text into the window
     * @param text Text to be printed 
     * @param offset_x X position in the window
     * @param offset_y Y position in the window
     */
    void Print(const std::string& text, unsigned short int offset_x, unsigned short int offset_y);
    /**
     * @brief Prints the text into the window
     * @param text Text to be printed as sstream
     * @param offset_x X position in the window
     * @param offset_y Y position in the window
     */
    void Print(std::ostringstream& text_streamed, unsigned short int offset_x, unsigned short int offset_y); //for ss cuz string builder deez nutz
    /**
     * @brief Prints the text into the window with specified color pair (Foreground and background colors)
     * @param text Text to be printed 
     * @param offset_x X position in the window
     * @param offset_y Y position in the window
     * @param color_pair The identifier of the color pair to be used (Has to be inicialized beforehand)
     */
    void CPrint(const std::string& text, unsigned short int offset_x, unsigned short int offset_y, unsigned short int color_pair);
    /**
     * @brief Prints the text into the window with specified color pair (Foreground and background colors)
     * @param text Text to be printed as sstream
     * @param offset_x X position in the window
     * @param offset_y Y position in the window
     * @param color_pair The identifier of the color pair to be used (Has to be inicialized beforehand)
     */
    void CPrint(std::ostringstream& text_streamed, unsigned short int offset_x, unsigned short int offset_y, unsigned short int color_pair);
    /**
     * @brief Calls refresh on self
     */
    void Refresh();
    /**
     * @brief Draws a box around the window with selected chtype
     * @param chtype chartype 
     * @param chtype_ chartype 
     */
    void Box(unsigned int chtype = 0, unsigned int chtype_ = 0);
    /**
     * @brief Deletes it's own ncurse window and remakes it with new parameters
     * @param x New x position relative to enviroment
     * @param y New y position relative to enviroment
     * @param width New width
     * @param height New height
     */
    void ReBuild(unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);
    /**
     * @brief Prints debug data (positions x,y relative to enviroment and height,width) about the window into std::cout
     * 
     */
    void ConsoleLog();
    /**
     * @brief Returns x position relative to enviroment
     * 
     * @return unsigned short int 
     */
    unsigned short int GetX();
    /**
     * @brief Returns y position relative to enviroment
     * 
     * @return unsigned short int 
     */
    unsigned short int GetY();
    /**
     * @brief Returns width of the window
     * 
     * @return unsigned short int 
     */
    unsigned short int GetWidth();
    /**
     * @brief Returns heigth of the window
     * 
     * @return unsigned short int 
     */
    unsigned short int GetHeigth();
    /**
     * @brief Constructs a new nc window object
     * 
     * @param name Element name (Window name)
     * @param x Windows x position relative to enviroment
     * @param y Windows y position relative to enviroment
     * @param width Windows width
     * @param height Windows height
     */
    NC_WINDOW(const std::string& name, unsigned short int x, unsigned short int y, unsigned short int width, unsigned short int height);
    /**
     * @brief Destroys the nc window object
     */
    ~NC_WINDOW();
};

#endif