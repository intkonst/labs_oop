#include <iostream>
#include <cstring>
#include <cmath>

#include "fraction.hpp"


namespace {

constexpr char MINUS = '-';
constexpr char SPACE = ' ';
constexpr char SLASH = '/';

constexpr size_t BUFFER_SIZE = 1024;
constexpr int MAX_INT = 1000000;
constexpr int N_DEC = 4;

int gcd(int a, int b) {
    while (b != 0) {
        int с = b;
        b = a % b;
        a = с;
    }

    return a;
}

bool char_is_num(const char c) {
    return c >= '0' && c <= '9';
}

int char_to_int(const char c) {
    return c - '0';
}

bool is_char_in_str(const char* str, char ch) {
    return std::strchr(str, ch) != nullptr;
}

} // namespace


namespace fraction {

void Fraction::simplify() {
    int koef = gcd(numerator, denominator);
    numerator /= koef;
    denominator /= koef;
    base += static_cast<int>(numerator/denominator);
    numerator %= denominator;
}

void Fraction::is_correct() {
    if (denominator == 0) {
        throw std::runtime_error("Error: incorrect denominator in fraction.");
    }

    if (base >= MAX_INT || numerator >= MAX_INT || denominator >= MAX_INT) {
        throw std::runtime_error("Error: fraction is very big.");
    }
}

void Fraction::parse_str(const char* str) {
    positive = true;
    base = 0;
    numerator = 0;
    denominator = 0;

    int str_len = std::strlen(str);

    enum class Mode {
        base,
        numerator,
        denominator,
    };

    if (is_char_in_str(str, SPACE)) {
        Mode mode = Mode::base;
    } else {
        Mode mode = Mode::numerator;
    }

    for (int i = 0; i < str_len; i++) {
        char current = str[i];
        if (current == MINUS && i == 0) {
            positive = false;
        } else if (current == SPACE && mode == Mode::base) {
            mode = Mode::numerator;
        } else if (current == SLASH && mode == Mode::numerator) {
            mode = Mode::denominator;
        } else if (char_is_num(current)) {

            if (mode == Mode::base) {
                base = base * 10 + char_to_int(current);
                if (base > MAX_INT) throw std::runtime_error("Base is over big");

            } else if (mode == Mode::numerator) {
                numerator = numerator * 10 + char_to_int(current);
                if (numerator > MAX_INT) throw std::runtime_error("Numerator is over big");

            } else if (mode == Mode::denominator) {
                denominator = denominator * 10 + char_to_int(current);
                if (denominator > MAX_INT) throw std::runtime_error("Numerator is over big.");
            }

        } else {
            throw std::runtime_error("Invalid input string");
        }
    }

    if (mode == Mode::numerator) {
        throw std::runtime_error("Invalid input string");
    }
}

Fraction::Fraction() : base(0), numerator(0), denominator(1), positive(true) {}

Fraction::Fraction(const char* str) {
    parse_str(str);
    is_correct();
    simplify();
}

Fraction::Fraction(int base, int numerator, int denominator)
    : base(abs(base)), numerator(abs(numerator)), denominator(abs(denominator)), positive(base >= 0) {
    is_correct();
    simplify();
}

Fraction::Fraction(int numerator, int denominator) : base(0), numerator(abs(numerator)), denominator(abs(denominator)), positive(numerator >= 0) {
    is_correct();
    simplify();
}

Fraction::Fraction(double num) : base(0) {
    numerator = abs(static_cast<int>(std::pow(10, N_DEC) * num));
    denominator = std::pow(10, N_DEC);
    positive = num >= 0;
    simplify();
}

Fraction Fraction::operator+(const Fraction& other) const {
    return Fraction((this->positive ? 1 : -1) * (this->base * this->denominator + this->numerator) * other.denominator +
                        (other.positive ? 1 : -1) * (other.base * other.denominator + other.numerator) * this->denominator,
                    this->denominator * other.denominator);
}

Fraction Fraction::operator+(double number) const {
    return *this + Fraction(number);
}

Fraction Fraction::operator+(int number) const {
    return *this + Fraction(number, 0, 1);
}

Fraction operator+(double number, const Fraction& other) {
    return other + number;
}

Fraction operator+(int number, const Fraction& other) {
    return other + number;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
}

Fraction& Fraction::operator+=(double number) {
    *this = *this + number;
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    if (!fraction.positive) {
        os << MINUS;
    }
    if (fraction.base != 0) {
        os << fraction.base << SPACE;
    }
    if (fraction.numerator != 0) {
        os << fraction.numerator << SLASH << fraction.denominator;
    }
    if (fraction.numerator == 0 && fraction.base == 0) {
        os << 0;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& fraction) {
    char str[BUFFER_SIZE];
    is.getline(str, sizeof(str));
    fraction = Fraction(str);
    return is;
}


} // namespace fraction
