#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <csignal>
#include <ncurses.h>
#include "../headers/ncurses.hpp"
#include "../headers/network.hpp"
#include "../headers/datahandle.hpp"

/**
 * @brief Required 'hook' to be able to bind a function to a csignal
 * @param sig 
 */
void RESIZER(int sig);

/**
 * @brief Class representing the command line interface
 * @param
 */
class CLI
{
private:
    /// @brief vector containing all the devices to display
    std::vector<NET_DEVICE> devices;
    /// @brief Pointer to the window containing the device list
    NC_WINDOW* device_ui = nullptr;
    /// @brief Pointer to the window containing the selected devices interfaces/modes
    NC_WINDOW* device_mode_ui = nullptr;
    /// @brief Pointer to the window containing the selected interfaces/modes commands
    NC_WINDOW* device_atributes_ui = nullptr;
    /// @brief Maximum values inherited from ncurses translated to local
    unsigned short int MAX_X, MAX_Y;
    /// @brief Current active collmn
    unsigned short int ACTIVE_COLL = 0;
    /// @brief Currently active element in each window
    unsigned short int Active[3] = {0,0,0}; 
    /// @brief Mode of display (text/command)
    bool DISPLAY_MODE = 0;
    /// @brief Adds a new device to the list of devices
    /// @param type What type of device to add
    /// @return true operation successful
    /// @return false operation unsuccessful
    bool AddDevice(NET_DEVICE_TYPE type);
    /// @brief Draws the text and info about the devices into the windows
    void DrawTextDevices();
    /// @brief Handles changing elements in focus
    /// @param change_coll Flag if collumn is changed
    /// @param increase Flag if increasing values
    void ChangeActive(bool change_coll, bool increase);
    /// @brief Loads data to devices
    void LoadData();
public:
    /// @brief Handles when the window is resized by remaking everything
    void Resize();
    /// @brief Initiates the command line interface and displays it
    void START_RUNTIME();
    /// @brief Constructor
    CLI();
    /// @brief Destructor
    ~CLI();
};
/// @brief Needed for handling resize csignal holds pointer to the currently active command line interface 
extern CLI* ACTIVE_CLI; 





#endif