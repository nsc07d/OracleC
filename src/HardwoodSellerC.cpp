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

	//First line placeholder strings
	string firstLine, buyer, address, date, temp;
	int count = 0;

	//Open file and get first line for parsing
	ifstream inFile;
	inFile.open(inputFilePath);
	getline(inFile, firstLine);

	//Function to parse just the first line
	buyerInfo(firstLine, count, buyer, address, date, temp);
}

/*
 * Method to compute the deliveryTime
 */
double deliveryTime() {
	double deliveryETA = 0.0;
	return deliveryETA;
}

/*
* Simply parses the top line. Known amount of tokens makes this easy
*/
void buyerInfo(string& x, int y, string& buyer, string& address, string& date, string& temp)
{
	//Parses the entire line
	for (unsigned int i = 0; i < x.length(); i++)
	{
		//If you reach a ; and count == 0 you've reached the name of the buyer
		if (x[i] == ';' && y == 0)
		{
			buyer = temp;
			temp = "";
			y++;
		}
		//Otherwise if you reach a ; and count == 1 you've reached the end of the address
		else if (x[i] == ';' && y == 1)
		{
			address = temp;
			temp = "";
			y++;
		}
		//Otherwise you just append line[i] to a string until it reaches a ;
		else
			temp += x[i];
	}
	//Setting the remainder of the temp string to date since that's what's left over
	date = temp;

	//This resets temp and x for parsing the second line
	temp = "";
	x = "";


}
