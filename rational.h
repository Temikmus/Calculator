#pragma once

class Rational {
public:
    Rational():numer(0), denom(1){}
    Rational(long long n);
    Rational(long long n, long long d);
    void update();
    void print()const;
    void copy(Rational x);
    void sum(Rational x, Rational y);
    void product(Rational x, Rational y);
    void division(Rational x, Rational y);
    void difference(Rational x, Rational y);
private:
    long long numer, denom;
};
