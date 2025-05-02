#include <iostream>
#include <cstring>

#include "app.hpp"


namespace {

//code here

} // namespace

namespace app {

void runDemonstrativeMode() {
    std::cout << "Welcome to demonstrative mode!" << std::endl;
}

void runInteractiveMode() {
    std::cout << "Welcome to interactive mode!" << std::endl;
}

void run(int argc, char** argv) {
    if (argc == 2 && std::strcmp(argv[1], "-i") == 0) {
        runInteractiveMode();
        return;
    }
    runDemonstrativeMode();
}

} // namespace app
