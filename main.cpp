#include <iostream>
#include "graph.h"
#include "address_manager.h"

int main() {
    AddressManager addressManager;
    addressManager.addAddress("Delivery Depot", 10, 20);
    addressManager.addAddress("Address 1", 10, 40);
    addressManager.addAddress("Address 2", 20, 60);
    addressManager.addAddress("Address 3", 30, 80);
    addressManager.addAddress("Address 4", 40, 100);

    std::cout << "Generated Addresses:\n";
    addressManager.printAddresses();

    Graph graph;
    for (const auto& address : addressManager.getAddresses()) {
        graph.addNode(address);
    }
    graph.addEdge(addressManager.getAddresses()[0], addressManager.getAddresses()[1], 5.0);
    graph.addEdge(addressManager.getAddresses()[0], addressManager.getAddresses()[2], 10.0);
    graph.addEdge(addressManager.getAddresses()[1], addressManager.getAddresses()[3], 9.0);
    graph.addEdge(addressManager.getAddresses()[2], addressManager.getAddresses()[3], 25.0);
    graph.addEdge(addressManager.getAddresses()[3], addressManager.getAddresses()[4], 3.0);

    Address startAddress = addressManager.getAddresses()[0];
    Address* optimalEndAddress = nullptr;

    std::cout << "Planning route from " << startAddress.name << " to the best end node:\n";
    Stack<Node>* pathStack = graph.dijkstra(&startAddress, optimalEndAddress);

    if (optimalEndAddress) {
        std::cout << "Optimal end node: " << optimalEndAddress->name << "\n";
    } else {
        std::cout << "No optimal end node found.\n";
    }

    std::cout << "Planned route:\n";
    while (!pathStack->isEmpty()) {
        Node* node = pathStack->pop();
        node->print();
        delete node; // Free memory allocated for nodes
    }

    delete pathStack; // Free memory allocated for path stack

    return 0;
}
