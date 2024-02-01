#include <stdexcept>
#define PI 3.14159265358979323846

bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

int calculateGCD(int a, int b) {
    if (b<0 || a<0)
        throw std::invalid_argument ("Can't find GSD between negative numbers");
    if (b == 0) {
        return a;
    }
    return calculateGCD(b, a % b);
}

int calculateLCM(int a, int b) {
    int gcd = calculateGCD(a, b);
    return (a * b) / gcd;
}

// Функция для быстрого возведения в степень
double power(double base, int exponent) {
    if (exponent < 0) {
        throw std::invalid_argument ("Can't find power, because exponent is negative");
    }
    double result = 1.0;
    while (exponent > 0) {
        // Если степень четная
        if (exponent % 2 == 0) {
            base *= base;
            exponent /= 2;
        } else {
            result *= base;
            exponent -= 1;
        }
    }

    return result;
}

double calculateRoot(double base, int exponent) {
    if (base < 0 && exponent%2 == 0) {
        // Если основание отрицательное и степень чётная, корень не определен для вещественных чисел
        throw std::invalid_argument ("Can't square, because the number is negative");
    }
    // Начальное значение для метода Ньютона
    double x = base;

    // Количество итераций для приближенного вычисления
    int iterations = 1000;

    // Применение метода Ньютона для приближенного вычисления корня
    for (int i = 0; i < iterations; ++i) {
        x = ((exponent - 1) * x + base / power(x, exponent - 1)) / exponent;
    }
    return x;
}

unsigned long long factorial(int n) {
    if (n<0)
        throw std::invalid_argument ("Can't find the factorial, because number is negative");
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Функция для вычисления синуса угла в градусах
double calculateSin(double angleDegrees) {
    // Преобразование угла из градусов в радианы
    double angleRadians = angleDegrees * 3.14159265358979323846 / 180.0;

    // Ряд Тейлора для синуса
    double result = 0;
    for (int n = 0; n < 15; ++n) {
        result += (power(-1, n) * power(angleRadians, 2 * n + 1)) / factorial(2 * n + 1);
    }

    return result;
}

double toRadians(double degrees) {
    return degrees * (PI / 180.0);
}

// Функция для вычисления косинуса угла в градусах
double calculateCos(double angleDegrees) {
    // Переводим угол из градусов в радианы
    double radians = toRadians(angleDegrees);

    // Ряд Тейлора для вычисления косинуса
    double result = 1.0;
    double term = 1.0;

    for (int i = 1; i <= 10; ++i) {
        term *= (-radians * radians) / ((2 * i - 1) * (2 * i));
        result += term;
    }

    return result;
}

