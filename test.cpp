
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string.h>


// other includes and definitions

#include "header.h"

using namespace std;

// define your datatype here


// convert from string to myType
myType convert(string s){

	myType m;
	m.fromString(s);
	return m;
}


// convert from myType to string
string toStr(myType m){

	return m.toString();

}

void myType::shrinkFract(int n){
    
    if(fractDigits > n){
        fracts.resize(n);
        fractDigits = n;
    }

}

myType myFactorial(int n){

  myType num(n);
  myType one("1.0");

    try{
        if(n < 0){
            throw "only positive numbers permitted";
        }

    }
     catch(const char* msg){
    cerr << msg << endl;
    return 0;
  }

  if(n == 0 || n == 1){
    return one;
  }



  for(myType i = num - one; i > one; i--){

    num *= i;


  }

 return num;

}



myType myPrime(myType n){
    
    myType zero(0), two(2);
    n.makeWhole();
try{
    if(n < zero){
        throw "number is too small!";
    }
}
catch(const char* msg){
    cerr << msg << endl;
    return 0;
}
    if(n < two){
        return two;
    }
    if(n % two == zero){
        n--;
    }
    bool prime = false;

    while(!prime){
        n += 2;
        prime = isPrime(n);
    }

    return n;
    
}

bool isPrime(myType n){

    myType zero(0), two(2), three(3);

    if(n % two == zero){
        return false;
    }
    if(n % three == zero){
        return false;
    }
    if(n == three){
        return true;
    }
    
    myType num_sqrt = mySqrt(n);
    num_sqrt.makeWhole();
    
    for(myType i = three + two; i <= num_sqrt; i += two){

        if (n % i == zero){
            return false;
        }
    }

    return true;
}

myType mySqrt(double d){

  myType num(d);
  myType one(1);

  if(d == 0){
    return 0;
  }

  try{
    if(d < 0){
        throw "only positive numbers permitted";
    }
  }
  catch(const char* msg){
    cerr << msg << endl;
    return 0;
  }

  myType guess("2.0");
  myType zero("0.0");
  myType half("0.5");

  int guess_pow;
  //if power of digit is multiple of 2
  if(num.getIntDigits()%2==1){
    guess_pow = (num.getIntDigits()-1)/2;

  }else{

    guess *= 3;
    guess_pow = (num.getIntDigits()-2)/2;

  }

  for(int i = 0; i < guess_pow; i++){

    guess *= 10;
  }


    int i = 0;
    
    if(num > one){
        
        for(i = 0; i < 8; i++){
            guess = half * (guess + (num/guess));
        }
        
    }else{

      while( 1){
        guess = half * (guess + (num/guess));
        i++;
        if(i > 10 && guess*guess == num){
            break;
        }
        if(i==20)
            break;
      }
    }
  guess.roundOff(100 - guess.getIntDigits());
  return guess;

}

myType mySqrt(myType num){

  myType guess("2.0");
  myType zero("0.0");
  myType half("0.5");
  myType one(1);

  int guess_pow;
  //if power of digit is multiple of 2
  if(num.getIntDigits()%2==1){
    guess_pow = (num.getIntDigits()-1)/2;

  }else{

    guess *= 3;
    guess_pow = (num.getIntDigits()-2)/2;

  }

  for(int i = 0; i < guess_pow; i++){

    guess *= 10;
  }


   int i = 0;
    
    if(num > one){
        
        for(i = 0; i < 8; i++){
            guess = half * (guess + (num/guess));
        }
        
    }else{

      while( 1){
        guess = half * (guess + (num/guess));
        i++;
        if(i > 10 && guess*guess == num){
            break;
        }
        if(i==20)
            break;
      }
    }
    guess.roundOff(99);
  return guess;

}

myType myPow(double d, int p){

    try{
        if(p < 0){
            throw "only positive powers permitted";
        }
    }

  catch(const char* msg){
    cerr << msg << endl;
    return 0;
  }
  
  if(p == 0){
      return 1;
  }

    myType num(d);
    myType copy_num = num;


    for(int i = 1; i < p; i++){

        num *= copy_num;
    }

    return num;

}

myType myPow(myType num, int p){

    myType copy_num = num;

    for(int i = 1; i < p; i++){

        num *= copy_num;
    }

    return num;

}

myType myPi(int n){

    if(n == 0){
        return 3;
    }
    if(n > 99){
        n = 99;
    }

     try{
    if(n < 0){
        throw "n must be positive";
    }
  }

  catch(const char* msg){
    cerr << msg << endl;
    return 0;
  }
    myType pi("3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798");
    pi.roundOff(n);

    return pi;


}


