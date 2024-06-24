#ifndef NODE_H
#define NODE_H

#include "address.h"

class Node {
public:
    float costFromStart;
    Address* address;
    Node* nextNode;
    Node* parentNode;

    Node(Address* addr) : costFromStart(0), address(addr), nextNode(nullptr), parentNode(nullptr) {}

    void print() const {
        std::cout << address->name << " (" << address->xCoordinate << ", " << address->yCoordinate << ") -> cost: " << costFromStart << "\n";
    }

    bool operator !=(const Node& rhd) {
        return (address->name != rhd.address->name);
    }
    bool operator <(const Node& rhd) {
        return (address->name < rhd.address->name);
    }
    bool operator ==(const Node& rhd) {
        return (address->name == rhd.address->name);
    }
    bool operator >(const Node& rhd) {
        return (address->name > rhd.address->name);
    }
};

#endif
