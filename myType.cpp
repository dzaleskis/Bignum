#include "header.h"

#define BASE 10

using namespace std;



myType::myType(string input){// default constructor for user-defined string

    fromString(input);

}

myType::myType(){//default empty constructor

    isNegative = false;
    fractDigits = 0;
    intDigits = 0;
}

myType::myType(int input){

    string s = to_string(input);
    s += ".0";
    fromString(s);

}

myType::myType(double input){

    string s = to_string(input);

    fromString(s);


}

const myType & myType::operator +=(const myType & b){//adds two myTypes

    if(isNegative != b.isNegative){

        myType c = b;

        if(c.isNegative==true){
            c.isNegative = false;
        }else{
            c.isNegative = true;
        }


        *this -= c;
        return *this;
    }

    int fractsDistance = max(getFractDigits(), b.getFractDigits());
    int intsDistance = max(getIntDigits(), b.getIntDigits());

    if(fractsDistance>getFractDigits()){

        fracts.resize(fractsDistance,'0');
        fractDigits = fractsDistance;

    }

    int carry=0, sum;

    for(int i = fractsDistance-1;i>=0;i--){

        sum = getFractDigit(i)+ b.getFractDigit(i) + carry;
        carry = sum/BASE;
        sum %= BASE;
        changeFractDigit(sum, i);
    }

    for(int i = 0;i<intsDistance;i++){

        sum = getIntDigit(i)+ b.getIntDigit(i) + carry;
        carry = sum/BASE;
        sum %= BASE;

        if(i<getIntDigits()){
        changeIntDigit(sum,i);
        }else{
        addIntDigit(sum);
        }
    }

    if(carry!=0){
        addIntDigit(carry);

    }



    return *this;

}

const myType & myType::operator -= (const myType & b){// subtracts of two myTypes

     if(isNegative != b.isNegative){

        myType c = b;

        if(c.isNegative==true){
            c.isNegative = false;
        }else{
            c.isNegative = true;
        }


        *this += c;
        return *this;
 }

    if((isNegative==false && ((*this) < b))||(isNegative==true && (*this) > b)){


        *this = b - *this;

        if(isNegative==true){
            isNegative = false;
        }else {
            isNegative = true;
        }
        return *this;
    }


    int fractsDistance = max(getFractDigits(), b.getFractDigits());
    int intsDistance = max(getIntDigits(), b.getIntDigits());
    if(fractsDistance>getFractDigits()){

        fracts.resize(fractsDistance,'0');
        fractDigits = fractsDistance;
    }

    int borrow=0, diff;

    for(int i = fractsDistance-1;i>=0;i--){
        diff = 10 + getFractDigit(i)- b.getFractDigit(i) - borrow;

        if(diff<10){
            borrow = 1;
        }else{
            borrow = 0;
        }

        diff %= BASE;
        changeFractDigit(diff, i);
    }

    for(int i = 0;i<intsDistance;i++){

        diff = 10 + getIntDigit(i)- b.getIntDigit(i) - borrow;

        if(diff<10){
            borrow = 1;
        }else{
            borrow = 0;
        }

        diff %= BASE;
        if(i<getIntDigits()){
        changeIntDigit(diff,i);
        }else{
        addIntDigit(diff);
        }
    }




    standardize();
    return *this;

}



const myType & myType::operator *= (const myType & b){//multiplies myType by another myType

    myType c, sum;
    
    int distance = b.getFractDigits();
    if(distance > 105){
        distance = 105;
    }
    
    for(int i = distance-1; i >=0; i--){
        c.addFractDigit(getIntDigit(i));
    }

    for(int i = 0; i < getFractDigits(); i++){

        c.addFractDigit(getFractDigit(i));
    }

    for(int i = distance; i < getIntDigits(); i++){

        c.addIntDigit(getIntDigit(i));
    }
    
    c.shrinkFract(210);

    for(int i = distance-1; i>=0; i--){
        
        sum += (c * b.getFractDigit(i));
        c *=BASE;
    }

    for(int i =0; i < b.getIntDigits(); i++){

        sum += (c * b.getIntDigit(i));

        c *=BASE;


    }
    
    sum.shrinkFract(105);
    sum.standardize();

    if(isNegative!=b.isNegative){

        sum.isNegative = true;

    }



    *this = sum;

    return *this;

}

const myType & myType::operator *= (int num){ //multiplies myType by an int



    if(num==0){
        myType c(0);
        *this = c;
        return *this;

    }

    if(num==1){

        return *this;
    }

    if(num>BASE || num < 0){

        return *this;
    }

    int product = 0, carry = 0;

    for(int i = getFractDigits()-1; i>=0; i--){

        product = getFractDigit(i)*num + carry;

        carry = product/BASE;

        product %= BASE;

        changeFractDigit(product,i);

    }

    for(int i = 0; i < getIntDigits(); i++){

        product = getIntDigit(i)*num + carry;

        carry = product/BASE;

        product %= BASE;

        changeIntDigit(product,i);

    }

    while(carry!=0){

        addIntDigit(carry);
        carry /= BASE;
    }

    return *this;


}

