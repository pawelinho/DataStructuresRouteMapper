#ifndef NODE_H
#define NODE_H

#include "address.h"

class Node {
public:
    float g;
    Address* address;
    Node* nextNode;
    Node* parentNode;

    Node(Address* addr) : g(0), address(addr), nextNode(nullptr), parentNode(nullptr) {}

    void print() const {
        std::cout << address->name << " (" << address->xCoordinate << ", " << address->yCoordinate << ") -> cost: " << g << "\n";
    }

    bool operator!=(const Node& otherNode) const {
        return address->name != otherNode.address->name;
    }

    bool operator==(const Node& otherNode) const {
        return address->name == otherNode.address->name;
    }
};

#endif
