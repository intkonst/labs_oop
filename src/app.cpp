#include <iostream>
#include <cstring>

#include "app.hpp"
#include "../planet/planet.hpp"
#include "../car/car.hpp"

namespace {

    const int BUFFER_SIZE = 1024;

} // namespace

namespace app {

    void runDemonstrativeMode(){
        std::cout << "Welcome to demonstrative mode!" << std::endl;

        const char* filename = "system.txt";

        planet::Planet** solarSystem = new planet::Planet*[BUFFER_SIZE];
        int size = 0;
        planet::Planet::readFromFile(filename, solarSystem, size);
    
        std::cout << std::endl << "System before sorting: " << std::endl;
        planet::Planet::print(solarSystem, size);
        planet::Planet::sort(solarSystem, size);
        std::cout << std::endl << "System after sorting: " << std::endl;
        planet::Planet::print(solarSystem, size);
    
        char* marsName = new char[6];
        std::strcpy(marsName, "Mars");
        planet::Planet* mars = new planet::Planet(marsName, 6786, 1, 2);
        delete marsName;

        std::cout << std::endl << *mars << "  => adding to system" << std::endl << std::endl;
        planet::Planet::append(solarSystem, size, mars);
        planet::Planet::print(solarSystem, size);
        planet::Planet* removePlanet = solarSystem[std::min(size, 4)];
        std::cout << std::endl << *removePlanet << " => remove from system" << std::endl << std::endl;
        planet::Planet::remove(solarSystem, size, removePlanet);
        planet::Planet::print(solarSystem, size);

        planet::Planet::edit_diameter(solarSystem, size, 1, 1);
    
        const char* fileout = "output.txt";
        std::cout << "Write updates in the file: " << fileout << std::endl;
        planet::Planet::writeToFile(fileout, solarSystem, size);
    
        delete[] solarSystem;

    }

    void runInteractiveMode(){
        std::cout << "Welcome to interactive mode!" << std::endl;

        
        const char* filename = "carpark.txt";
        
        int size = 0;
        car::Car** carpark = new car::Car*[BUFFER_SIZE];
        car::Car::readFromFile(filename, carpark, size);

        const char* fileout = "output.txt";
        car::Car::writeToFile(fileout, carpark, size);


    }

    void run(int argc, char** argv){
        if (argc == 2 && std::strcmp(argv[1], "-i") == 0){
            runInteractiveMode();
            return;
        }
        runDemonstrativeMode();
    }

}
