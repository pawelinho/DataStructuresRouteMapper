#ifndef ADDRESS_MANAGER_H
#define ADDRESS_MANAGER_H

#include "address.h"
#include <vector>

class AddressManager {
public:
    std::vector<Address> addressList;
    // Add address to list
    void addAddress(const std::string& addressName, int x, int y) {
        addressList.push_back(Address(addressName, x, y));
    }
    //returns list of addresses
    const std::vector<Address>& getAddresses() const {
        return addressList;
    }
    // Log addresses list
    void printAddresses() const {
        for (const auto& address : addressList) {
            address.print();
        }
    }
};

#endif
