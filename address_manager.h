#include "address.h"
#include <vector>

class AddressManager {
private:
    std::vector<Address> addresses;

public:
    void addAddress(const std::string& name, int x, int y) {
        addresses.push_back(Address(name, x, y));
    }

    void printAddresses() const {
        for (const auto& addr : addresses) {
            addr.print();
        }
    }
};