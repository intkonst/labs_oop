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
    base = 0;
    numerator = 0;
    denominator = 1;
    positive = true;

    const size_t strLen = std::strlen(str);

    if (strLen == 0) {
        throw std::invalid_argument("Empty input string");
    }

    // Определение начального режима парсера
    enum class Mode {
        BASE,       // Парсим целую часть
        NUMERATOR,   // Парсим числитель
        DENOMINATOR  // Парсим знаменатель
    };

    Mode mode = (std::strchr(str, SPACE) ? Mode::BASE : Mode::NUMERATOR);

    for (size_t i = 0; i < strLen; ++i) {
        const char current = str[i];

        // Обработка знака
        if (current == MINUS && i == 0) {
            positive = false;
            continue;
        }

        // Обработка разделителей
        switch (current) {
            case SPACE:
                if (mode == Mode::BASE) {
                    mode = Mode::NUMERATOR;
                    continue;
                }
                break;
                
            case SLASH:
                if (mode == Mode::NUMERATOR) {
                    mode = Mode::DENOMINATOR;
                    continue;
                }
                break;
        }

        // Обработка цифр
        if (char_is_num(current)) {
            const int digit = char_to_int(current);
            
            switch (mode) {
                case Mode::BASE:
                    base = base * 10 + digit;
                    if (base > MAX_INT) throw std::invalid_argument("Whole part is very large");
                    break;
                    
                case Mode::NUMERATOR:
                    numerator = numerator * 10 + digit;
                    if (numerator > MAX_INT) throw std::invalid_argument("Numerator is very large");
                    break;
                    
                case Mode::DENOMINATOR:
                    denominator = denominator * 10 + digit;
                    if (denominator > MAX_INT) throw std::invalid_argument("Denominator is very large");
                    break;
            }
        } else {
            throw std::invalid_argument("Invalid character in input. ");
        }
    }

    // Проверка корректности результата
    if (denominator == 0 && numerator != 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    if (mode == Mode::NUMERATOR && std::strchr(str, SLASH)) {
        throw std::invalid_argument("Invalid fraction format");
    }
}

Fraction::Fraction() : base(0), numerator(0), denominator(1), positive(true) {
}

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

void Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
}

void Fraction::operator+=(double number) {
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
