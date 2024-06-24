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
                    neighborNode->costFromStart = edge.second;
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
        startNode->costFromStart = 0;
        openList->insert(startNode);

        std::unordered_map<std::string, Node *> visitedNodes;
        visitedNodes[startNode->address->name] = startNode;

        std::cout << "Starting Dijkstra\n";

        while (!openList->isEmpty())
        {
            Node *currentNode = openList->findLowestCostNode();
            openList->remove(currentNode);

            std::cout << "Current Node: " << currentNode->address->name << " with cost: " << currentNode->costFromStart << "\n";

            LinkedList<Node> *adjacentNodes = getAdjacentNodes(currentNode->address);
            Node *adjNode = adjacentNodes->firstNode;
            while (adjNode != nullptr)
            {
                float tentativeCost = currentNode->costFromStart + getEdgeWeight(currentNode->address, adjNode->address);
                std::cout << "Checking adj node: " << adjNode->address->name << " with tentative cost: " << tentativeCost << "\n";
                if (visitedNodes.find(adjNode->address->name) == visitedNodes.end() || tentativeCost < visitedNodes[adjNode->address->name]->costFromStart)
                {
                    adjNode->costFromStart = tentativeCost;
                    adjNode->parentNode = currentNode;
                    visitedNodes[adjNode->address->name] = adjNode;
                    if (!openList->contains(adjNode))
                    {
                        openList->insert(adjNode);
                    }
                }
                adjNode = adjNode->nextNode;
            }
        }

        // Find the node with the smallest distance that is not the start node
        float minDistance = 9999;
        for (const auto &[name, node] : visitedNodes)
        {
            if (node->costFromStart < minDistance && name != start->name)
            {
                minDistance = node->costFromStart;
                optimalEndNode = node->address;
            }
        }

        if (optimalEndNode == nullptr)
        {
            optimalEndNode = startNode->address;
        }

        Node *optimalEndNodePointer = visitedNodes[optimalEndNode->name];

        return reconstructPath(optimalEndNodePointer);
    }

    // Reconstruct the path from the goal node to the start node
    Stack<Node> *reconstructPath(Node *goalNode)
    {
        Stack<Node> *pathStack = new Stack<Node>(getNumberOfNodes());
        Node *currentNode = goalNode;
        while (currentNode->parentNode != nullptr)
        {
            pathStack->push(currentNode);
            currentNode = currentNode->parentNode;
        }
        return pathStack;
    }
};

#endif
