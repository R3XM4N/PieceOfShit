#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <sstream>
#include <string>
#include <vector>

enum class NET_DEVICE_TYPE{
    NONE,
    ROUTER,
    SWITCH_L2
};

enum class INTERFACE_TYPE{
    NONE,
    ENABLE,
    GLOBAL_CONF,
    VLAN_CONF,  
    OSPF_CONF,
    INT_GIGABYTE,
    INT_FAST
};

std::string interfaceTypeToString(INTERFACE_TYPE int_type);

enum class COMMAND_TYPE{
    NONE,
    IPv4,
    IPv6,
    VLAN_ACCESS,
    VLAN_TRUNK
};

class NETCOMMAND
{
protected:
    COMMAND_TYPE command = COMMAND_TYPE::NONE;
public:
    unsigned short int output_count_text, output_count_commands; 
    virtual std::vector<std::string> ToString()= 0;
    virtual std::vector<std::string> GetCommands()= 0;
};

class IP_C : public NETCOMMAND 
{
private:
    std::string address = "0.0.0.0";
    unsigned int mask_suffix = __UINT32_MAX__;
public:
    IP_C(COMMAND_TYPE cmd, std::string address, unsigned int suffix);
    ~IP_C() = default;
    std::vector<std::string> ToString() override;
    std::vector<std::string> GetCommands() override;
};

class INTERFACE
{
private:
    static unsigned int next_id;
    unsigned int INDENTIFIER;
    INTERFACE_TYPE TYPE = INTERFACE_TYPE::NONE;
    std::string identifier = "INVALID INTERFACE";
    std::vector<NETCOMMAND*> config;
public:
    INTERFACE(INTERFACE_TYPE int_type, std::string interface_identifier);
    ~INTERFACE();
    void AddCommand(NETCOMMAND* declared_command);
    std::vector<NETCOMMAND*>& GetCommands();
    std::string GetIdentifier();
    std::string ToString();
};

class NET_DEVICE
{
private:
    static unsigned int next_id;
    unsigned int INDENTIFIER;
    const static unsigned short int MAX_HOSTNAME_LENGTH = 16;
    std::string HOSTNAME = "INVALID DEVICE";
    std::vector<INTERFACE> interfaces;
    NET_DEVICE_TYPE device_type = NET_DEVICE_TYPE::NONE;
public:
    std::vector<INTERFACE>& GetInterfaces();
    std::string Hostname();
    std::string ToString();
    bool SetHostname(std::string new_hostname);
    bool AddInterface(INTERFACE_TYPE interface_type, std::string identifier);
    bool AddInterfaceRange(INTERFACE_TYPE interface_type, std::string identifier_prefix, unsigned short int count);
    NET_DEVICE(NET_DEVICE_TYPE deviceType);
    ~NET_DEVICE();

    bool AddIP(COMMAND_TYPE ip_type, std::string interface_identifier, std::string address, unsigned int suffix);
};

#endif