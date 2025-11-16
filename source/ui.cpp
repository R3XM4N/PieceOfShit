#include "../headers/ui.hpp"
CLI* ACTIVE_CLI = nullptr;

void CLI::DrawTextDevices(){
    unsigned short int start = 1; // TO DO: based on ncursor
    for (unsigned short int i = start; i <= this->devices.size(); i++)
    {
        this->device_ui->Print(this->devices[i - 1].Hostname(), static_cast<unsigned short int>(2), i);
    }
    start = 1;
    if (this->devices.size() > 0)
    {
        while (start <= this->devices[this->Active[0]].GetInterfaces().size())
        {
            this->device_mode_ui->Print(this->devices[this->Active[0]].GetInterfaces()[start - 1].ToString(), static_cast<unsigned short int>(2), start);
            start++;
        }

        if (this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands().size())
        {
            start = 1;
            for (auto &i : this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands())
            {
                std::vector<std::string> texts = i->ToString();
                for (std::string &text : texts)
                {
                    this->device_atributes_ui->Print(text, static_cast<unsigned short int>(2), start);
                    start++;
                }
            }    
        }
    }
}

void CLI::Resize(){
    resizeterm(LINES, COLS);
    clear();
    refresh();

    this->MAX_X = static_cast<unsigned short int>(COLS);
    this->MAX_Y = static_cast<unsigned short int>(LINES);

    this->device_ui->ReBuild(0, 0, 20, MAX_Y);
    this->device_mode_ui->ReBuild(20 , 0, 36, MAX_Y);
    this->device_atributes_ui->ReBuild(56 , 0, 60, MAX_Y);
    
    this->device_ui->Box();
    this->device_mode_ui->Box();
    this->device_atributes_ui->Box();

    //TO DO: TEXT PRINTING TO
    this->DrawTextDevices();

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

    this->device_ui = new NC_WINDOW("LIST", 0, 0, 20, MAX_Y);
    this->device_mode_ui = new NC_WINDOW("MODE", 20 , 0, 36, MAX_Y);
    this->device_atributes_ui = new NC_WINDOW("CONFIG", 56 , 0, 60, MAX_Y);

    this->AddDevice(NET_DEVICE_TYPE::ROUTER);
    this->AddDevice(NET_DEVICE_TYPE::ROUTER);
    this->devices[0].SetHostname("Smerovac smeru");
    this->devices[1].SetHostname("Autismus");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/0");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/1");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/2");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/3");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/4");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_GIGABYTE, "0/0");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_GIGABYTE, "0/4");
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/0", "0::0", 64);
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/1", "0::0", 64);
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/0", "0::0", 64);
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/0", "0::0", 64);

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
bool CLI::AddDevice(NET_DEVICE_TYPE type){
    this->devices.push_back(NET_DEVICE(type));
    return 1;
}

void CLI::HandleCursor(){

}

void RESIZER(int sig){
    ACTIVE_CLI->Resize();
}