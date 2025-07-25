#ifndef FRACTION_H
#define FRACTION_H

#include<iostream>

class Fraction
{
public:
    Fraction();
    Fraction(int num,int denom);
    void add(const Fraction &frac);
    void mult(const Fraction &frac);
    double decimal();
    int getNum();
    int getDenom();
    friend std::ostream& operator <<
        (std::ostream &out,const Fraction &frac);

private:
    int num;  // numerator
    int denom;  // denominator
    void reduce();  // 约分
    int gcd(int u,int v); // 求最大公约数
};

#endif // FRACTION_H