myType myLog(double d){

    myType num(d);
    myType zero(0);

    try{
        if(d < 0){
            throw "only positive numbers permitted";
        }
    }

  catch(const char* msg){
    cerr << msg << endl;
    return 0;
  }

    myType ln10("2.30258509299404568401799145468436420760110148862877297603332790096757260967735248023599720508959829834");
    myType ln2("0.693147180559945309417232121458176568075500134360255254120680009493393621969694715605863326996418687542");
    if(d == 10){
        ln10.roundOff(99);
        return ln10;
    }
    if(d == 2){
        ln2.roundOff(99);
        return ln2;
    }
    if(d == 1){
        return 0;
    }
    int exponent = num.getIntDigits();
    if(exponent>0){
    num /= myPow(10, exponent);
    }
    
    int doubled = 0;
    myType two(2), one(1);
    
    while((one/num) >= two){
        num *= 2;
        doubled++;
    }

    myType ln(0);
    myType dividend(1);
    myType divisor(1);
    myType constant = (num - 1)/(num + 1);
    myType constantpow2 = myPow(constant, 2);
    myType currentpow = constant;
    
    for(int i = 1; i < 210; i+= 2){
        ln += (dividend/divisor) * currentpow;
        divisor += 2;
        currentpow *= constantpow2;
        
    }


    ln *= 2;

    for(int i = 0; i < exponent; i++){

        ln += ln10;

    }
    for(int i = 0; i < doubled; i++){
        ln -= ln2;
    }
    ln.roundOff(100 - ln.getIntDigits());
    return ln;
}




myType mySin(double d){//done

    myType num(d);
    myType pi = myPi(99);
    myType zero(0);
    myType one(1);
    myType two(2);
    bool changeSign1 = false, changeSign2 = false;
    

    if(num < zero){
        myType negative(-1);
        num *= negative;
        changeSign1 = true;
    }

    if( (num % (2*pi)) > pi){
        changeSign2 = true;
    }




    myType rads = num % ( pi);
    myType halfpi = (pi / two);

    if(rads > halfpi){

        myType temp = rads - halfpi;

        rads = halfpi - temp;

    }

    myType i(3);
    myType hundred(80);

    myType sin = rads;
    myType startPow = myPow(rads,3);
    myType startFactorial = myFactorial(3);
    myType radsPow2 = rads*rads;

    bool plus = false;

    for(i; i < hundred; i+= two){

        if(!plus){
        sin -= startPow / startFactorial;
        plus = true;
        }else{
        sin += startPow / startFactorial;
        plus = false;
        }
        startPow *= radsPow2;
        startFactorial *= ((i+1) * (i+2));
    }



     if(changeSign1){
        myType negative(-1);
        sin *= negative;
    }
    if(changeSign2){
        myType negative(-1);
        sin *= negative;
    }
    sin.roundOff(99);
    return sin;

}

int myFind(myType* data, int n, myType value){

    for(int i = 0; i < n; i++){

        if(value == data[i]){
            return i;
        }

    }
    return -1;

}

myType myAvg(myType* data, int n){

    myType sum(0);

    for(int i = 0; i < n; i++){

        sum += data[i];

    }
    myType divisor(n);
    sum /= divisor;
    sum.roundOff(99);
    return sum;


}


void mySort(myType* data, int n){

    int changes;

for(int j = 0; j < n; j++){

    changes = 0;

    for(int i = 0; i < n - j -1; i++){


        if(data[i] > data[i+1]){

            myType temp = data[i];

            data[i] = data[i+1];
            data[i+1] = temp;

            changes++;
        }


    }

    if(changes == 0){
            break;
        }


}

}


/* DO NOT MODIFY CODE BELOW */

int main(){
	while(1){
		int x = -1;
		cin >> x;
		if (x == 0)
			break;
		string s;
		double d;
		int n;
		myType *data = NULL;
		string output;
		switch(x){
			case 1:
				cin >> n;
				cout << (output = toStr(myFactorial(n))) << endl;
				break;
			case 2:
				cin >> s;
				cout << (output = toStr(myPrime(convert(s)))) << endl;
				break;
			case 3:
				int p;
				cin >> d >> p;
				cout << (output = toStr(myPow(d, p))) << endl;
				break;
			case 4:
				cin >> d;
				cout << (output = toStr(myLog(d))) << endl;
				break;
			case 5:
				cin >> d;
				cout << (output = toStr(mySin(d))) << endl;
				break;
			case 6:
				cin >> d;
				cout << (output = toStr(mySqrt(d))) << endl;
				break;
			case 7:
				cin >> n;
				cout << (output = toStr(myPi(n))) << endl;
				break;
			case 8:
				cin >> n;
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				cout << (output = toStr(myAvg(data, n))) << endl;
				delete [] data;
				break;
			case 9:
				cin >> n;
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				cin >> s;
				int f;
				cout << (f = myFind(data, n, convert(s))) << endl;
				delete [] data;
				break;
			case 10:
				cin >> n;
				data = new myType[n];
				for(int i = 0; i < n; ++i){
					string s;
					cin >> s;
					data[i] = convert(s);
				}
				mySort(data, n);
				for(int i = 0; i < n; ++i){
					cout << (output = toStr(data[i])) << endl;
				}
				delete [] data;
				break;
		}
	}
	return 0;
}
