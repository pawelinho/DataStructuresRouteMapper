#include <string>
#include <iostream>

class Address {
public:
    std::string name;
    int x;
    int y;

    Address(const std::string& n, int x_coord, int y_coord)
        : name(n), x(x_coord), y(y_coord) {}

    void print() const {
        std::cout << name << " (" << x << ", " << y << ")\n";
    }
};