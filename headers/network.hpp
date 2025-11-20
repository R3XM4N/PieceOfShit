#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "../headers/llist.hpp"

///@brief enumm Representing the type of network device
enum class NET_DEVICE_TYPE{
    NONE,
    ROUTER,
    SWITCH_L2
};
/// @brief enum Representing the type of interface/mode of operation on a device
enum class INTERFACE_TYPE{
    NONE,
    ENABLE,
    GLOBAL_CONF,
    VLAN_CONF,
    OSPF_CONF,
    DHCP_CONF,
    INT_GIGABYTE,
    INT_FAST
};
/**
 * @brief Function for translating enum values for interfaces/modes into human readable text
 * 
 * @param int_type The type of inteface/mode of operation
 * @return std::string 
 */
std::string interfaceTypeToString(INTERFACE_TYPE int_type);
/// @brief Type of command used to distinguish commands
enum class COMMAND_TYPE{
    NONE,
    IPv4,
    IPv6,
    VLAN_ACCESS,
    VLAN_TRUNK,
    DHCP,
    OSPF
};

/**
 * @brief Class representing a generic command structure to use as a parent do not use directly
 */
class NETCOMMAND
{
protected:
    COMMAND_TYPE command = COMMAND_TYPE::NONE;
public:
    // unsigned short int output_count_text, output_count_commands; 
    /**
     * @brief Method that returns the text format of the command
     * @return std::vector<std::string> 
     */
    virtual std::vector<std::string> ToString()= 0;
    /**
     * @brief Method that returns commands required to be run on the interface for the command to be properly executed
     * @return std::vector<std::string> 
     */
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

class DHCP_C : public NETCOMMAND
{
private:
    std::string pool_name;
    std::string network_addr_and_mask; //mask and suffix
    std::string default_gateway;
    std::string dns_address; //mask and suffix
    std::string domain_name; //mask and suffix

public:
    std::vector<std::string> ToString() override;
    std::vector<std::string> GetCommands() override;
    DHCP_C(COMMAND_TYPE cmd, std::string pool_name, std::string network, std::string defaultg, std::string domain_n);
    ~DHCP_C();
};


/// @brief Class representing a interface/mode of operation on a device
class INTERFACE
{
private:
    /// @brief Unique id assigner to ensure no duplicate object
    static unsigned int next_id;
    /// @brief Unique id to ensure no duplicate object
    unsigned int INDENTIFIER;
    /// @brief The type of interface this object represents
    INTERFACE_TYPE TYPE = INTERFACE_TYPE::NONE;
    /// @brief The identifier of this interface/mode (for interfaces "0/0" or "0/0/3", for vlan "40" etc...) 
    std::string identifier = "INVALID INTERFACE";
    /// @brief Commands assigned to this interface/mode of operation
    std::vector<std::shared_ptr<NETCOMMAND>> config;
public:
    /// @brief Constructor for the interface/mode
    /// @param int_type Type of interface/mode of operation
    /// @param interface_identifier Unique indetifier of the interface
    INTERFACE(INTERFACE_TYPE int_type, std::string interface_identifier);
    /// @brief Destructor
    ~INTERFACE();
    /// @brief Adds a command to the list of commands associated with this interface/mode of operation
    /// @param declared_command Pointer to the command that is supposed to be added
    void AddCommand(std::shared_ptr<NETCOMMAND> declared_command);
    /// @brief Gets a reference to the private pointer of commands
    /// @return reference to a vector of commands associated with this interface
    std::vector<std::shared_ptr<NETCOMMAND>>& GetCommands();
    /// @brief Getter for identifier
    /// @return string Indetifier
    std::string GetIdentifier();
    /// @brief Returns human readable form of the name of the interface/mode of operation
    /// @return string of human readable format of self
    std::string ToString();
};
/// @brief Class representing a generic network device
class NET_DEVICE
{
private:
    /// @brief Unique id assigner
    static unsigned int next_id;
    /// @brief Unique id to avoid duplicity
    unsigned int INDENTIFIER;
    /// @brief Maximum allowed hostname size
    const static unsigned short int MAX_HOSTNAME_LENGTH = 16;
    /// @brief Hostname of this device
    std::string HOSTNAME = "INVALID DEVICE";
    /// @brief Interfaces and modes of operation on this device
    std::vector<INTERFACE> interfaces;
    /// @brief The type of device
    NET_DEVICE_TYPE device_type = NET_DEVICE_TYPE::NONE;
public:
    /// @brief Gives reference to the private vector of interfaces
    /// @return Reference to a vector of interfaces
    std::vector<INTERFACE>& GetInterfaces();
    /// @brief Hostname getter
    /// @return string Hostname
    std::string Hostname();
    /// @brief Human readable format of device
    /// @return string 
    std::string ToString();
    /// @brief Adds DHCP to a device with chosen parameters
    /// @param pool_name DHCP pool name
    /// @param network Network address
    /// @param defaultg Default gateway
    /// @param domain_n Domain name
    /// @return successful?s
    bool AddDHCP(std::string pool_name, std::string network, std::string defaultg, std::string domain_n);
    /// @brief Sets the devices hostname, raises false if invalid
    /// @param new_hostname New hostname
    /// @return successful?
    bool SetHostname(std::string new_hostname);
    /// @brief Adds a new interface/mode of operation to the device, raises false if duplicate
    /// @param interface_type Type of interface/mode to be added
    /// @param identifier Interfaces/Mode identifier
    /// @return successful?
    bool AddInterface(INTERFACE_TYPE interface_type, std::string identifier);
    /// @brief Adds a range of interfaces fa "0/" 10 would give 10 interfaces going from "fa 0/0" to "fa 0/9". Workds only on one layer up (0/X yes not 0/X/Y), raises false when it fails
    /// @param interface_type Type of interfaces to add
    /// @param identifier_prefix The first part of identifier
    /// @param count Ammount of interfaces to add
    /// @return successful?
    bool AddInterfaceRange(INTERFACE_TYPE interface_type, std::string identifier_prefix, unsigned short int count);
    /// @brief Device constructor
    /// @param deviceType Type of device to be initialized
    NET_DEVICE(NET_DEVICE_TYPE deviceType);
    /// @brief Destructor
    ~NET_DEVICE();
    /// @brief Adds ipv4/ipv6 on the selected interface, raises false if it fails
    /// @param ip_type Command type of either IPV4 to add IPv4 or IPV6 to add IPv6
    /// @param interface_identifier Identifier of the interface
    /// @param address IP address to assign
    /// @param suffix Suffix form of the adress mask
    /// @return successful?
    bool AddIP(COMMAND_TYPE ip_type, std::string interface_identifier, std::string address, unsigned int suffix);
};

#endif