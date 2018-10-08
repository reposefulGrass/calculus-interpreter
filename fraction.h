// Corey Wingo (csw170030)
// 10/15/2017
// Project 4 -- Preventing a Paradox
// CS 2336 Jason Smith

/* Fraction - A fraction comprised of a numerator and denominator.
 * 
 * Author - Leigh (csw170030)
 * Date   - 10/27/2017
*/

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

class Fraction {
private:
	int gcd (int a, int b) const;

public:
	int numer; // numerator
	int denom; // denominator

	Fraction ();
	Fraction (const int& number);
	Fraction (const int& numer, const int& denom);

	bool isNegative ();
	bool isInteger ();

	void simplify ();

	Fraction  operator +  (const Fraction& other) const;
	Fraction  operator /  (const Fraction& other) const;
	Fraction& operator =  (const Fraction& other);
	bool      operator == (const Fraction& other);
	bool      operator <  (const Fraction& other);
	bool      operator >  (const Fraction& other); 
	friend std::ostream& operator << (std::ostream& out, Fraction f);
};

// Find the gcd of two integers
int Fraction::gcd (int a, int b) const {
	if (b != 0) {
		return gcd(b, a%b);
	} else {
		return a;
	}
}

Fraction::Fraction () {
	numer = 0;
	denom = 1;
}

Fraction::Fraction (const int& number) {
	this->numer = number;
	this->denom = 1;
}

Fraction::Fraction (const int& numer, const int& denom) {
	this->numer = numer;
	this->denom = denom;
}

/* isNegative - returns whether the fraction is negative or not.
*/
bool Fraction::isNegative () {
	return (((numer < 0) || (denom < 0)) && !(numer < 0 && denom < 0));
}

/* isInteger - returns whether the fraction is an integer when simplified.
*/
bool Fraction::isInteger () {
	simplify();
	return denom == 1 || denom == -1;
}

/* simplify - simplify the fraction as much as possible.
*/
void Fraction::simplify () {
	int greatestCommonDenom = gcd(numer, denom);

	numer = numer / greatestCommonDenom;
	denom = denom / greatestCommonDenom;
}

Fraction Fraction::operator + (const Fraction& other) const {
	int tempNumer = 0, tempDenom = 0;

	// find the LCM (tempDenom) 
	tempDenom = gcd(this->denom, other.denom);		
	int LCM = tempDenom = ((this->denom * other.denom) / tempDenom);	

	// find the new numerator  
	tempNumer = (this->numer * (LCM / this->denom)) + (other.numer * (LCM / other.denom));

	Fraction frac (tempNumer, tempDenom);
	frac.simplify();
	return frac;
}

Fraction Fraction::operator / (const Fraction& other) const {
	int tempNumer = 0, tempDenom = 0;
	
	tempNumer = this->numer * other.denom;	
	tempDenom = this->denom * other.numer;

	Fraction frac (tempNumer, tempDenom);
	frac.simplify();
	return frac;
}

Fraction& Fraction::operator = (const Fraction& other) {
	if (this == &other) {
		return *this;
	}

	this->numer = other.numer;
	this->denom = other.denom;

	return *this;
}

bool Fraction::operator == (const Fraction& other) {
	return (this->numer == other.numer) && (this->denom == other.denom);
}

std::ostream& operator << (std::ostream& out, Fraction f) {
	// Print only positive numbers, since the term class handles the 
	// printing of negative terms.
	if (f.denom == 1) {
		int numerator = (f.numer > 0)? f.numer : -f.numer;
		out << numerator;
	} else {
		int numerator = (f.numer > 0)? f.numer : -f.numer;
		int denominator = (f.denom > 0)? f.denom : -f.denom;
		out << "(" << numerator << "/" << denominator << ")";
	}

	return out;
}

bool Fraction::operator < (const Fraction& other) {
	double frac1 = this->numer / this->denom; 
	double frac2 = other.numer / other.denom;

	return frac1 < frac2;	
}

bool Fraction::operator > (const Fraction& other) {
	double frac1 = this->numer / this->denom; 
	double frac2 = other.numer / other.denom; 

	return frac1 > frac2; 
}

#endif
