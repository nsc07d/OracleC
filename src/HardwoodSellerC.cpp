//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Nate Craver
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
	
	//Declaring what is needed to parse second line
	deque<WoodItem> purorder;
	deque<string> wood;
	deque<int> allWood;
	string typeOfWood;
	string itemp;

	//Sending that information in to parseOrder();
	parseOrder(firstLine, purorder, wood, allWood, typeOfWood, itemp);
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

/*
* This function parses the second line. It reads a woodtype and pushes
* its WoodItem into a WoodItem deque. It then reads the next quantity
* and pushes that into an adjacent deque.
*/
void parseOrder(string &line, deque<WoodItem> &purorder, deque<string> &wood, deque<int> &allWood,
	string &typeOfWood, string &itemp)
{
	//Creating WoodType types~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	string cherry = "Cherry", curly_maple = "Curly Maple",
		genuine_mahogany = "Genuine Mahogany", wenge = "Wenge",
		white_oak = "White Oak", sawdust = "Sawdust", fileName;

	WoodItem Cherry(cherry, 2.5, 5.95), Curly_Maple(curly_maple, 1.5, 6.00),
		Genuine_Mahogany(genuine_mahogany, 3, 9.60), Wenge(wenge, 5, 22.35),
		White_Oak(white_oak, 2.3, 6.70), Sawdust(sawdust, 1, 1.5);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == ':')
		{
			/*
				We now have the wood type. we simply match the type with its
				corresponding WoodItem and push that WoodItem into a deque
			*/
			if (typeOfWood == "Cherry")
				purorder.push_front(Cherry);
			else if (typeOfWood == "Curly Maple")
				purorder.push_front(Curly_Maple);
			else if (typeOfWood == "Genuine Mahogany")
				purorder.push_front(Genuine_Mahogany);
			else if (typeOfWood == "Wenge")
				purorder.push_front(Wenge);
			else if (typeOfWood == "White Oak")
				purorder.push_front(White_Oak);
			else if (typeOfWood == "Sawdust")
				purorder.push_front(Sawdust);
			else
			{
				cout << "Not a valid purchase order, please reenter file." << endl;
				break;
			}
			typeOfWood = "";
		}
		else if (line[i] == ';')
		{
			/*
				We now have an amount of WoodItem. We convert the string to its
				int equivalent and push it into a deque.
			*/
			int holder = stoi(itemp);
			allWood.push_front(holder);
			itemp = "";
		}
		else if (isdigit(line[i]))
			itemp += line[i];
		else
			typeOfWood += line[i];
	}
	int holder = stoi(itemp);
	allWood.push_front(holder);
}
