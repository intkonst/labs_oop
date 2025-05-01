#pragma once

#include <iostream>


namespace planet {

class Planet {
 private:
    char* _name;
    int _diameter;
    bool _has_life;
    int _count_of_satellites;
    int _id;
    
    static int _n;

 public:
    Planet(char* name, int diameter, bool has_life, int count_of_satellites);
    Planet();
    ~Planet();

    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::istream& operator>>(std::istream& in, Planet& planet);
    friend bool operator==(const Planet& el1, const Planet& el2);
    friend bool operator<(const Planet& el1, const Planet& el2);

    static void readFromFile(const char* filename, Planet** planets, int& size);
    static void writeToFile(const char* filename, Planet** planets, int& size);

    static void print(Planet**& planets, int& size);
    static void sort(Planet**& planets, int& size);

    static void append(Planet**& planets, int& size, Planet* planet);
    static void remove(Planet**& planets, int& size, Planet* planet);
};

}  // namespaace planet
