#include "BankAccount.h"

BankAccount::BankAccount(string n,double b)
{
    name = n;
    balance = b;
}

void BankAccount::deposit(double amount)
{
    balance += amount;
}

void BankAccount::withdraw(double amount)
{
    if(balance >= amount) balance -= amount;
    else cerr << "Your balance is insufficient" << endl;
}

double BankAccount::getBalance() const
{
    return balance;
}

void BankAccount::setName(string Newname)
{
    name = Newname;
}
