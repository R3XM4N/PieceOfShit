#include "../headers/ui.hpp"
CLI* ACTIVE_CLI = nullptr;

void CLI::Resize(){
    resizeterm(LINES, COLS);
    clear();
    refresh();

    this->MAX_X = static_cast<unsigned short int>(COLS);
    this->MAX_Y = static_cast<unsigned short int>(LINES);

    this->device_ui->ReBuild(0, 0, 16, MAX_Y);
    this->device_mode_ui->ReBuild(16 , 0, 20, MAX_Y);
    this->device_atributes_ui->ReBuild(36 , 0, 20, MAX_Y);
    
    this->device_ui->Box();
    this->device_mode_ui->Box();
    this->device_atributes_ui->Box();

    //TO DO: TEXT PRINTING TO
    
    this->device_ui->Refresh();
    this->device_mode_ui->Refresh();
    this->device_atributes_ui->Refresh();
}

CLI::CLI(/* args */)
{
    initscr();
    ACTIVE_CLI = this;
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    std::signal(SIGWINCH, RESIZER);
    this->MAX_X = static_cast<unsigned short int>(COLS);
    this->MAX_Y = static_cast<unsigned short int>(LINES);

    this->device_ui = new NC_WINDOW("LIST", 0, 0, 16, MAX_Y);
    this->device_mode_ui = new NC_WINDOW("MODE", 16 , 0, 20, MAX_Y);
    this->device_atributes_ui = new NC_WINDOW("CONFIG", 37 , 0, 20, MAX_Y);
}

CLI::~CLI()
{
    delete(this->device_ui);
    delete(this->device_mode_ui);
    delete(this->device_atributes_ui);
}

void CLI::START_RUNTIME(){
    
    Resize();
    char INPUT;
    while (INPUT = getch(), INPUT != 'q')
    {
        switch (INPUT)
        {
        case KEY_UP:
        if (cursor.y == 0) break;
            cursor.y--;
            HandleCursor();
            break;
        case KEY_DOWN:
            if (cursor.y == CURSOR_Y_MAX) break;
            cursor.y++;
            HandleCursor();
            break;
        case KEY_LEFT:
            if (cursor.x == 0) break;
            cursor.x--;
            HandleCursor();
            break;
        case KEY_RIGHT:
            if (cursor.x == CURSOR_X_MAX) break;
            cursor.x++;
            HandleCursor();
            break;
        default:
            break;
        }
    }
    endwin();
    // this->device_atributes_ui->ConsoleLog();
    // this->device_mode_ui->ConsoleLog();
    // this->device_ui->ConsoleLog();

}

void HandleCursor(){

}

void RESIZER(int sig){
    ACTIVE_CLI->Resize();
}