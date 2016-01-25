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
	string cherry = "cherry", curly_maple = "curly maple",
	genuine_mahogany = "genuine mahogany", wenge = "wedge",
	white_oak = "white oak", sawdust = "sawdust", fileName;

	WoodItem Cherry(cherry, 2.5, 5.95), Curly_Maple(curly_maple, 1.5, 6.00),
		Genuine_Mahogany(genuine_mahogany, 3, 9.60), Wenge(wenge, 5, 22.35),
		White_Oak(white_oak, 2.3, 6.70), Sawdust(sawdust, 1, 1.5);
		
	
	cout
		<< "Please enter in Purchase Order file name: ";
	cin >> fileName;

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
