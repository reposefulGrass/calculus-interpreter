// Corey Wingo (csw170030)
// 10/15/2017
// Project 4 -- Preventing a Paradox
// CS 2336 Jason Smith

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "binaryTree.h"
#include "term.h"
#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
#include <cctype>

class Expression {
private:
	void parse (std::string expr);
	void integrateTerms (Node<Term>* term); 
	double evalNode (Node<Term>* current, double x); 

public:
	BinaryTree<Term> expr;

	Expression (std::string expr);

	double eval (double x);
	void integrateExpr ();
	void setFirstTerm (Node<Term>* current);

	void printInorder (std::ostream& out, Node<Term>* current, int count);
	friend std::ostream& operator << (std::ostream& out, Expression& expr);
};

// parse - parse the expression for terms, inserting each one into `expr`.
void Expression::parse (std::string exprStr) {
	std::regex searchFor ("([-+]*[0-9]*){1}x{0,1}(\\^([-+]*[0-9]*)){0,1}");	
	std::sregex_iterator it (exprStr.begin(), exprStr.end(), searchFor);
	std::sregex_iterator it_end;	
	
	while (it != it_end) {
		std::string termStr = it->str();

		// Regex is giving an empty string at the end:
		if (!termStr.empty()) {
			Term term (termStr);

			// Simply Terms if their powers are the same.
			Node<Term>* found = expr.search(term);
			if (found) {
				found->data = found->data + term;
			} else {
				expr.insert(term);
			}
		}

		++it;
	}

	setFirstTerm(expr.root);
}

Expression::Expression (std::string expr) {
	expr.erase(remove_if(expr.begin(), expr.end(), isspace), expr.end());
	parse(expr);
}

// Recursive eval method for `eval()`.
double Expression::evalNode (Node<Term>* current, double x) {
	if (current == nullptr) {
		return 0.0;
	}
	return (current->data).eval(x)
		   	+ evalNode(current->leftLink, x)
			+ evalNode(current->rightLink, x);
}

// Evaluate the expression at `x`.
double Expression::eval (double x) {
	return evalNode(expr.root, x); 
}

// Recursive method for `integrateExpr()`.
void Expression::integrateTerms (Node<Term>* term) {
	if (term != nullptr) {
		integrateTerms(term->leftLink);
		(term->data).integrate();
		integrateTerms(term->rightLink);
	}
}

// Integrate every term in the expression.
void Expression::integrateExpr () {
	integrateTerms(expr.root);	
}

// Find and set the first term of the expression.
void Expression::setFirstTerm (Node<Term>* current) {
	if (current == nullptr) {
		return;
	}

	while (current->leftLink != nullptr) {
		current = current->leftLink;
	}

	(current->data).setFirst();
}

// Print the expression in order of power (greteat to least).
void Expression::printInorder (std::ostream& out, Node<Term>* current, int count) {
	if (current != nullptr) {
		printInorder(out, current->leftLink, count);

		out << current->data;
		
		printInorder(out, current->rightLink, count);
	}
}

std::ostream& operator << (std::ostream& out, Expression& expression) {
	expression.printInorder(out, expression.expr.root, 0);

	return out;
}

#endif
