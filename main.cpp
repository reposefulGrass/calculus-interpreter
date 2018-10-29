// Corey Wingo (csw170030)
// 10/15/2017
// Project 4 -- Preventing a Paradox
// CS 2336 Jason Smith

#include "expression.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

double evalIntegral (Expression expr, int a, int b);

int main () {
	ifstream infile ("integrals.txt");
	ofstream outfile ("answers.txt");
	
	if (!infile || !outfile) {
		cout << "Could not open integrals.txt or answers.txt" << endl;
		return 1;
	}	

	bool definite;
	int a = 0, b = 0;
	
	string line;
	getline(infile, line);

	while (infile) {
		// Determine if definite or indefinite integral
		if (line.at(0) == '|') {
			definite = false;	

			line.replace(0, 1, "");	
		} else {
			definite = true;
			stringstream river (line);

			river >> a;
			river.ignore();
			river >> b;

			// replace the a|b -> "".
			getline(river, line);
		}

		// Get rid of the trailing " dx".
		int length = (int) line.length();
		line.replace(length-3, length-1, "");
		
		// Print and/or evaluate expression
		Expression expr (line);
		expr.integrateExpr();
		double evaluated = evalIntegral(expr, a, b);

		if (!definite) {
			outfile << expr << " + C" << endl;
		} else {
			outfile << fixed << showpoint << setprecision(3)
					<< expr << ", " << a << "|" << b << " = " << evaluated << endl;
		}

		getline(infile, line);	
	}

	infile.close();
	outfile.close();
}

double evalIntegral (Expression expr, int a, int b) {
	int multiple = (a > b)? -1 : 1;
	return (expr.eval(b) - expr.eval(a)) * multiple;
}
