#include "rational.h"
#include <iostream>
#include <stdexcept>

Rational::Rational(long long n) {
    numer=n;
    denom=1;
}

void Rational::update() {
    if (numer%denom==0)
    {
        numer/=denom;
        denom=1;
    }
}

void Rational::copy(Rational x) {
    numer = x.numer;
    denom = x.denom;
}

void Rational::sum(Rational x, Rational y) {
    Rational z(x.numer*y.denom+y.numer*x.denom, x.denom*y.denom);
    this->copy(z);
}

void Rational::print()const {
    std::cout<<numer<<"/"<<denom<<"\n";
}

void Rational::product(Rational x, Rational y) {
    Rational z(x.numer*y.numer, x.denom*y.denom);
    this->copy(z);
}

void Rational::division(Rational x, Rational y) {
    Rational z(x.numer*y.denom, x.denom*y.numer);
    this->copy(z);
}

void Rational::difference(Rational x, Rational y) {
    Rational z(x.numer*y.denom-y.numer*x.denom, x.denom*y.denom);
    this->copy(z);
}

Rational::Rational(long long n, long long d): numer(n)
{
    if (!d)
        throw std::invalid_argument("На ноль делить нельзя");
    else
    {
        denom=d;
        this->update();
    }
}