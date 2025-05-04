#pragma once

#include <iostream>


namespace car {

class Car {
    private:

        char* _state_number;
        int _count_of_seats;
        bool _is_electic;
        float _power;
        int _id;

        static int _n;
    
    public:
        Car(char* state_number, int count_of_seats, bool is_electic, float power);
        Car();
        ~Car();

        friend std::ostream& operator<<(std::ostream& os, const Car& car);
        friend std::istream& operator>>(std::istream& in, Car& car);
        friend bool operator==(const Car& el1, const Car& el2);
        friend bool operator<(const Car& el1, const Car& el2);

        static void readFromFile(const char* filename, Car** car_park, int& size);
        static void writeToFile(const char* filename, Car** car_park, int& size);

        static void print(Car**& car_park, int& size);
        static void edit_power(Car**&, int& size, int id, float power);
        static void sort(Car**& car_park, int& size);
    
        static void append(Car**& car_park, int& size, Car* car);
        static void remove(Car**& car_park, int& size, Car* car);

};

} // namespace car
