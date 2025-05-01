#include <cstring>
#include <fstream>
#include <iostream>

#include "planet.hpp"


namespace {

const int BUFFER_SIZE = 256;

} // namespace


namespace planet {

int Planet::_n = 0;

Planet::Planet() {
    _id = _n++;
    std::cout << "Creating planet without args ID=" << _id << std::endl;
}

Planet::Planet(char* name, int diameter, bool has_life, int count_of_satellites)
    : _diameter(diameter), _has_life(has_life), _count_of_satellites(count_of_satellites) {
    _name = new char[std::strlen(name) + 1];
    std::strcpy(_name, name);

    _id = _n++;
    std::cout << "Creating planet with args ID=" << _id << std::endl;
}

Planet::~Planet() {
    delete[] _name;
    std::cout << "Deleting planet ID=" << _id << std::endl;
}

std::istream& operator>>(std::istream& in, Planet*& planet) {
    char* name = new char[BUFFER_SIZE];
    int diameter{};
    bool has_life{};
    int count_of_satellites{};

    in >> name >> diameter >> has_life >> count_of_satellites;
    planet = new Planet(name, diameter, has_life, count_of_satellites);
    delete[] name;

    return in;
}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << "Planet ID: " << planet._id << ", " << planet._name << ": ";
    os << "diametr - " << planet._diameter << ", ";
    os << (planet._has_life ? "has life" : "has not life") << ", ";
    os << "count of satellites - " << planet._count_of_satellites;

    return os;
}

bool operator==(const Planet& el1, const Planet& el2) {
    return el1._diameter == el2._diameter && el1._has_life == el2._has_life && el1._count_of_satellites == el2._count_of_satellites &&
           std::strcmp(el1._name, el2._name) == 0;
}

bool operator<(const Planet& el1, const Planet& el2) {
    return el1._diameter < el2._diameter;
}


void Planet::readFromFile(const char* filename, Planet** planets, int& size) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << filename << std::endl;
        throw std::runtime_error("Can't open file");
    }

    size = 0;
    Planet* planet = nullptr;
    Planet** buffer = new Planet*[BUFFER_SIZE];

    while (!file.eof()) {
        file >> planet;
        buffer[size++] = planet;
    }

    delete[] planets;
    planets = new Planet*[size];
    for (int i = 0; i < size; i++) {
        planets[i] = buffer[i];
    }
    delete[] buffer;
}

void Planet::writeToFile(const char* filename, Planet** planets, int& size) {
    std::ofstream file(filename);

    for (int i = 0; i < size; i++) {
        file << planets[i]->_name << ' ' << planets[i]->_diameter << ' ' << planets[i]->_has_life << ' ' << planets[i]->_count_of_satellites;
        if (i != size - 1) {
            file << std::endl;
        }
    }
}

void Planet::print(Planet**& planets, int& size) {
    for (int i = 0; i < size; i++) {
        std::cout << *planets[i] << std::endl;
    }
}

void Planet::sort(Planet**& planets, int& size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*planets[j + 1] < *planets[j]) {
                std::swap(planets[j], planets[j + 1]);
            }
        }
    }
}

void Planet::append(Planet**& planets, int& size, Planet* planet) {
    if (planets != nullptr) {
        Planet** buffer = planets;
        planets = new Planet*[size + 1];
        for (int i = 0; i < size; i++) {
            planets[i] = buffer[i];
        }
        planets[size++] = planet;
        delete[] buffer;
    }
}

void Planet::remove(Planet**& planets, int& size, Planet* planet) {
    for (int i = 0; i < size; i++) {
        if (*planets[i] == *planet) {
            for (int j = i; j < size - 1; j++) {
                planets[j] = planets[j + 1];
            }
            size--;
        }
    }
}

} // namespace planet
