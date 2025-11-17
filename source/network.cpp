#include "../headers/network.hpp"

/*
NONE,
ENABLE,
GLOBAL_CONF,
VLAN_CONF,
OSPF_CONF,
INT_GIGABYTE,
INT_FAST
*/

std::string interfaceTypeToString(INTERFACE_TYPE int_type){
    switch (int_type)
    {
    case INTERFACE_TYPE::ENABLE:
        return "#";
        break;
    case INTERFACE_TYPE::GLOBAL_CONF:
        return "(global): ";
        break;
    case INTERFACE_TYPE::VLAN_CONF:
        return "(vlan): ";
        break;
    case INTERFACE_TYPE::OSPF_CONF:
        return "(ospf): ";
        break;
    case INTERFACE_TYPE::INT_GIGABYTE:
        return "(gi): ";
        break;
    case INTERFACE_TYPE::INT_FAST:
        return "(fa): ";
        break;
    default:
        return "ERROR";
        break;
    }
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
unsigned int INTERFACE::next_id = 0;
INTERFACE::INTERFACE(INTERFACE_TYPE int_type, std::string interface_identifier) : INDENTIFIER(next_id++) {
    this->identifier = interface_identifier;
    this->TYPE = int_type;
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
std::string INTERFACE::ToString(){
    return interfaceTypeToString(this->TYPE) + this->GetIdentifier();
}
#pragma endregion

#pragma region NET_DEVICE
unsigned int NET_DEVICE::next_id = 0;
std::vector<INTERFACE>& NET_DEVICE::GetInterfaces(){
    return this->interfaces;
}

bool NET_DEVICE::AddIP(COMMAND_TYPE ip_type, std::string interface_identifier, std::string address, unsigned int suffix){
    for (INTERFACE &interface : this->interfaces){
        if (interface.GetIdentifier() == interface_identifier){
            interface.AddCommand(new IP_C(ip_type, address, suffix));
            return 1;
        }
    }
    return 0;
}
NET_DEVICE::NET_DEVICE(NET_DEVICE_TYPE deviceType) : INDENTIFIER(next_id++) 
{
    this->device_type = device_type;
}

NET_DEVICE::~NET_DEVICE()
{
    
}
std::string NET_DEVICE::ToString(){
    return "NET_DEVICE::ToString NOT IMPLEMENTED";
}
std::string NET_DEVICE::Hostname(){
    return this->HOSTNAME;
}
bool NET_DEVICE::SetHostname(std::string new_hostname){
    this->HOSTNAME = new_hostname;
    return 1;
}

bool NET_DEVICE::AddInterface(INTERFACE_TYPE interface_type, std::string identifier){
    this->interfaces.push_back(INTERFACE(interface_type, identifier));
    return 1;
}

bool NET_DEVICE::AddInterfaceRange(INTERFACE_TYPE interface_type, std::string identifier_prefix, unsigned short int count){
    std::stringstream buffer;
    for (unsigned short int i = 0; i < count; i++){
        buffer.str(std::string());
        buffer << identifier_prefix << i;
        this->interfaces.push_back(INTERFACE(interface_type, buffer.str()));
    }
    return 1;
    
}
#pragma endregion