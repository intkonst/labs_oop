#include <iostream>

#include "app.h"


namespace {

constexpr int BUFFER_SIZE = 1024;

} // namespace


namespace app {

void run(int argc, char** argv) {
    std::cout << "Hello world!" << std::endl;
}

} // namespace app
