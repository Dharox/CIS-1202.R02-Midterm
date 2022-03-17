/*
Daniel Breslin
3/8/2022
CIS 1202.R02 Midterm Project
*/

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<cstring>
#include<vector>

using namespace std;

struct Product_S
{
	int productID;
	char productName[50];
	float productPrice;
};

Product_S Get_Products();
int Menu();
int Get_Order(vector<Product_S> &idList, Product_S products[], int numItems);

int main()
{
	// Required elements.
	double* sumPrice = new double;
	double* avgPrice = new double;
	vector<Product_S> idList;
	Product_S products[100];
	int menuChoice;
	int numItems = 0;
	int numOrdered = 0;

	// bool to control loop for entering data.
	bool repeat = true;

	cout << setprecision(2) << fixed;

	while (repeat && numItems < 100)
	{
		menuChoice = Menu();

		switch (menuChoice)
		{
		case 1:// Enter new item.
			products[numItems] = Get_Products();
			numItems++;
			break;
		case 2:// Enter new order.
			numOrdered = Get_Order(idList, products, numItems);
			break;
		case 3:// Exit
			repeat = false;
		default:// Extreme error; shouldn't be possible unless Menu function gets extremely broken somehow.
			cout << "\nCatastrophic error encountered. Program will terminate.";
		}
	}

	// Inform user if max number of products have been entered.
	if (numItems >= 100)
	{
		cout << "\nMax number of products reached.";
	}

	*sumPrice = 0;
	cout << "\nProducts ordered: ";
	for (int i = 0; i < numOrdered; i++)
	{
		cout << "\nID:\t\t" << idList[i].productID;
		cout << "\nProduct:\t" << idList[i].productName;
		cout << "\nPrice:\t\t$" << idList[i].productPrice << endl;

		*sumPrice += idList[i].productPrice;
	}

	*avgPrice = *sumPrice / numOrdered;
	cout << "\nThe order average is $" << *avgPrice;

	// Forgot to delete DMA pointers in original; change added in class 3/15/22.
	delete sumPrice;
	delete avgPrice;

	return 0;
}
// Menu to drive program.
int Menu()
{
	int choice;
	bool takingInput = true;
	// This string will be used for taking user input then validating it.
	string userInput;

	cout << "What would you like to do? " << endl;
	cout << "\n1. Enter new product";
	cout << "\n2. Enter order";
	cout << "\n3. Exit";

	// While loop with try-catch statements to check for input errors and catch exceptions.
	while (takingInput)
	{
		cout << "\nPlease enter your choice: ";
		cin >> userInput;
		// Try to convert userInput string to proper datatype.
		try
		{
			choice = stoi(userInput);
			takingInput = false;
			if (choice < 1 || choice > 3)
			{
				cout << "\nError, please enter a number 1-3.";
				takingInput = true;
			}
		}
		catch (invalid_argument e)
		{
			cout << "\n\"" << userInput << "\" is not valid: ";
		}
	}

	return choice;
}
// Enter data into the structure and store structure in an array.
Product_S Get_Products()
{
	Product_S newProduct;
	string userInput;
	bool takingInput = true;

	// While loop with try-catch statements to check for input errors and catch exceptions.
	while (takingInput)
	{
		cout << "\nEnter the 5-digit product ID: ";
		cin >> userInput;
		try
		{
			newProduct.productID = stoi(userInput);
			takingInput = false;

			if (newProduct.productID < 10000 || newProduct.productID > 99999)
			{
				cout << "\nError: please enter a 5-digit number that does not start with zero: ";
				takingInput = true;
			}
		}
		catch (invalid_argument e)
		{
			cout << "\n\"" << userInput << "\" is not valid, please re-enter: ";
		}
	}

	cin.ignore();
	cout << "\nEnter the product name: ";
	cin.get(newProduct.productName, 50);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// While loop with try-catch statements to check for input errors and catch exceptions.
	// Reset takingInput to true for try-catch control.
	takingInput = true;
	while (takingInput)
	{
		cout << "\nEnter the product price: ";
		cin >> userInput;
		try
		{
			newProduct.productPrice = stof(userInput);
			takingInput = false;
		}
		catch (invalid_argument e)
		{
			cout << "\n\"" << userInput << "\" is not valid, please re-enter: ";
		}
	}

	return newProduct;
}
// Enter IDs of products ordered and store IDs in vector.
int Get_Order(vector<Product_S> &idList, Product_S products[], int numItems)
{
	int orderItems = 0;
	bool repeat = true;
	int productID;
	int prodPosition = -1;

	while (repeat)
	{
		cout << "\nPlease enter a product ID for this order: ";
		cin >> productID;

		for (int i = 0; i < numItems; i++)
		{
			if (productID == products[i].productID)
			{
				idList.push_back(products[i]);
				orderItems++;
				prodPosition = i;
			}
		}
		
		if (productID != products[prodPosition].productID)
		{
			cout << "\nNo match found for product ID: " << productID;
		}

		cout << "\nWould you like to enter another item?";
		cout << "\n1. Yes";
		cout << "\n0. No" << endl;
		cin >> repeat;
	}

	return orderItems;
}
