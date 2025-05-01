#pragma once

#include <iostream>


namespace car {

class Car {
    private:
        enum class Color {
            COLORLESS = 0,
            RED = 1,
            GREEN = 2,
            BLUE = 3  
        };

        enum class EngineType {
            PETROL = 0,
            DIESEL = 1,
            ELECTRIC = 2
        };

        char* _state_number;
        int _color;
        int _engine_type;
        float _powerfull;
        int _id;

        static int _n;
    
    public:
        Car(char* state_number, int color, int engine_type, float powerfull);
        Car();
        ~Car();

        friend std::ostream& operator<<(std::ostream& os, const Car& car);
        friend std::istream& operator>>(std::istream& in, Car& car);
        friend bool operator==(const Car& el1, const Car& el2);
        friend bool operator<(const Car& el1, const Car& el2);

        static void readFromFile(const char* filename, Car** car_park, int& size);
        static void writeToFile(const char* filename, Car** car_park, int& size);

        static void print(Car**& car_park, int& size);
        static void sort(Car**& car_park, int& size);
    
        static void append(Car**& car_park, int& size, Car* car);
        static void remove(Car**& car_park, int& size, Car* car);

};

} // namespace car
