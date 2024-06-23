#include <iostream>
#include "address.h"

int main()
{
    std::cout << "Route Mapping System for Delivery Drivers" << std::endl;
    Address addr("Delivery Depot", 10, 20);
    std::cout << "Created Address:\n";
    addr.print();
    return 0;
}