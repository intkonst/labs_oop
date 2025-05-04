#include <cstring>
#include <fstream>
#include <iostream>

#include "car.h"


namespace {

const int BUFFER_SIZE = 1024;

} // namespace


namespace car {

int Car::_n = 0;

Car::Car() {
    _id = _n++;
    std::cout << "Create car | ID: " << _id << std::endl;
}

Car::Car(char* state_number, int count_of_seats, bool is_electic, float power)
    : _count_of_seats(count_of_seats), _is_electic(is_electic), _power(power) {
    _state_number = new char[std::strlen(state_number) + 1];
    std::strcpy(_state_number, state_number);

    _id = _n++;
    std::cout << "Create car with parameters | ID: " << _id << std::endl;
}

Car::~Car() {
    delete[] _state_number;
    std::cout << "Delete car | ID: " << _id << std::endl;
}


bool operator==(const Car& el1, const Car& el2) {
    return el1._count_of_seats == el2._count_of_seats && el1._is_electic == el2._is_electic && el1._power == el2._power &&
           std::strcmp(el1._state_number, el2._state_number) == 0;
}

bool operator<(const Car& el1, const Car& el2) {
    return el1._power < el2._power;
}

std::istream& operator>>(std::istream& in, Car*& car) {
    char* state_number = new char[BUFFER_SIZE];
    int count_of_seats{};
    bool is_electic{};
    float power{};

    in >> state_number >> count_of_seats >> is_electic >> power;
    car = new Car(state_number, count_of_seats, is_electic, power);
    delete[] state_number;

    return in;
}

std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << "Car ID: " << car._id << ", State number: " << car._state_number << ", ";
    os << "Count of seats: " << car._count_of_seats << ", ";
    os << (car._is_electic ? "Is electric" : "Isn't electric") << ", ";
    os << "Power: " << car._power;

    return os;
}

void Car::readFromFile(const char* filename, Car** carpark, int& size) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << filename << std::endl;
        throw std::runtime_error("Error: can't open file!");
    }

    size = 0;
    Car* car = nullptr;
    Car** buffer = new Car*[BUFFER_SIZE];

    while (!file.eof()) {
        file >> car;
        buffer[size++] = car;
    }

    delete[] carpark;
    carpark = new Car*[size];
    for (int i = 0; i < size; i++) {
        carpark[i] = buffer[i];
    }
    delete[] buffer;
}

void Car::writeToFile(const char* filename, Car** carpark, int& size) {
    std::ofstream file(filename);

    for (int i = 0; i < size; i++) {
        file << carpark[i]->_state_number << ' ' << carpark[i]->_count_of_seats << ' ' << carpark[i]->_is_electic << ' ' << carpark[i]->_power;
        if (i != size - 1) {
            file << std::endl;
        }
    }
}

void Car::print(Car**& carpark, int& size) {
    for (int i = 0; i < size; i++) {
        std::cout << *carpark[i] << std::endl;
    }
}

void Car::edit_power(Car**& carpark, int& size, int id, float power) {
    bool id_is_find = false;
    for(int i = 0; i < size; i++) {
        if (carpark[i]->_id == id) {
            id_is_find = true;
            carpark[i]->_power = power;
        }
    }
    if (!id_is_find){
        std::cout << "Error: Unknown ID of car. Check correct ID by using print function." << std::endl;
    }
}

void Car::sort(Car**& carpark, int& size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*carpark[j + 1] < *carpark[j]) {
                std::swap(carpark[j], carpark[j + 1]);
            }
        }
    }
}

void Car::append(Car**& carpark, int& size, Car* car) {
    if (carpark != nullptr) {
        Car** buffer = carpark;
        carpark = new Car*[size + 1];
        for (int i = 0; i < size; i++) {
            carpark[i] = buffer[i];
        }
        carpark[size++] = car;
        delete[] buffer;
    }
}


void Car::remove(Car**& carpark, int& size, Car* car) {
    for (int i = 0; i < size; i++) {
        if (*carpark[i] == *car) {
            for (int j = i; j < size - 1; j++) {
                carpark[j] = carpark[j + 1];
            }
            size--;
        }
    }
}

} // namespace car
