#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T>
class LinkedList
{
public:
    T *firstNode;

    LinkedList() : firstNode(nullptr) {}

    void insert(T *newNode)
    {
        newNode->nextNode = firstNode;
        firstNode = newNode;
    }

    void remove(T *nodeToRemove)
    {
        T *currentNode = firstNode;
        T *previousNode = firstNode;
        while (currentNode != nullptr && *currentNode != *nodeToRemove)
        {
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
        }
        if (currentNode != nullptr)
        {
            if (currentNode == firstNode)
            {
                firstNode = firstNode->nextNode;
            }
            else
            {
                previousNode->nextNode = currentNode->nextNode;
            }
        }
    }

    T *findLowestCostNode()
    {
        if (firstNode == nullptr)
            return nullptr;
        T *currentNode = firstNode;
        T *lowestCostNode = firstNode;
        while (currentNode != nullptr)
        {
            if (currentNode->g < lowestCostNode->g)
            {
                lowestCostNode = currentNode;
            }
            currentNode = currentNode->nextNode;
        }
        return lowestCostNode;
    }

    bool isEmpty() const
    {
        return firstNode == nullptr;
    }

    bool contains(T *nodeToCheck) const
    {
        T *currentNode = firstNode;
        while (currentNode != nullptr)
        {
            if (*currentNode == *nodeToCheck)
            {
                return true;
            }
            currentNode = currentNode->nextNode;
        }
        return false;
    }
};

#endif
