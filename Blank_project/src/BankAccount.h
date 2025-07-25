#ifndef  _BankAccount_h
#define  _BankAccount_h

#include<string>
#include<iostream>
using namespace std;

class BankAccount{
public:
    BankAccount(string n,double d); // constructor
    void deposit(double amount);  // methods
    void withdraw(double amount);
    double getBalance() const;
    void setName(string Newname);

private:
    string name;
    double balance;
};


#endif // _BanKAccount_h
