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

        static void edit_power(Car**&, int& size, int id, float power);
        static void edit_type(Car**&, int& size, int id, bool is_electic);
        static void edit_count_of_seats(Car**& carpark, int& size, int id, bool count_of_seats);
        static void edit_state_number(Car**& carpark, int& size, int id, char* state_number);
        static void readFromFile(const char* filename, Car** car_park, int& size);
        static void writeToFile(const char* filename, Car** car_park, int& size);

        static void print(Car**& car_park, int& size);
        static void sort(Car**& car_park, int& size);
    
        static Car* get_obj_by_id(Car**& carpark, int& size, int id);

        static void append(Car**& car_park, int& size, Car* car);
        static void remove(Car**& car_park, int& size, Car* car);

};

} // namespace car
