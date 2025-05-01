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

    char* marsName = new char[BUFFER_SIZE];
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

int menu() {
    std::cout << std::endl;
    std::cout << " ============== ГЛАВНОЕ МЕНЮ ========================\n";
    std::cout << "1 - считать файл\t\t 4 - добавление нового автомобиля" << std::endl;
    std::cout << "2 - записать файл\t\t 5 - удаление автомобиля" << std::endl;
    std::cout << "3 - сортировка файла\t\t 6 - редактирование файла" << std::endl;
    std::cout << "7 - вывод файла \t\t 8 - выход" << std::endl;
    std::cout << "Для выбора операции введите цифру от 1 до 8: " << std::endl;
    int resp;
    std::cin >> resp;
    std::cin.clear();
    std::cin.ignore(10, '\n');
    std::cout << std::endl;
    if (resp > 8 || resp < 1){
        return -1;
    }
    return resp;
}

void runInteractiveMode(){
    std::cout << "Welcome to interactive mode!" << std::endl;
    
    const char* filename = "carpark.txt";
    const char* fileout = "output.txt";

    int size = 0;
    car::Car** carpark = new car::Car*[BUFFER_SIZE];

    while (true) {
        switch (menu()) {
            case 1:
                delete[] carpark;
                carpark = new car::Car*[BUFFER_SIZE];
                car::Car::readFromFile(filename, carpark, size);
                break;
            case 2:
                car::Car::writeToFile(fileout, carpark, size);
                break;
            case 3:
                car::Car::sort(carpark, size);
                break;
            case 4:
                //добавление автомобиля
            
                // char* state_number = new char[BUFFER_SIZE];
                // std::strcpy(state_number, "e190md78");
                // planet::Planet* mars = new planet::Planet(marsName, 6786, 1, 2);
                // delete marsName;
                // cat::Car::append(car_park, size, car);
                // break;
                return;

            case 5:
                //удаление автомобиля по id

                // sort_db(planets, n_planet);
                // break;
                return;
            case 6:
                //редактировать файл
                return;
            case 7:
                car::Car::print(carpark, size);
                break;
            case 8:
                std::cout << "Goodbye!" << std::endl;
                return;
            default:
                std::cout << " Неправильный ввод" << std::endl;
                break;
        }
    }
}

void run(int argc, char** argv) {
    if (argc == 2 && std::strcmp(argv[1], "-i") == 0) {
        runInteractiveMode();
        return;
    }
    runDemonstrativeMode();
}

} // namespace app
