#pragma once

#include <iostream>
#include <string>
#include <vector>


class myType{
public:

    myType();
    myType(std::string input);
    myType(int input);
    myType(double input);

    //myType & operator = (const myType & b);
    const myType & operator += (const myType & b);
    const myType & operator -= (const myType & b);
    const myType & operator *= (const myType & b);
    const myType & operator *= (int num);
    const myType & operator /= (const myType &b);
    const myType & operator %= (const myType &b);

    myType & operator++(int);
    myType & operator--(int);


    std::string toString()const;
    void print(std::ostream & out)const;
    void fromString(std::string input);
    void shrinkFract(int n);
    void roundOff(int n);
    void makeWhole();

    int getIntDigit(int pos)const;
    int getFractDigit(int pos)const;
    int getIntDigits()const;
    int getFractDigits() const;
    bool areEqual(const myType & b) const;
    bool lessThan(const myType & b) const;

    private:

    void addIntDigit(int digit);
    void addFractDigit(int digit);
    void changeFractDigit(int digit, int pos);
    void changeIntDigit(int digit, int pos);
    void standardize();

    bool isNegative;
    std::vector<char> intgs;
    std::vector<char> fracts;
    int intDigits;
    int fractDigits;


};


myType operator +(const myType & a, const myType & b);
myType operator -(const myType & a, const myType & b);
myType operator *(const myType & a, const myType & b);
myType operator *(const myType &a, int num);
myType operator *(const myType & a, const myType & b);
myType operator /(const myType & a, const myType & b);
myType operator %(const myType & a, const myType & b);

std::ostream & operator <<(std::ostream & out, const myType & a);
std::istream & operator >> (std::istream & in, myType & a);


bool operator == (const myType & a, const myType & b);
bool operator != (const myType & a, const myType & b);
bool operator < (const myType & a, const myType & b);
bool operator <= (const myType & a, const myType & b);
bool operator > (const myType & a, const myType & b);
bool operator >= (const myType & a, const myType & b);

myType myFactorial(int n);
myType mySqrt(double d);
myType mySqrt(myType num);
myType myPow(double d, int p);
myType myPow(myType num, int p);
myType myPi(int n);
myType myLog(double d);
myType myAvg(myType *data, int n);
myType mySin(double d);
myType myPrime(myType n);
int myFind(myType *data, int n, myType value);
void mySort(myType *data, int n);
bool isPrime(myType n);

