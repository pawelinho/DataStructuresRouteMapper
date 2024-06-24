#include <iostream>
#include "graph.h"
#include "address_manager.h"

int main() {
    AddressManager addressManager;
    addressManager.addAddress("Delivery Depot", 10, 20);
    addressManager.addAddress("Address 1", 1, 4);
    addressManager.addAddress("Address 2", 2, 6);
    addressManager.addAddress("Address 3", 5, 8);
    addressManager.addAddress("Address 4", 6, 10);
    addressManager.addAddress("Address 5", 8, 10);
    addressManager.addAddress("Address 6", 13, 11);
    addressManager.addAddress("Address 7", 20, 14);
    addressManager.addAddress("Address 8", 30, 30);
    addressManager.addAddress("Address 9", 33, 20);
    addressManager.addAddress("Address 10", 35, 25);

    std::cout << "Generated Addresses:\n";
    addressManager.printAddresses();

    Graph graph;
    for (auto &address : addressManager.getAddresses()) {
        graph.addNode(address);
    }

    graph.addEdge(addressManager.getAddresses()[0], addressManager.getAddresses()[1], 2);
    graph.addEdge(addressManager.getAddresses()[0], addressManager.getAddresses()[2], 2);
    graph.addEdge(addressManager.getAddresses()[1], addressManager.getAddresses()[2], 1);
    graph.addEdge(addressManager.getAddresses()[1], addressManager.getAddresses()[3], 5);

    graph.addEdge(addressManager.getAddresses()[2], addressManager.getAddresses()[3], 2);
    graph.addEdge(addressManager.getAddresses()[2], addressManager.getAddresses()[4], 7);
    graph.addEdge(addressManager.getAddresses()[2], addressManager.getAddresses()[5], 10);


    graph.addEdge(addressManager.getAddresses()[3], addressManager.getAddresses()[5], 2);
    graph.addEdge(addressManager.getAddresses()[3], addressManager.getAddresses()[6], 2);

    graph.addEdge(addressManager.getAddresses()[4], addressManager.getAddresses()[6], 3);
    graph.addEdge(addressManager.getAddresses()[4], addressManager.getAddresses()[7], 30);
    graph.addEdge(addressManager.getAddresses()[4], addressManager.getAddresses()[8], 12);
    graph.addEdge(addressManager.getAddresses()[5], addressManager.getAddresses()[6], 3);
    graph.addEdge(addressManager.getAddresses()[5], addressManager.getAddresses()[7], 10);
    
    graph.addEdge(addressManager.getAddresses()[6], addressManager.getAddresses()[7], 4);
    graph.addEdge(addressManager.getAddresses()[6], addressManager.getAddresses()[8], 7);
    graph.addEdge(addressManager.getAddresses()[7], addressManager.getAddresses()[8], 4);
    graph.addEdge(addressManager.getAddresses()[7], addressManager.getAddresses()[9], 5);
    graph.addEdge(addressManager.getAddresses()[7], addressManager.getAddresses()[10], 15);
    graph.addEdge(addressManager.getAddresses()[8], addressManager.getAddresses()[10], 6);


    graph.printWeights();

    Address startAddress = addressManager.getAddresses().front();
    Address endAddress = addressManager.getAddresses().back();

    Stack<Node>* pathStack = graph.dijkstra(&startAddress, &endAddress);
    std::vector<std::string> route;
    std::cout << "Pathstack:\n" << pathStack;

    if (pathStack) {
        std::cout << "Planned route:\n";
        while (!pathStack->isEmpty()) {
            Node* node = pathStack->pop();
            route.push_back(node->address->name);
            std::cout << node->address->name << "\n";
        }
    } else {
        std::cerr << "No path found.\n";
    }

    return 0;
}
