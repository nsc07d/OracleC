//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Nathaniel Craver
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
//============================================================================

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "WoodItem.h"
using namespace std;


//Function Prototypes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double deliveryTime(const WoodItem &w, const int &p);
void readInputFile(string inputFilePath);
void buyerInfo(string& x, int y, string& buyer, string& address, string& date, string& temp);
void parseOrder(string &line, deque<WoodItem> &purorder, deque<string> &wood, deque<int> &allWood,
	string &typeOfWood, string &itemp);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
*	Start int main()
*/
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

	//Get the second line
	getline(inFile, firstLine);

	//Declaring what is needed to parse second line
	deque<WoodItem> purorder;
	deque<string> wood;
	deque<int> allWood;
	string typeOfWood;
	string itemp;

	//Sending that information in to parseOrder();
	parseOrder(firstLine, purorder, wood, allWood, typeOfWood, itemp);

	//TOTALING UP AND PRINTING OUT EVERYTHING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	double woodQuanAmount = 0, totalWoodQuantity = 0, totalWoodPrice = 0, tempETA;
	vector<double> eta;

	cout << "Buyer Name: " << buyer << endl
		<< "Address: " << address << endl
		<< "Purchase Date: " << date << endl;

	cout << "Order Details:" << endl;
	/*
		This while loop will gather information about two deques that have our
		WoodItem and the amount of that woodtype in the order. Simple math gives us
		the cost and the deliveryTime() function gives us the correct ETA which we
		simply print out to the screen.
	*/
	while (!purorder.empty())
	{
		totalWoodQuantity += allWood.back();
		cout << "Wood Type: " << purorder.back().type << "   Quantity: " << allWood.back()
			<< "   Price/BF: $" << purorder.back().price << endl;
		woodQuanAmount = purorder.back().price * allWood.back();
		cout << "Cost: $" << fixed << setprecision(2) << woodQuanAmount << endl;
		tempETA = deliveryTime(purorder.back(), allWood.back());
		eta.push_back(tempETA);

		totalWoodPrice += woodQuanAmount;
		purorder.pop_back();
		allWood.pop_back();
	}
	auto iter = max_element(eta.begin(), eta.end());

	/*
		If the quantity > 1000 we will not display the rest of the information.
		This could be done sooner but I chose to do it here.
	*/
	if (totalWoodQuantity > 1000)
	{
		cout << "I'm sorry, we only handle orders with quantities less than 1000." <<
			" Please readjust your order." << endl;
	}
	else
	{
		cout << "Delivery ETA: " << *iter << " hours." << endl;
		cout << "Total Price: $" << fixed << setprecision(2) << totalWoodPrice << endl;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}


/*
* Method to compute the deliveryTime. Takes in the back of the stacks since they're
* of the same WoodTypes and calculates ETA. Random comment for submission.
*/
double deliveryTime(const WoodItem &w, const int &woodAmount) {

	double deliveryETA = 0.0;

	//Taken from online assignment page
	if (woodAmount >= 501 && woodAmount < 1000)
		deliveryETA = 5.5 * w.baseDeliveryTime;
	else if (woodAmount >= 401)
		deliveryETA = 5 * w.baseDeliveryTime;
	else if (woodAmount >= 301)
		deliveryETA = 4 * w.baseDeliveryTime;
	else if (woodAmount >= 201)
		deliveryETA = 3 * w.baseDeliveryTime;
	else if (woodAmount >= 101)
		deliveryETA = 2 * w.baseDeliveryTime;
	else
		deliveryETA = 1 * w.baseDeliveryTime;

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
