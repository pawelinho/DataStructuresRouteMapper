#ifndef GRAPH_H
#define GRAPH_H

#include "address.h"
#include "node.h"
#include "linked_list.h"
#include "stack.h"
#include <vector>
#include <iostream>
#include <limits>
#include <unordered_map>

class Graph {
private:
    std::vector<std::pair<Address, std::vector<std::pair<Address, double>>>> adjacencyList;

public:
    void addNode(const Address& address) {
        adjacencyList.push_back({address, {}});
    }

    void addEdge(const Address& source, const Address& destination, double weight) {
        for (auto& node : adjacencyList) {
            if (node.first.name == source.name) {
                node.second.push_back({destination, weight});
                return;
            }
        }
    }

    void printGraph() const {
        for (const auto& node : adjacencyList) {
            std::cout << node.first.name << " -> ";
            for (const auto& edge : node.second) {
                std::cout << edge.first.name << " (" << edge.second << ") ";
            }
            std::cout << "\n";
        }
    }

    void printWeights() const {
        std::cout << "Edge Weights:\n";
        for (const auto& node : adjacencyList) {
            for (const auto& edge : node.second) {
                std::cout << node.first.name << " -> " << edge.first.name << " : " << edge.second << "\n";
            }
        }
    }

    LinkedList<Node>* getAdjacentNodes(const Address* address) const {
        LinkedList<Node>* adjacentNodes = new LinkedList<Node>();
        for (const auto& node : adjacencyList) {
            if (node.first.name == address->name) {
                for (const auto& edge : node.second) {
                    Node* adjNode = new Node(new Address(edge.first));
                    adjNode->costFromStart = edge.second;
                    adjacentNodes->insert(adjNode);
                }
                break;
            }
        }
        return adjacentNodes;
    }

    int getNumberOfNodes() const {
        return adjacencyList.size();
    }

    double getEdgeWeight(const Address* source, const Address* destination) const {
        for (const auto& node : adjacencyList) {
            if (node.first.name == source->name) {
                for (const auto& edge : node.second) {
                    if (edge.first.name == destination->name) {
                        return edge.second;
                    }
                }
            }
        }
        return 9999; // If edge not found, return a very large number
    }

    Node* findLowestNode(LinkedList<Node>* lst) {
        double lowest = std::numeric_limits<double>::max();
        Node* lowestNode = nullptr;
        Node* current = lst->firstNode;
        while (current != nullptr) {
            if (current->costFromStart < lowest) {
                lowest = current->costFromStart;
                lowestNode = current;
            }
            current = current->nextNode;
        }
        return lowestNode;
    }

    Stack<Node>* dijkstra(Address* start, Address* end) {
        LinkedList<Node>* open = new LinkedList<Node>();
        Node* startNode = new Node(start);
        startNode->costFromStart = 0;
        open->insert(startNode);

        std::unordered_map<std::string, Node*> visitedNodes;
        visitedNodes[start->name] = startNode;

        std::cout << "Starting Dijkstra's Algorithm\n";

        while (!open->isEmpty()) {
            Node* currentNode = findLowestNode(open);
            open->remove(currentNode);

            std::cout << "Current Node: " << currentNode->address->name << " with cost: " << currentNode->costFromStart << "\n";

            if (currentNode->address->name == end->name) {
                return reconstructPath(currentNode);
            }

            LinkedList<Node>* adjacentNodes = getAdjacentNodes(currentNode->address);
            Node* adjNode = adjacentNodes->firstNode;
            while (adjNode != nullptr) {
                double tentativeCost = currentNode->costFromStart + getEdgeWeight(currentNode->address, adjNode->address);
                std::cout << "Checking adj: " << adjNode->address->name << " with tentative cost: " << tentativeCost << "\n";

                if (visitedNodes.find(adjNode->address->name) == visitedNodes.end() || tentativeCost < adjNode->costFromStart) {
                    adjNode->costFromStart = tentativeCost;
                    adjNode->parentNode = currentNode;
                    if (visitedNodes.find(adjNode->address->name) == visitedNodes.end()) {
                        open->insert(adjNode);
                        visitedNodes[adjNode->address->name] = adjNode;
                    }
                }

                adjNode = adjNode->nextNode;
            }

        }

        return nullptr; // If no path is found
    }

    Stack<Node>* reconstructPath(Node* goalNode) {
        Stack<Node>* pathStack = new Stack<Node>(getNumberOfNodes());
        Node* currentNode = goalNode;
        while (currentNode != nullptr) {
            pathStack->push(currentNode);
            currentNode = currentNode->parentNode;
        }
        return pathStack;
    }
};

#endif
