// Corey Wingo (csw170030)
// 10/15/2017
// Project 4 -- Preventing a Paradox
// CS 2336 Jason Smith

/* Term - A class emulating a term of an expression, comprised of
 * 		coefficient and power. 
 *
 * Author - Leigh (csw170030)
 * Date   - 10/02/2017
*/

#ifndef TERM_H
#define TERM_H

#include "fraction.h"
#include <sstream>
#include <regex>
#include <string>
#include <fstream>
#include <cmath>

class Term {
private:
	void parse (std::string term);

public:
	Fraction coeff;
	int power;
	bool isFirst = false;

	Term ();
	Term (const int&      coeff, const int& power);
	Term (const Fraction& coeff, const int& power); 
	Term (std::string term);

	double eval (double var) const;
	void integrate ();

	void setFirst ();

	Term operator +  (const Term& other) const;
	Term operator /  (const Term& other) const;
	Term operator =  (const Term& other);
	bool operator == (const Term& other) const;
	bool operator <  (const Term& other) const;
	bool operator >  (const Term& other) const;
	friend std::ostream& operator << (std::ostream& out, Term& term);
};

/* Parse - parse a string for its coefficient and power.
*/
void Term::parse (std::string term) {
	std::stringstream river (term);

	// Get the coefficient
	if (river.peek() == '-' || river.peek() == '+') {
		char sign = (char) river.get();
		int number;

		if (isdigit(river.peek())) {
			river >> number;	
		} else {
			number = 1;
		}	

		if (sign == '-') {
			number = -number;
		}

		Fraction coeff2 (number);
		coeff = coeff2;
	} else if (isdigit(river.peek())) {
		int number;

		river >> number;	

		Fraction coeff2 (number);
		coeff = coeff2;
	} else if (river.peek() == 'x') {
		Fraction coeff2 (1);
		coeff = coeff2; 
	}

	// parse for the power
	std::regex searchFor ("\\^[+-]?[0-9]+");
	std::sregex_iterator it (term.begin(), term.end(), searchFor);
	std::sregex_iterator it_end;

	// No power found (^digit)
	if (it == it_end) {
		// if `term` doesn't contain and "x", power = 0;
		// if `term` does, power = 1
		std::size_t found = term.find("x");
		if (found == std::string::npos) {
			power = 0;
		} else {
			power = 1;
		}
	} else {
		std::string str = it->str();
		std::stringstream lake (str);

		lake.ignore(); // skip ^
		lake >> power;
	}
}

Term::Term () {
	Fraction fraction;
	this->coeff = fraction;
	this->power = 0;
}

Term::Term (const int& coeff, const int& power) {
	Fraction fraction (coeff);
	this->coeff = fraction;
	this->power = power;
}

Term::Term (const Fraction& coeff, const int& power) {
	this->coeff = coeff; this->power = power;	
}

Term::Term (std::string term) {
	// Incase parse does not parse correctly or `term` is an empty string.
	Fraction fraction;
	this->coeff = fraction;
	this->power = 0;

	parse(term);
}

// Evaluate the term at x (var)
double Term::eval (double var) const {
	double var2 = pow(var, power);
	var2 *= (double(coeff.numer) / coeff.denom);

	return var2;	
}

// Integrate the term
void Term::integrate () {
	power++;
	Fraction divisor (power);
	coeff = coeff / divisor;
}

// Set the term to be the first term of the expression
void Term::setFirst () {
	isFirst = true;
}

Term Term::operator + (const Term& other) const {
	Term term;

	if (this->power == other.power) {
		term.coeff = this->coeff + other.coeff;
		term.power = this->power;
	}

	return term;
}

Term Term::operator / (const Term& other) const {
	Term term;

	term.coeff = this->coeff / other.coeff;
	term.power = this->power - other.power;	

	return term;
}

Term Term::operator = (const Term& other) {
	this->coeff = other.coeff;
	this->power = other.power;

	return *this;
} 

bool Term::operator == (const Term& other) const {
	return (this->power == other.power);
}

bool Term::operator < (const Term& other) const {
	return (this->power > other.power);
}

bool Term::operator > (const Term& other) const {
	return (this->power < other.power);
}

std::ostream& operator << (std::ostream& out, Term& term) {
	Fraction one  (1);
	Fraction negOne (-1);
	Fraction zero (0);

	// Do no print zero or undefined
	if (term.coeff == zero || term.coeff.denom == 0) {
		return out;
	}

	// print coefficient
	// If the fraction is an integer
	if (!(term.coeff == one) && !(term.coeff == negOne)) {
		// Print sign based on if the term is the first term of the expression.
		if (term.coeff.isNegative()) {
			out << ((term.isFirst)? "-" : " - ") << term.coeff;
		} else {
			out << ((term.isFirst)? "" : " + ") << term.coeff;
		}
	} else {
		if (term.coeff.isNegative()) {
			out << ((term.isFirst)? "-" : " - ");
		} else {
			out << ((term.isFirst)? "" : " + ");
		}
	}

	// print the x^power part of the term.
	if (term.power == 0) {
	} else if (term.power == 1) {
		out << "x";	
	} else {
		out << "x^" << term.power;
	}

	return out;
}

#endif
