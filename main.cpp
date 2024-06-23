#include <iostream>
#include "address_manager.h"

int main() {
    AddressManager manager;
    manager.addAddress("Depot", 10, 20);
    manager.addAddress("Address 1", 30, 40);

    std::cout << "Addresses in Manager:\n";
    manager.printAddresses();

    return 0;
}