const myType & myType::operator %= (const myType & b){// performs modulo operation on myType by another myType


    while(*this > b){

        *this -= b;
    }

    return *this;

}

const myType & myType::operator /= (const myType &b ){// performs division of myType by another myType

    myType result("0.0");
    myType rightValue = b;
    myType zero("0.0"), one("1.0");
    bool needToChangeSign = false;

    try{
    if(rightValue==zero){
        throw "error: division by zero";

    }
    }
    catch(const char* msg){
        cerr << msg << endl;
        return *this;
    }

    if(rightValue==one){//division by one
        return *this;
    }

    if(isNegative!=rightValue.isNegative){

        needToChangeSign = true;

        if(isNegative==true){
            isNegative = false;
        }else{
            rightValue.isNegative = false;
        }

    }

    while(*this>rightValue){

        *this -= rightValue;
        result++;

    }


    for(int i = 0; i < 105; i++){


        *this *=10;
        int j = 0;

        while(*this>rightValue){
            j++;
            *this -= rightValue;

        }

        if(i==0){
            result.changeFractDigit(j,i);


        }else{
            result.addFractDigit(j);
        }

    standardize();

    if(*this==zero){
        break;
    }


    }
    if(needToChangeSign == true){

        result.isNegative = true;
    }

    *this = result;

    return *this;

}



myType operator + (const myType& a, const myType& b) {//returns result of addition of two myTypes

    myType result = a;
    result += b;
    return result;

}

myType operator -(const myType & a, const myType & b){//returns result of subtraction of two myTypes
    myType result = a;
    result -= b;
    return result;

}

myType operator *(const myType & a, const myType & b){//returns result of multiplication of two myTypes

    myType result = a;
    result *= b;
    return result;
}

myType operator *(const myType & a, int num){//returns result of multiplication of a myType by an int

    myType result = a;
    result *= num;
    return result;


}

myType operator %(const myType & a, const myType & b){//returns result of modulo operation on a myType by another myType

    myType result = a;
    result %= b;
    return result;


}

myType operator /(const myType & a, const myType & b){//returns result of division of a myType by another myType

    myType result = a;
    result /= b;
    return result;


}

myType & myType::operator ++(int){//positive increment operator


    myType c("1.0");

    *this += c;

    return *this;
}

myType & myType::operator --(int){//negative increment operator

   myType c("-1.0");

    *this += c;

    return *this;
}


bool operator < (const myType & a, const myType & b){

    return a.lessThan(b);

}

bool operator <= (const myType & a, const myType & b){

    if(a<b){
        return true;

    }

    if(a==b){
        return true;
    }

    return false;
}

bool operator > (const myType & a, const myType & b){

    return !(a.lessThan(b));

}

bool operator >= (const myType & a, const myType & b){

    if(a>b){
        return true;

    }

    if(a==b){
        return true;
    }

    return false;

}

bool operator != (const myType & a, const myType & b){
    return !(a.areEqual(b));

}

bool operator == (const myType & a, const myType &b){

    return (a.areEqual(b));

}

ostream & operator <<(ostream & out, const myType & a){//prints object to console

    a.print(out);
    return out;

}

istream & operator >> (istream & in, myType & a){//gets object from console

    string input;
    cin >> input;

    a.fromString(input);
    return in;

}

void myType::print(ostream & out)const{//helper for << operator

 out << toString();

}

string myType::toString()const{//returns object as string

    string output="";

    if(isNegative==true){
        output = "-";
        }

    for(int i = intDigits-1; i>=0;i--){
        output += intgs[i];
    }
    output += ".";

    for(int i = 0; i<fractDigits ;i++){
        output += fracts[i];
    }




    return output;
}


void myType::fromString(string input){//for string input

    int strlen=0;
    int dotPos=0;
    bool correct=true;
    int dotCounter=0;

    isNegative = false;
    fractDigits = 0;
    intDigits = 0;
    intgs.clear();
    fracts.clear();

    try{

    for(strlen=0;input[strlen]!='\0';strlen++){

        if(input[strlen]>='0'&&input[strlen]<='9'){


        }else if(input[strlen]=='.'&&strlen>0){
            dotCounter++;
            dotPos = strlen+1;

        }else if(input[strlen]=='-'){

            isNegative = true;
            if(strlen>0){
                    correct=false;
            }

        }else{

            correct=false;

            }
        }

        if(!correct || dotCounter!=1){

            throw "Error: incorrect input";
        }



    for(int i=dotPos;i<strlen;i++){
        fractDigits++;
        fracts.push_back(input[i]);
    }

     for(int i=dotPos-2;i>=0+(1*isNegative);i--){
        intDigits++;
        intgs.push_back(input[i]);
    }

    standardize();

    }

    catch (const char* msg) {
     cerr << msg << endl;
     return;
   }

}

