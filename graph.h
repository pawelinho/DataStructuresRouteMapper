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
        return 9999; // If edge not found
    }

    Stack<Node>* dijkstra(const Address* start, const Address* end) {
        LinkedList<Node>* openList = new LinkedList<Node>();
        Node* startNode = new Node(const_cast<Address*>(start));
        startNode->costFromStart = 0;
        openList->insert(startNode);

        std::unordered_map<std::string, Node*> visitedNodes;
        visitedNodes[startNode->address->name] = startNode;

        std::unordered_map<std::string, float> costMap;
        costMap[startNode->address->name] = 0.0f;

        std::cout << "Starting Dijkstra\n";

        while (!openList->isEmpty()) {
            Node* currentNode = openList->findLowestCostNode();
            openList->remove(currentNode);

            if (currentNode->address->name == end->name) {
                std::cout << "End node reached: " << currentNode->address->name << "\n";
                delete openList; // Free memory allocated for the open list
                return reconstructPath(currentNode);
            }

            std::cout << "Current Node: " << currentNode->address->name << " with cost: " << currentNode->costFromStart << "\n";

            LinkedList<Node>* adjacentNodes = getAdjacentNodes(currentNode->address);
            Node* adjNode = adjacentNodes->firstNode;
            while (adjNode != nullptr) {
                float tentativeCost = currentNode->costFromStart + getEdgeWeight(currentNode->address, adjNode->address);
                std::cout << "Checking adj: " << adjNode->address->name << " with tentative cost: " << tentativeCost << "\n";

                if (costMap.find(adjNode->address->name) == costMap.end() || tentativeCost < costMap[adjNode->address->name]) {
                    adjNode->costFromStart = tentativeCost;
                    adjNode->parentNode = currentNode;
                    costMap[adjNode->address->name] = tentativeCost;
                    visitedNodes[adjNode->address->name] = adjNode;

                    if (!openList->contains(adjNode)) {
                        openList->insert(adjNode);
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
