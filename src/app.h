#pragma once

namespace app {
    
    enum class InteractiveAction {
        print = 1,
        read = 2,
        write = 3,
        append = 4,
        remove = 5,
        sort = 6,
        edit = 7,
        exit = 8
    };

    void runInteractiveMode();
    void runDemonstrativeMode();
    void run(int argc, char** argv);

} // namespace app
