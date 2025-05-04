#pragma once

#include <iostream>

namespace stack {

template<class T, class FRIEND>
class ListNode {              
    private:
        T value;                  
        ListNode *next;         
        ListNode(void) { next = nullptr; } 
        friend FRIEND;
};

template<class T>
class Stack {
    typedef class ListNode<T, Stack<T>> Node;
    Node *top;

    public:
        Stack(void) : top(nullptr) {}  

        bool empty(void) {            
            return top == nullptr;
        }

        void push(T n) {              
            Node *newNode = new Node;
            newNode->value = n;
            newNode->next = top;
            top = newNode;
        }

        T pop(void) {                 
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }
            T value = top->value;
            Node *temp = top;
            top = top->next;
            delete temp;
            return value;
        }

        T top_inf(void) {             
            if (empty()) {
                throw std::runtime_error("Stack is empty");
            }
            return top->value;
        }
        
        void output();
        Stack(const Stack<T>& stack);
        Stack<T>& operator=(const Stack<T>& stack);

        ~Stack(void) {                 
            while (!empty()) {
                pop();
            }
        }
};

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack) {
    if (this == &stack) {
        return *this;  
    }

    while (!empty()) {
        pop();
    }

    if (stack.top) {
        Node* current = stack.top;
        Node* newTop = new Node();
        newTop->value = current->value;
        this->top = newTop;

        Node* newCurrent = newTop;
        current = current->next;

        while (current) {
            Node* newNode = new Node();
            newNode->value = current->value;
            newCurrent->next = newNode;
            newCurrent = newNode;
            current = current->next;
        }
    }
    return *this;
}

template<class T>
void Stack<T>::output() {
    Node* current = top;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            std::cout << " * ";
        }
        std::cout << current->value;
        current = current->next;
        first = false;
    }
    std::cout << std::endl;
}

template<class T>
Stack<T>::Stack(const Stack<T>& stack) {
    top = nullptr; 
    Node* node = stack.top;
    while (node != nullptr) {
        this->push(node->value); 
        node = node->next;
    }
}

}
