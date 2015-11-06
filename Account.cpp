/******************************************************************************
Filename:				Account.cpp
Version:				1.0
Author:					Victor Fernandes
Student No.:			040772243
Course Name/Number:		CST8219 - C++ Programming
Lab Section:			302
Assignment #:			1
Assignment Name:		FleaBay in C++
Due Date:				October 19, 2015
Submission Date:		October 19, 2015
Professor:				Andrew Tyler
Purpose:				The Account class manages its own list of items for
						every instantiated object, as well as reporting its
						information when FleaBay requests it.
******************************************************************************/
#include <iostream>
using namespace std;
#include "Item.h"
#include "Account.h"



/******************************************************************************
Function Name:			Account::Account()
Purpose:				Constructor for Account object to be used in the 
						FleaBay database.
In Parameters:			N/A
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
Account::Account(){
	numItems = 0;
	ID = nullptr;
	PassWord = nullptr;
	items = nullptr;
}

Account::Account(char* usr, char* passwd){
	numItems = 0;
	ID = new char[strlen(usr)+1];
	PassWord = new char[strlen(passwd)+1];
	strcpy(ID, usr);
	strcpy(PassWord, passwd);
	items = nullptr;
}

char*& Account::getPassWord() {
	return PassWord;
}

ostream& operator<<(ostream& os, Account& a){
	for (unsigned int i = 0; i < a.getnumItems(); i++){
		os << " Item " << i+1 << ": " << *a.items[i] << endl;
	}
	return os;
}

/******************************************************************************
Function Name:			Account::AddItem()
Purpose:				Prompts the user to add an item to the Account's Item
						storage list. It checks for proper price value and has
						an option to abort the process if desired.
In Parameters:			N/A
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
void Account::AddItem(){

	if (numItems){
		cout << "These are your items for sale:" << this << endl;
	} else{
		cout << "No items in your account." << endl;
	}

	// Set up check for multiple items
	bool bContinue = true;

	while (bContinue){
		char user_select;
		
		if (numItems){
			cout << "Would you like to add another item? (y/N): ";
		}
		else {
			cout << "Would you like to add an item? (y/N): ";
		}

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
		
			// Will continue to run until user gives up or enters a proper value for price
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
		else {
			bContinue = false; // Exit out of item creation
		}
	}

}


/******************************************************************************
Function Name:			Account::~Account()
Purpose:				Destructor for the Account object. It is called when
						the parent class, FleaBay, deletes it from the account
						list. 
In Parameters:			N/A
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
Account::~Account(){
	if (numItems > 0) {
		for (unsigned int i = 0; i < numItems; i++){
			delete items[i];
		}
		delete[] items;
	}
	delete ID;
	delete PassWord;
}

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