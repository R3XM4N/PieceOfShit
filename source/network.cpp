#include "../headers/network.hpp"

std::string INTERFACE::ToString(){

}
std::string NET_DEVICE::ToString(){

}


#pragma region IP COMMAND
IP_C::IP_C(COMMAND_TYPE cmd, std::string address, unsigned int suffix){
    this->command = cmd;
    this->address = address;
    this->mask_suffix = suffix;
}
std::vector<std::string> IP_C::GetCommands(){
    std::stringstream output;
    if (command == COMMAND_TYPE::IPv4)
        output << "ip " << this->address << " TODO: MASK TRANSLATION/" << this->mask_suffix; //TO DO: add (mask)
    if (command == COMMAND_TYPE::IPv6)
        output << "ipv6 " << this->address << " /" << this->mask_suffix;
    else return {"IP COMMAND WRONGLY INITIALIZED (COMMAND)"};
    return {output.str()};
}
std::vector<std::string> IP_C::ToString(){
    std::stringstream output;
    if (command == COMMAND_TYPE::IPv4)
        output << "IPv4: " << this->address << " /" << this->mask_suffix;
    if (command == COMMAND_TYPE::IPv6)
        output << "IPv6: " << this->address << " /" << this->mask_suffix;
    else return {"IP COMMAND WRONGLY INITIALIZED (TEXT)"};
    return {output.str()};
}
#pragma endregion


#pragma region INTERFACE
INTERFACE::INTERFACE(std::string interface_identifier, INTERFACE_TYPE int_type){
    this->identifier = interface_identifier;
}

INTERFACE::~INTERFACE(){
    for (auto &command : config){
        delete command;
    }
}
void INTERFACE::AddCommand(NETCOMMAND* declared_command){
    this->config.push_back(declared_command);
}
std::string INTERFACE::GetIdentifier(){
    return this->identifier;
}
std::vector<NETCOMMAND*>& INTERFACE::GetCommands(){
    return this->config;
}
#pragma endregion

#pragma region NET_DEVICE
NET_DEVICE::NET_DEVICE(NET_DEVICE_TYPE deviceType)
{

}

NET_DEVICE::~NET_DEVICE()
{

}
void NET_DEVICE::AddIP(COMMAND_TYPE ip_type, std::string interface_identifier, std::string address, unsigned int suffix){
    for (INTERFACE &interface : this->interfaces){
        if (interface.GetIdentifier() == interface_identifier)
            interface.AddCommand(new IP_C(ip_type, address, suffix));
    }
}


#pragma endregion