void myType::standardize(){//gets rid of leading/trailing zeroes

    int firstNum, lastNum;

    for(int i=getIntDigits()-1;i>0;i--){

        firstNum = getIntDigit(i);

        if(firstNum==0){
            intgs.pop_back();
            intDigits--;
        }
        if(firstNum!=0){
            break;
        }

    }

    for(int i=getFractDigits()-1;i>0;i--){


        lastNum = getFractDigit(i);

        if(lastNum==0){

            fracts.pop_back();
            fractDigits--;
        }
        if(lastNum!=0){
            break;
        }

    }

    if(getIntDigits()==0){

        intDigits++;
        intgs.push_back('0');

    }

    if(getFractDigits()==0){

        fractDigits++;
        fracts.push_back('0');

    }



}



bool myType::lessThan(const myType & b) const{

     if (isNegative != b.isNegative){
        return isNegative;
    }

    if(isNegative==false){

    if (getIntDigits() > b.getIntDigits()){

    return false;

    }
    if(getIntDigits() < b.getIntDigits()){

    return true;
    }

    if(getIntDigits()==b.getIntDigits()){

    for(int i = getIntDigits()-1;i>(-1);i--){

        if(getIntDigit(i)<b.getIntDigit(i)){

            return true;
        }
        if(getIntDigit(i)>b.getIntDigit(i)){

            return false;

        }

    }

    for(int i = 0; i < getFractDigits(); i++){

        if(getFractDigit(i)<b.getFractDigit(i)){
            return true;
        }

        if(getFractDigit(i)>b.getFractDigit(i)){
            return false;
        }


        }
        if(getFractDigits() < b.getFractDigits()){
        return true;
    }
    }

    return false;

    }else{

        if (getIntDigits() < b.getIntDigits()){
    return false;

    }else if(getIntDigits() > b.getIntDigits()){
    return true;
    }

    for(int i = getIntDigits()-1;i>=0;i--){

        if(getIntDigit(i)>b.getIntDigit(i)){
            return true;
        }

        if(getIntDigit(i)<b.getIntDigit(i)){

            return false;

        }

    }

     for(int i = 0; i < getFractDigits(); i++){

        if(getFractDigit(i) > b.getFractDigit(i)){
            return true;
        }
         if(getFractDigit(i) < b.getFractDigit(i)){
            return false;
        }


    }
    if(getFractDigits()>b.getFractDigits()){
        return true;
    }

    return false;


    }



}


bool myType::areEqual(const myType &b) const{

    if(isNegative != b.isNegative){
        return false;
    }

    if(getIntDigits() != b.getIntDigits()){
        return false;
    }

    if(getFractDigits() != b.getFractDigits()){
        return false;
    }

    if(toString()==b.toString()){

        return true;
    }

    return false;


}

int myType::getFractDigit(int pos) const{//returns desired fractional digit of myType as int

    int digit;
    if(pos<fractDigits){

        digit = fracts[pos]-'0';
        return digit;
    }else{
        return 0;
    }

}

int myType::getIntDigit(int pos) const{//returns desired integer digit of myType as int

    int digit;
    if(pos<intDigits){

        digit = intgs[pos]-'0';
        return digit;
    }else{
        return 0;
    }

}

int myType::getIntDigits() const {//returns number of digits in integer part
    int digits = intDigits;
    return digits;
}

int myType::getFractDigits() const{//returns number of digits in fractional part
    int digits = fractDigits;
    return digits;
}

void myType::addIntDigit(int digit){//adds new digit to integer part of myType

    intgs.push_back((char)digit+48);
    intDigits++;
}

void myType::addFractDigit(int digit){//adds new digit to fraction part of myType

    fracts.push_back((char)digit+48);
    fractDigits++;
}

void myType::changeIntDigit(int digit, int pos){//changes integer-part digit at specified position

    if(pos<getIntDigits()){
        intgs[pos] = (char)digit+48;
    }
}

void myType::changeFractDigit(int digit, int pos){//changes fractional digit at specified position

    if(pos<getFractDigits()){
        fracts[pos] = (char)digit+48;
    }
}


void myType::roundOff(int n){

    int fractionSize = getFractDigits();

    if(fractionSize > n+1){

    shrinkFract(n + 1);
    int lastnum = getFractDigit(n);

    if(lastnum == 9){
    int following = 0;
    int counter = 0;
    for(int i = n-1; i >= 0; i--){

        following = getFractDigit(i);

        if(following != lastnum){
            break;
        }else{
            counter++;
        }

    }
    shrinkFract(n + 1 - counter);
    
    }

    fractionSize = getFractDigits();

    lastnum = getFractDigit(fractionSize - 1);

    if(fractionSize > 1){

    fractionSize--;
    shrinkFract(fractionSize);

     if(lastnum >= 5){

        if(getFractDigit(fractionSize - 1) == 9){

        while(getFractDigit(fractionSize - 1) == 9){
        changeFractDigit( getFractDigit(fractionSize - 2) + 1, fractionSize - 2);
        fractionSize--;
        shrinkFract(fractionSize);
        }


        }else{
        changeFractDigit( getFractDigit(fractionSize - 1) + 1, fractionSize - 1);
        }


    }

    }else{
        changeFractDigit(0, 0);
        myType temp(1);
        *this += temp;

    }



    }else{
        return;
    }

    standardize();

}


void myType::makeWhole(){

    shrinkFract(1);
    changeFractDigit(0, 0);

}


