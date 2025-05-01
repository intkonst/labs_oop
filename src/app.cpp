#include <iostream>
#include <cstring>

#include "app.hpp"
#include "../planet/planet.hpp"
#include "../car/car.hpp"

namespace {

    const int BUFFER_SIZE = 256;

} // namespace

namespace app {

    void runDemonstrativeMode(){
        std::cout << "Welcome to demonstrative mode!" << std::endl;

        const char* filename = "system.txt";

        planet::Planet** solarSystem = new planet::Planet*[BUFFER_SIZE];
        int size = 0;
        planet::Planet::readFromFile(filename, solarSystem, size);
    
        std::cout << std::endl << "Before sorting" << std::endl;
        planet::Planet::print(solarSystem, size);
        planet::Planet::sort(solarSystem, size);
        std::cout << std::endl << "After sorting" << std::endl;
        planet::Planet::print(solarSystem, size);
    
        char* plutoName = new char[6];
        std::strcpy(plutoName, "Pluno");
        planet::Planet* pluto = new planet::Planet(plutoName, 2280, 0, 1);
        delete plutoName;
        std::cout << std::endl << *pluto << " - appending to solar system" << std::endl << std::endl;
        planet::Planet::append(solarSystem, size, pluto);
        planet::Planet::print(solarSystem, size);
        planet::Planet* removePlanet = solarSystem[std::min(size, 5)];
        std::cout << std::endl << *removePlanet << " - removing from solar system" << std::endl << std::endl;
        planet::Planet::remove(solarSystem, size, removePlanet);
        planet::Planet::print(solarSystem, size);
    
        const char* fileout = "output.txt";
        std::cout << "Write changes to file " << fileout << std::endl;
        planet::Planet::writeToFile(fileout, solarSystem, size);
    
        delete[] solarSystem;

    }

    void runInteractiveMode(){
        std::cout << "Welcome to interactive mode!" << std::endl;

        const char* filename = "carpark.txt";
        

    }

    void run(int argc, char** argv){
        if (argc == 2 && std::strcmp(argv[1], "-i") == 0){
            runInteractiveMode();
            return;
        }
        runDemonstrativeMode();
    }

}
