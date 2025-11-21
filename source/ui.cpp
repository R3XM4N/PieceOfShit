#include "../headers/ui.hpp"
CLI* ACTIVE_CLI = nullptr;

void CLI::LoadData(){
    this->AddDevice(NET_DEVICE_TYPE::ROUTER);
    this->AddDevice(NET_DEVICE_TYPE::ROUTER);
    this->devices[0].SetHostname("Smerovac smeru");
    this->devices[1].SetHostname("Autismus");
    this->devices[0].AddDHCP("pool name xd", "0.0.0.0/32", "1.1.1.1", "jduspat.com");
    this->devices[1].AddDHCP("pool name xd", "0.0.0.0/32", "1.1.1.1", "jduspat.com");
    this->devices[1].AddInterface(INTERFACE_TYPE::INT_FAST, "0/0");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/0");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/1");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/2");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/3");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_FAST, "0/4");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_GIGABYTE, "0/0");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_GIGABYTE, "0/4");
    this->devices[0].AddInterface(INTERFACE_TYPE::INT_GIGABYTE, "0/4");
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/0", "0::0", 64);
    this->devices[1].AddIP(COMMAND_TYPE::IPv4, "0/0", "0.0.0.0", 32);
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/1", "0::0", 64);
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/0", "0::0", 64);
    this->devices[0].AddIP(COMMAND_TYPE::IPv6, "0/0", "0::0", 64);
}

void CLI::DrawTextDevices(){
    unsigned short int start = 1; // TO DO: based on ncursor
    for (unsigned short int i = start; i <= this->devices.size(); i++)
    {
        if (i - 1 == this->Active[0])
            this->device_ui->CPrint(this->devices[i - 1].Hostname(), static_cast<unsigned short int>(2), i, 1);
        else
            this->device_ui->Print(this->devices[i - 1].Hostname(), static_cast<unsigned short int>(2), i);
        
    }
    start = 1;
    if (this->devices.size() > 0){
        while (start <= this->devices[this->Active[0]].GetInterfaces().size()){
            if (start - 1 == this->Active[1] && this->ACTIVE_COLL > 0)
                this->device_mode_ui->CPrint(this->devices[this->Active[0]].GetInterfaces()[start - 1].ToString(), static_cast<unsigned short int>(2), start, 1);
            else
                this->device_mode_ui->Print(this->devices[this->Active[0]].GetInterfaces()[start - 1].ToString(), static_cast<unsigned short int>(2), start);
            start++;
        }

        if (this->devices[this->Active[0]].GetInterfaces().size() > 0){
            if (this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands().size()){
                start = 1;
                for (auto &i : this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands()){
                    std::vector<std::string> texts;
                    if (this->DISPLAY_MODE == 0)
                        texts = i->ToString();
                    else
                        texts = i->GetCommands();                    
                    for (std::string &text : texts){
                        if (start - 1 == this->Active[2] && this->ACTIVE_COLL > 1)
                            this->device_atributes_ui->CPrint(text, static_cast<unsigned short int>(2), start, 1);
                        else
                            this->device_atributes_ui->Print(text, static_cast<unsigned short int>(2), start);
                        start++;
                    }
                }    
            }
        }
    }
    std::stringstream tst;
    tst << "DEBUG: ACTIVE: " << this->ACTIVE_COLL << " A0: " << this->Active[0] <<" A1: " << this->Active[1] << " A2: " << this->Active[2]; 
    this->device_atributes_ui->Print(tst.str(), 2, this->MAX_Y - 2);
    tst.str("");
    tst << "Cols: " << COLS << "Lines: " << LINES;
    this->device_atributes_ui->Print(tst.str(), 2, this->MAX_Y - 3);
}

