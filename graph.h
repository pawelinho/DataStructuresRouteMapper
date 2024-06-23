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

class Graph
{
private:
    std::vector<std::pair<Address, std::vector<std::pair<Address, double>>>> adjacencyList;

public:
    // Add a new node to the graph
    void addNode(const Address &address)
    {
        adjacencyList.push_back({address, {}});
    }

    // Add an edge between two nodes with a weight
    void addEdge(const Address &source, const Address &destination, double weight)
    {
        for (auto &node : adjacencyList)
        {
            if (node.first.name == source.name)
            {
                node.second.push_back({destination, weight});
                return;
            }
        }
    }

    // Logging the Graph
    void printGraph() const
    {
        for (const auto &node : adjacencyList)
        {
            std::cout << node.first.name << " -> ";
            for (const auto &edge : node.second)
            {
                std::cout << edge.first.name << " (" << edge.second << ") ";
            }
            std::cout << "\n";
        }
    }

    // Get adjacent nodes for a given address
    LinkedList<Node> *getAdjacentNodes(const Address *address) const
    {
        LinkedList<Node> *adjacentNodes = new LinkedList<Node>();
        for (const auto &node : adjacencyList)
        {
            if (node.first.name == address->name)
            {
                for (const auto &edge : node.second)
                {
                    Node *neighborNode = new Node(new Address(edge.first));
                    neighborNode->g = edge.second;
                    adjacentNodes->insert(neighborNode);
                }
            }
        }
        return adjacentNodes;
    }

    // Get the number of nodes in the graph
    int getNumberOfNodes() const
    {
        return adjacencyList.size();
    }

    // Get the weight of the edge between two nodes
    double getEdgeWeight(const Address *source, const Address *destination) const
    {
        for (const auto &node : adjacencyList)
        {
            if (node.first.name == source->name)
            {
                for (const auto &edge : node.second)
                {
                    if (edge.first.name == destination->name)
                    {
                        return edge.second;
                    }
                }
            }
        }
        return 9999; // If edge not found
    }

    // Dijkstra's algorithm to find the shortest path
    Stack<Node> *dijkstra(const Address *start, Address *&optimalEndNode)
    {
        LinkedList<Node> *openList = new LinkedList<Node>();
        Node *startNode = new Node(const_cast<Address *>(start));
        openList->insert(startNode);

        std::unordered_map<Address *, float> distanceMap;
        std::unordered_map<Address *, Node *> visitedNodes;
        distanceMap[startNode->address] = 0.0f;
        visitedNodes[startNode->address] = startNode;

        while (!openList->isEmpty())
        {
            Node *currentNode = openList->findLowestCostNode();
            openList->remove(currentNode);

            LinkedList<Node> *adjacentNodes = getAdjacentNodes(currentNode->address);
            Node *neighborNode = adjacentNodes->firstNode;
            while (neighborNode != nullptr)
            {
                float currentCost = currentNode->g + getEdgeWeight(currentNode->address, neighborNode->address);
                if (neighborNode->g == 0 || currentCost < neighborNode->g)
                {
                    neighborNode->g = currentCost;
                    neighborNode->parentNode = currentNode;
                    distanceMap[neighborNode->address] = currentCost;
                    visitedNodes[neighborNode->address] = neighborNode;
                }
                if (!openList->contains(neighborNode))
                {
                    openList->insert(neighborNode);
                }
                neighborNode = neighborNode->nextNode;
            }

            delete adjacentNodes; // Free memory allocated for adjacent nodes
        }

        // Find the node with the smallest distance
        float minDistance = 9999;
        for (const auto &[address, distance] : distanceMap)
        {
            if (distance < minDistance)
            {
                minDistance = distance;
                optimalEndNode = address;
            }
        }

        Node *optimalEndNodePointer = visitedNodes[optimalEndNode];

        return reconstructPath(optimalEndNodePointer);
    }

    // Reconstruct the path from the goal node to the start node
    Stack<Node> *reconstructPath(Node *goalNode)
    {
        Stack<Node> *pathStack = new Stack<Node>(getNumberOfNodes());
        Node *currentNode = goalNode;
        while (currentNode != nullptr)
        {
            pathStack->push(currentNode);
            currentNode = currentNode->parentNode;
        }
        return pathStack;
    }
};

#endif
