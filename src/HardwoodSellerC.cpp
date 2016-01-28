//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
//============================================================================

#include <iostream>
using namespace std;

int main() {
	string fileName;
		
	cout << "Please enter in Purchase Order file name: ";
	cin >> fileName;

	//Main simply calls readInputFile which does all the work
	readInputFile(fileName);

	return 0;
}

/*
 * Method to read the input file
 */
void readInputFile(string inputFilePath) {

}

/*
 * Method to compute the deliveryTime
 */
double deliveryTime() {
	double deliveryETA = 0.0;
	return deliveryETA;
}
