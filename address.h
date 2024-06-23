#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include <iostream>

class Address {
public:
    std::string name;
    int xCoordinate; // This would be translated to long and lat coords on a real map
    int yCoordinate; // This would be translated to long and lat coords on a real map

    Address(const std::string& addressName, int x, int y)
        : name(addressName), xCoordinate(x), yCoordinate(y) {}

    void print() const {
        std::cout << name << " (" << xCoordinate << ", " << yCoordinate << ")\n";
    }

    bool operator==(const Address& other) const {
        return name == other.name;
    }
};

#endif
