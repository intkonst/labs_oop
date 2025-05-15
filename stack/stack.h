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
        void reverse();
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
    std::cout << "функция вызвалась 1" << std::endl;
    if (this == &stack) {
        return *this;  
    }

    while (!empty()) {
        pop();
    }
    std::cout << "функция вызвалась" << std::endl;
    if (stack.top) {
        Node* current = stack.top;
        Node* newTop = new Node();
        newTop->value = current->value;
        this->top = newTop;

        Node* newCurrent = newTop;
        current = current->next;
        

        std::cout << "я в ифе" << std::endl;
        while (current) {
            Node* newNode = new Node();

            newNode->value = current->value;
            newCurrent->next = newNode;
            newCurrent = newNode;
            current = current->next;
            std::cout << "я в цикле" << std::endl;
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
void Stack<T>::reverse() {
 Node* current = top;
 top = nullptr;
 
 while (current) {
 Node* next = current->next;
 current->next = top;
 top = current;
 current = next;
 }
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



template<class T>
Stack<T>::Stack(const Stack<T>& stack) {
    Stack<T> temp;
    
    Node* current = stack.top;
    while (current != nullptr) {
        temp.push(current->value);
        current = current->next;
    }
    
    while (!temp.empty()) {
        this->push(temp.pop());
    }
}

}



