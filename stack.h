#ifndef STACK_H
#define STACK_H

template <class T>
class Stack {
private:
    T** stackArray;
    int maximumSize;
    int topIndex;

public:
    Stack(int size) : maximumSize(size), topIndex(-1) {
        stackArray = new T*[maximumSize];
    }

    ~Stack() {
        delete[] stackArray;
    }

    void push(T* item) {
        if (topIndex < maximumSize - 1) {
            stackArray[++topIndex] = item;
        }
    }

    T* pop() {
        if (topIndex >= 0) {
            return stackArray[topIndex--];
        }
        return nullptr;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    void print() const {
        for (int i = topIndex; i >= 0; --i) {
            stackArray[i]->print();
        }
    }
};

#endif
