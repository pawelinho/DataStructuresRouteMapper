#include <cassert>
#include "graph.h"
#include "address_manager.h"

void testDijkstra() {
    AddressManager addressManager;
    addressManager.addAddress("Delivery Depot", 10, 20);
    addressManager.addAddress("Address 1", 1, 4);
    addressManager.addAddress("Address 2", 2, 6);
    addressManager.addAddress("Address 3", 5, 8);
    addressManager.addAddress("Address 4", 6, 10);
    addressManager.addAddress("Address 5", 8, 10);
    addressManager.addAddress("Address 6", 13, 11);
    addressManager.addAddress("Address 7", 20, 14);

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
    graph.addEdge(addressManager.getAddresses()[5], addressManager.getAddresses()[6], 3);
    graph.addEdge(addressManager.getAddresses()[6], addressManager.getAddresses()[7], 4);

    Address startAddress = addressManager.getAddresses()[0];
    Address endAddress = addressManager.getAddresses()[7];

    Stack<Node>* pathStack = graph.dijkstra(&startAddress, &endAddress);
    assert(pathStack != nullptr);

    std::vector<std::string> expectedRoute = {"Delivery Depot", "Address 2", "Address 3", "Address 5", "Address 6", "Address 7"};
    std::vector<std::string> actualRoute;

    while (!pathStack->isEmpty()) {
        Node* node = pathStack->pop();
        actualRoute.push_back(node->address->name);
    }

    assert(expectedRoute == actualRoute);
}

int main() {
    testDijkstra();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
