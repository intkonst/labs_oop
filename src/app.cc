#include <iostream>
#include <cstring>

#include "app.h"
#include "../planet/planet.h"
#include "../car/car.h"

namespace {

const int BUFFER_SIZE = 1024;

} // namespace

namespace app {

void runDemonstrativeMode(){
    std::cout << "Welcome to demonstrative mode!\n\n" << std::endl;

    const char* filename = "system.txt";

    std::cout << "\nCreate system of planets...\n" << std::endl;

    planet::Planet** solarSystem = new planet::Planet*[BUFFER_SIZE];
    int size = 0;
    planet::Planet::readFromFile(filename, solarSystem, size);

    std::cout << std::endl << "\nSystem before sorting: \n" << std::endl;
    planet::Planet::print(solarSystem, size);
    planet::Planet::sort(solarSystem, size);
    std::cout << std::endl << "\nSystem after sorting: \n" << std::endl;
    planet::Planet::print(solarSystem, size);
    std::cout << std::endl;
    char* marsName = new char[BUFFER_SIZE];
    std::strcpy(marsName, "Mars");
    planet::Planet* mars = new planet::Planet(marsName, 6786, 1, 2);
    delete marsName;

    std::cout << "\n\n" << *mars << "  => adding to system" << std::endl << std::endl;
    std::cout << "\nSystem before add planet: \n" << std::endl;
    planet::Planet::append(solarSystem, size, mars);
    planet::Planet::print(solarSystem, size);
    planet::Planet* removePlanet = solarSystem[std::min(size, 4)];
    std::cout << "\n\n" << *removePlanet << " => remove from system" << std::endl << std::endl;
    planet::Planet::remove(solarSystem, size, removePlanet);
    std::cout << "\nSystem after add planet: \n" << std::endl;
    planet::Planet::print(solarSystem, size);

    planet::Planet::edit_diameter(solarSystem, size, 1, 1);

    const char* fileout = "output.txt";
    std::cout << "\nWrite updates in the file: " << fileout << std::endl;
    planet::Planet::writeToFile(fileout, solarSystem, size);

    delete[] solarSystem;

    std::cout << "\nGoodbye!" << std::endl;

}

int menu() {
    std::cout << std::endl;
    std::cout << "================================= ГЛАВНОЕ МЕНЮ ==================================\n";
    std::cout << "1 - считать файл в буфер\t\t 4 - добавление нового автомобиля в буфер" << std::endl;
    std::cout << "2 - записать файл из буфера\t\t 5 - удаление автомобиля из буфера по ID" << std::endl;
    std::cout << "3 - сортировка буфера\t\t\t 6 - редактирование автомобиля по ID" << std::endl;
    std::cout << "7 - вывод буфера \t\t\t 8 - выход" << std::endl;
    std::cout << "\nДля выбора операции введите цифру от 1 до 8: " << std::endl;
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

int edit_menu() {
    std::cout << std::endl;
    std::cout << "===================== МЕНЮ РЕДАКТИРОВАНИЯ =====================\n";
    std::cout << "1 - государственный номер\t\t3 - тип питания" << std::endl;
    std::cout << "2 - количество мест\t\t\t4 - мощность двигателя" << std::endl;
    std::cout << "\nДля выбора операции введите цифру от 1 до 4: " << std::endl;
    int resp;
    std::cin >> resp;
    std::cin.clear();
    std::cin.ignore(10, '\n');
    std::cout << std::endl;
    if (resp > 4 || resp < 1){
        return -1;
    }
    return resp;
}



void runInteractiveMode(){
    std::cout << "Welcome to interactive mode!" << std::endl;
    
    const char* filename = "carpark.txt";
    const char* fileout = "output.txt";

    int size = 0;
    float power = 0;
    int id = 0;
    int count_of_seats = 0;
    bool is_electic = false;
    char* buffer = new char[BUFFER_SIZE];
    car::Car** carpark = new car::Car*[BUFFER_SIZE];
    car::Car* new_car = new car::Car();

    while (true) {
        switch (menu()) {
            case 1:
                car::Car::readFromFile(filename, carpark, size);
                break;
            case 2:
                car::Car::writeToFile(fileout, carpark, size);
                break;
            case 3:
                car::Car::sort(carpark, size);
                std::cout << "\nАвтомобили отсортированы по мощности двигателя...\n" << std::endl;
                break;

            case 4:
            std::cout << "\nВведите новый государственный номер: "<< std::endl;
            std::cin >> buffer;
            std::cout << "\nВведите новое количество мест: " << std::endl;
            std::cin >> count_of_seats;
            std::cout << "\nАвтомобиль электрический? <1/0>: " << std::endl;
            std::cin >> is_electic;
            std::cout << "\nВведите новую мощность: " << std::endl;
            std::cin >> power;

            new_car = new car::Car(buffer, count_of_seats, is_electic, power);
            car::Car::append(carpark, size, new_car);

            std::cout << "Автомобиль был успешно добален..." << std::endl;
            delete[] buffer;
            break;

            case 5:

                if (size != 0) {
                    car::Car::print(carpark, size);
                } else {
                    std::cout << "Буфер пустой => возврат в главное меню..." << std::endl;
                    break; 
                }

                std::cout << "\nВведите ID автомобиля: " << std::endl;
                std::cin >> id;
                std::cout << std::endl;
                car::Car::remove(carpark, size, car::Car::get_obj_by_id(carpark, size, id));
                break;
            case 6:
                if (size != 0) {
                    car::Car::print(carpark, size);
                } else {
                    std::cout << "Буфер пустой => возврат в главное меню..." << std::endl;
                    break; 
                }

                
                std::cout << "\nВведите ID автомобиля: " << std::endl;
                std::cin >> id;
                std::cout << std::endl;
                
                switch (edit_menu()) {
                    case 1: // гос номер
                        std::cout << "\nВведите новый государственный номер: "<< std::endl;
                        std::cin >> buffer;
                        car::Car::edit_state_number(carpark, size, id, buffer);
                        delete[] buffer;
                        break;
                    case 2: // количество мест
                      
                        std::cout << "\nВведите новое количество мест: " << std::endl;
                        std::cin >> count_of_seats;
                        car::Car::edit_count_of_seats(carpark, size, id, count_of_seats);
                        break;
                    case 3: // тип питания
                        
                        std::cout << "\nАвтомобиль электрический? <1/0>: " << std::endl;
                        std::cin >> is_electic;
                        car::Car::edit_type(carpark, size, id, is_electic);
                        break;
                    case 4: // мощность
                        std::cout << "\nВведите новую мощность: " << std::endl;
                        std::cin >> power;
                        car::Car::edit_power(carpark, size, id, power);
                        break;
                        
                    default:
                        std::cout << "Неправильный ввод, попробуйте снова..." << std::endl;
                        

                } 
                break;
            case 7:
                car::Car::print(carpark, size);
                break;
            case 8:
                std::cout << "Goodbye!" << std::endl;
                return;
            default:
                std::cout << "Неправильный ввод, попробуйте снова..." << std::endl;
                break;
        }
        id = 0;
        power = 0;
        is_electic = 0;
        count_of_seats = 0;
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
