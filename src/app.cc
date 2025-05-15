#include <iostream>

#include "../stack/stack.h"


namespace {

void Multipliers(int num, stack::Stack<int>* stack) {
    for (int i = 2; i <= num; i++) {
        while (num % i == 0) {
            stack->push(i);
            num /= i;
        }
    }
}

} // namespace


namespace app {

void run(int argc, char** argv) {
    int num = 0;
    std::cout << "Welcome! Enter num [num>1]: " << std::endl;
    std::cin >> num;

    if (num <= 1) {
        throw std::invalid_argument("Incorrect input! Num must be >1. Try again.");
    }

    stack::Stack<int> stack_1; // = new stack::Stack<int>();
    Multipliers(num, &stack_1);
    std::cout << num << " = ";
    stack_1.output();
    
    stack::Stack<int> stack_2;
    stack_2 = stack::Stack<int>(stack_1);
    // std::cout << num << " = ";
    // stack_2.output();

    

    // stack_2.reverse();
    // std::cout << num << " = ";
    // stack_2.output();

    // stack_2 = stack_1;
    // std::cout << num << " = ";
    // stack_1.output();
    
    // std::cout << "it me 2" << std::endl;

    // delete stack_1;
    // delete stack_2;

}

} // namespace app

