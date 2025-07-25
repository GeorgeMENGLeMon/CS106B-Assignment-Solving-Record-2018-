#include "fraction.h"

Fraction::Fraction() {
    num = 1;
    denom = 1;
}

Fraction::Fraction(int num,int denom) {
    this->num = num;
    this->denom = denom;
}

void Fraction::add(const Fraction &other) {
    num = num*other.denom + denom*other.num;
    denom *= other.denom;
    reduce();
}

void Fraction::mult(const Fraction &other) {
    num *= other.num;
    denom *= other.denom;
}

double Fraction::decimal() {
    return (double)num/denom;
}

int Fraction::getNum() {
    return num;
}

int Fraction::getDenom() {
    return denom;
}

void Fraction::reduce() {
    int frac_gcd = gcd(num,denom);

    num /= frac_gcd;
    denom /= frac_gcd;
}

int Fraction::gcd(int u,int v) {
    if(!v) return u;
    else return gcd(v,u%v);
}

std::ostream& operator<<(std::ostream& out,const Fraction &frac) {
    out << frac.num << "/" << frac.denom;
    return out;
}