void CLI::Resize(){
    resizeterm(0, 0);
    // doupdate();s
    clear();
    refresh();

    this->MAX_X = static_cast<unsigned short int>(COLS);
    this->MAX_Y = static_cast<unsigned short int>(LINES);

    this->device_ui->ReBuild(0, 0, 20, MAX_Y);
    this->device_mode_ui->ReBuild(20 , 0, 36, MAX_Y);
    // this->device_atributes_ui->ReBuild(56 , 0, 60, MAX_Y);
    this->device_atributes_ui->ReBuild(56 , 0, (this->MAX_X - 56) - ((this->MAX_X) % 2), MAX_Y);
    
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
    start_color();
    ACTIVE_CLI = this;
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    // std::signal(SIGWINCH, RESIZER);
    this->MAX_X = static_cast<unsigned short int>(COLS);
    this->MAX_Y = static_cast<unsigned short int>(LINES);

    this->device_ui = new NC_WINDOW("LIST", 0, 0, 20, MAX_Y);
    this->device_mode_ui = new NC_WINDOW("MODE", 20 , 0, 36, MAX_Y);
    // this->device_atributes_ui = new NC_WINDOW("CONFIG", 56 , 0, 60, MAX_Y);
    this->device_atributes_ui = new NC_WINDOW("CONFIG", 56 , 0, (this->MAX_X - 56) - ((this->MAX_X) % 2), MAX_Y);

    this->LoadData();
}

CLI::~CLI()
{
    delete(this->device_ui);
    delete(this->device_mode_ui);
    delete(this->device_atributes_ui);
}

void CLI::START_RUNTIME(){
    
    Resize();
    int INPUT;
    while (INPUT = wgetch(stdscr), INPUT != 'q')
    {
        switch (INPUT)
        {
        case 'w':
            ChangeActive(0, 0);
            break;
        case 's':
            ChangeActive(0 ,1);
            break;
        case 'a':
            ChangeActive(1, 0);
            break;
        case 'd':
            ChangeActive(1, 1);
            break;
        case 'e':
            this->DISPLAY_MODE = !this->DISPLAY_MODE;
            this->Resize();
            break;
        case KEY_RESIZE:
            this->Resize();
            break;
        default:
            break;
        }
        INPUT = 0;
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

void CLI::ChangeActive(bool change_coll, bool increase){
    if (change_coll){
        if (increase)
        {
            switch (this->ACTIVE_COLL){
            case 0: //device list
                if (this->devices[this->Active[0]].GetInterfaces().size() > 0){
                    this->ACTIVE_COLL++;
                    this->Active[1] = 0;
                }
                
                break;
            case 1: //interface list
                if (this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands().size() > 0){
                    this->ACTIVE_COLL++;
                    this->Active[2] = 0;
                }
                break;
            case 2: //command list
                //NOTHING AT EDGE
                break;
            default: // INVALID
                break;
            }
        }
        else{
            switch (this->ACTIVE_COLL){
            case 0: //device list
                //NOTHING AT EDGE
                break;
            case 1: //interface list
                this->ACTIVE_COLL--;
                this->Active[1] = 0;
                break;
            case 2: //command list
                this->ACTIVE_COLL--;
                this->Active[2] = 0;
                break;
            default: // INVALID
                break;
            }
        }
    }
    else if (!change_coll){
        if (this->devices.size() > 0){
            if (this->ACTIVE_COLL == 0){ //DEVICE LIST
                if (increase && this->Active[0] + 1 <= this->devices.size() - 1){
                    this->Active[0]++;
                }
                else if (!increase && this->Active[0] != 0){
                    this->Active[0]--;
                }
            }
            else if (this->ACTIVE_COLL == 1 && this->devices[this->Active[0]].GetInterfaces().size() > 0){ //INTERFACE LIST
                if (increase && this->Active[1] + 1 <= this->devices[this->Active[0]].GetInterfaces().size() - 1){
                    this->Active[1]++;
                }
                else if (!increase && this->Active[1] != 0){
                    this->Active[1]--;
                }
            }
            else if (this->ACTIVE_COLL == 2 && this->devices[this->Active[0]].GetInterfaces().size() > 0){ //COMMAND LIST
                    if (this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands().size() > 0){
                        if (increase && this->Active[2] + 1 <= this->devices[this->Active[0]].GetInterfaces()[this->Active[1]].GetCommands().size() - 1){
                        this->Active[2]++;
                    }
                    else if (!increase && this->Active[2] != 0){
                        this->Active[2]--;
                    }
                }
            }
        }
    }
    Resize();
}

// void RESIZER(int sig){
//     // ACTIVE_CLI->Resize();
// }