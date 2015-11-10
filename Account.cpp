/******************************************************************************
Filename:			Account.cpp
Version:			2.1
Author:				Victor Fernandes
Student No.:			040772243
Course Name/Number:		CST8219 - C++ Programming
Lab Section:			302
Assignment #:			1
Assignment Name:		FleaBay in C++
Due Date:			October 19, 2015
Submission Date:		October 19, 2015
Professor:			Andrew Tyler
Purpose:			The Account class manages its own list of items for
				every instantiated object, as well as reporting its
				information when FleaBay requests it.
******************************************************************************/
#include <iostream>
using namespace std;
#include "Item.h"
#include "Account.h"



/******************************************************************************
Function Name:			Account::Account()
Purpose:			Constructor for Account object to be used in the 
				FleaBay database.
In Parameters:			N/A
Out Parameters:			N/A
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
Account::Account(){
	numItems = 0;
	ID = nullptr;
	PassWord = nullptr;
	items = nullptr;
}

/******************************************************************************
Function Name:			Account::Account()
Purpose:			Constructor for the Account object to be used with its
				respective Account object that takes in parameters for
				creation.
In Parameters:			char*, char*
Out Parameters:			N/A
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
Account::Account(char* usr, char* passwd){
	numItems = 0;
	ID = new char[strlen(usr)+1];
	PassWord = new char[strlen(passwd)+1];
	strcpy(ID, usr);
	strcpy(PassWord, passwd);
	items = nullptr;
}

/******************************************************************************
Function Name:			Account::Account()
Purpose:			Copy constructor for Account
In Parameters:			Account&
Out Parameters:			N/A
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
Account::Account(Account& obj) {
	this->numItems = obj.numItems;
	this->ID = new char[strlen(obj.ID)+1];
	this->PassWord = new char[strlen(obj.PassWord)+1];

	strcpy(ID, obj.ID);
	strcpy(PassWord, obj.PassWord);

	if (obj.numItems){
		this->items = new pItem[obj.numItems];
		for (unsigned int i = 0; i < obj.numItems; i++) {
			this->items[i] = new Item(*obj.items[i]);
		}
	}
	else {
		this->items = nullptr;
	}
}

/******************************************************************************
Function Name:			Account::getPassWord()
Purpose:			Return a reference to the PassWord data member
In Parameters:			N/A
Out Parameters:			char*&
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
char*& Account::getPassWord() {
	return PassWord;
}

/******************************************************************************
Function Name:			operator<<
Purpose:			Overloaded << operator for std::ostream
In Parameters:			ostream&, Account&
Out Parameters:			ostream&
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
ostream& operator<<(ostream& os, Account& a){
	for (unsigned int i = 0; i < a.getnumItems(); i++){
		os << " Item " << i+1 << ": " << *a.items[i] << endl;
	}
	return os;
}

/******************************************************************************
Function Name:			Account::AddItem()
Purpose:			Prompts the user to add multiple items to the Account's
				Item storage list. It checks for proper price value and
				has an option to abort the process if desired. It also 
				lets the user change their password.
In Parameters:			N/A
Out Parameters:			N/A
Version:			1.1
Author:				Victor Fernandes
******************************************************************************/
void Account::AddItem(){

	// Set up check for multiple items
	bool bContinue = true;

	while (bContinue){
		if (numItems){
			cout << "*******************************" << endl
			     << "These are your items for sale: " << endl 
				 << " " << *this;
		} else{
			cout << "No items in your account." << endl;
		}
		char user_select;
		
		cout << "(P) Change password" << endl
		     << "(Y) Add an item" << endl
			 << "(Any key) Return to previous menu" << endl;

		fflush(stdin);
		cin >> user_select;

		if (toupper(user_select) == 'Y'){
			char desc_buffer[100] = {'\0'};
			double price_buffer;
			cout << "Enter the new Item description: ";
			fflush(stdin);
			cin.getline(desc_buffer, 100);

			// Set up condition checks
			bool price_ok = false;
			bool cancelled = false;
		
			// Will continue to run until user gives up or enters a proper price
			while (!price_ok || cancelled){
				cout << "\nEnter the item price (or -1.0 to cancel): ";
				fflush(stdin);
				cin >> price_buffer;

				if (!cin.good()){
					cin.clear();
					cin.ignore(128,'\n');
					cout << endl << "Incorrect value. Try again with a proper number";
					continue;
				}
			
				if (price_buffer == -1.0){
					cancelled = true;
					break; // Break out of loop and cancel
				}

				price_ok = true;

			}

			if (cancelled){
				return; //Check if user cancelled item entry and exit function if so
			} 

		
			char* description = new char[strlen(desc_buffer)+1];
			double price = price_buffer;
			strcpy(description, desc_buffer);
			Item *newItem = new Item(description, price);

			ppItem newItems = new pItem[numItems+1];

			if (items == nullptr){
				items = newItems;
			} else {
				for (unsigned int i = 0; i < numItems; i++) {
						newItems[i] = items[i];
					}
				delete[] items;
				items = newItems;
			}
			items[numItems++] = newItem;
		
		}
		else if (toupper(user_select) == 'P'){
			char passwd_buffer[80] = {'\0'};

			cout << "Please enter the new password: ";
			fflush(stdin);
			cin.getline(passwd_buffer, 80);

			while (!strcmp(this->getPassWord(), passwd_buffer)) {
				cout << "*** This password is identical to your current one." << endl
				     << "Please enter a different password: ";
				fflush(stdin);
				cin.getline(passwd_buffer, 80);
			}

			delete this->PassWord;
			this->PassWord = new char[strlen(passwd_buffer)+1];
			strcpy(this->PassWord, passwd_buffer);

			cout << "Password change successful." << endl;

		}
		else {
			bContinue = false; // Exit out of menu
		}
	}

}


/******************************************************************************
Function Name:			Account::~Account()
Purpose:			Destructor for the Account object. It is called when
				the parent class, FleaBay, deletes it from the account
				list. 
In Parameters:			N/A
Out Parameters:			N/A
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
Account::~Account(){
	if (numItems > 0) {
		for (unsigned int i = 0; i < numItems; i++){
			delete items[i];
		}
		delete[] items;
	}
	delete[] ID;
	delete[] PassWord;
}

