//
//  main.cpp
//  birge-vieta
//
//  Created by manolo on 9/15/14.
//  Copyright (c) 2014 manolo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

//	If division is false returns the value of a polynomial evaluated in x
//	otherwise it returns the value of the polynomial divided by its derivative evaluated in x
double f(vector<double> polynomial, int degree, double x, bool division) {
	vector<double> derivative;
	double fx = polynomial[degree];
	for (int i=degree-1; i>=0; i--) {
		fx *= x;
		fx += polynomial[i];
		derivative.insert(derivative.begin(), fx);
	}
	if (division) {
		double fpx = polynomial[degree];
		for (int i=degree-1; i>=1; i--) {
			fpx *= x;
			fpx += derivative[i];
		}
		return fx/fpx;
	} else {
		return fx;
	}
}

int main() {
	char yn;
	double err, root;
	int degree, maxIterations;
	vector<double> polynomial;
	
	do {
		cout << "What is the polynomial's degree?\n";
		cin >> degree;
		
		for (int i=degree; i>=0; i--) {
			cout << "What is the coeficient for degree " << i << "?\n";
			double c;
			cin >> c;
			polynomial.insert(polynomial.begin(), c);
		}
		
		cout << "What value do you want to use for the margin of error?\n";
		cin >> err;
		cout << "What is the maximum number of iterations?\n";
		cin >> maxIterations;
		
		int roots = 1;
		while (degree>0) {
			int iter = maxIterations;
			root = rand()%100;
			do {
				root = root - f(polynomial, degree, root, 1);
			} while ((err<fabs(f(polynomial, degree, root, 0))) && (0<--iter));
			cout << "Root #" << roots++ << " is: " << root << endl;
			
			double y = polynomial[degree];
			for (int i=degree-1; i>=1; i--) {
				y *= root;
				y += polynomial[i];
				polynomial[i] = y;
			}
			polynomial.erase(polynomial.begin());
			degree--;
		}
		
		polynomial.clear();
		
		cout << "Do you want to solve another polynomial? y/n\n";
		cin >> yn;
	} while (yn == 'y');
}