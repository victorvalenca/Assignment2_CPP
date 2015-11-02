/******************************************************************************
Filename:				FleaBay.cpp
Version:				2.0
Author:					Victor Fernandes
Student No.:			040772243
Course Name/Number:		CST8219 - C++ Programming
Lab Section:			302
Assignment #:			2
Assignment Name:		FleaBay in C++
Due Date:				October 22, 2015
Submission Date:		October 21, 2015
Professor:				Andrew Tyler
Purpose:				The FleaBay class is used to manage Accounts and their
						list of Items, authenticate, and generate
						database reports.
******************************************************************************/
#include "Item.h"
#include "Account.h"
#include "FleaBay.h"
#include <iostream>
using namespace std;

/******************************************************************************
Function Name:		FleaBay::FleaBay()
Purpose:			Constructor for the FleaBay database.
In Parameters:		N/A
Out Parameters:		N/A
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
FleaBay::FleaBay(){
	numAccounts = 0;
	accounts = nullptr;
}

ostream& operator<<(ostream& os ,FleaBay& f) {
	if (f.numAccounts) {
		for (unsigned int i = 0; i < f.numAccounts; i++){
				os << "Account ID: " << f.accounts[i]->getID() << endl
					 << f.accounts[i];
		}
	}
	else {
		os << "** NO ACCOUNTS **" << endl;
	}
	return os;
}

Account FleaBay::operator[](char* acc) {
	for (unsigned int i = 0; i < numAccounts; i++){
		if (!strcmp(accounts[i]->getID(), acc)){
			return *accounts[i];
		}
	}
	return;

}

/******************************************************************************
Function Name:		FleaBay::Login()
Purpose:			Secondary selection menu to allow the user to add or
					manage their own account.
In Parameters:		N/A
Out Parameters:		Boolean
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
bool FleaBay::Login(){
	char user_select;
	char login_buffer[80] = {'\0'};
	char passwd_buffer[80] = {'\0'};

	bool user_check = true;
	bool found = false;

	cout << "1. Add a new Account" << endl;
	cout << "2. Open an existing Account" << endl;
	cout << "3. Return to main menu" << endl;
	fflush(stdin);
	cin >> user_select;

	switch(user_select) {
	case '1': //TODO: Add New Account
		if (!AddNewAccount()){}
		break;
	case '2': //TODO: Account Management
		if(!numAccounts){
			cout << "There are no accounts." << endl;
			break;
		}

		// Username prompt and validation
		cout << "Please enter your account ID: ";
		fflush(stdin);
		cin.getline(login_buffer,80);
		unsigned int i;
		for(i = 0; i < numAccounts && !found;) {
			if (strcmp(accounts[i]->getID(), login_buffer) != 0) {
				if (i == numAccounts) {
					//Do nothing and move on
				} else {
					i++;
				}
			} else {
				found = true;
			}
		}

		//Password Prompt
		if (found) {
			cout << "Please enter your password: ";
			fflush(stdin);
			cin.getline(passwd_buffer,80);
			if (!strcmp(accounts[i]->getPassWord(), passwd_buffer)){
				accounts[i]->AddItem();
			} else {
				cout << "Password doesn't match this ID." << endl;
				break;
			}
		}
		break;
	case '3': // Return to menu
		break;
	default:
		cout << "Invalid selection. Returning to main menu..." << endl;
		break;
	}

	return true;
}

/******************************************************************************
Function Name:		FleaBay::AddNewAccount()
Purpose:			Prompts the user for account login information and
					prepares the database to add a new account.
In Parameters:		N/A
Out Parameters:		Boolean
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
bool FleaBay::AddNewAccount(){
	Account *newEntry;
	char login_buffer[80] = {'\0'};
	char passwd_buffer[80] = {'\0'};
	bool check = true;

	cout << "Please enter your account ID: " << endl;
	fflush(stdin);
	cin.getline(login_buffer,80);
	for (unsigned int i = 0; i < FleaBay::numAccounts; i++){
		if (!strcmp(accounts[i]->getID(), login_buffer)){
			cout << "Account already exists" << endl;
			check = false;
			break;
		}
	}

	if (check){
		cout << "Please enter your password: " << endl;
		fflush(stdin);
		cin.getline(passwd_buffer,80);
		
		char* ID = new char[strlen(login_buffer)+1];
		char* passwd = new char[strlen(passwd_buffer)+1];
		strcpy(ID, login_buffer);
		strcpy(passwd, passwd_buffer);
		newEntry = new Account(ID, passwd);

		ppAccount newAccounts = new pAccount[numAccounts+1];
		if (accounts == nullptr){
			accounts = newAccounts;
		}
		else {
			for (unsigned int i = 0; i < numAccounts; i++) {
				newAccounts[i] = accounts[i];
			}
			delete[] accounts;
			accounts = newAccounts;
		}

		accounts[numAccounts] = newEntry;
		numAccounts++;
	}

	return true;
}

/******************************************************************************
Function Name:		FleaBay::~FleaBay()
Purpose:			Destructor for the FleaBay database. It iterates through
					its account list and deletes them, followed by the list
					itself.
In Parameters:		N/A
Out Parameters:		N/A
Version:			1.0
Author:				Victor Fernandes
******************************************************************************/
FleaBay::~FleaBay(){
	if (numAccounts > 0){
		for (unsigned int i = 0; i < numAccounts; i++) {
			delete accounts[i];
		}
	}
	delete[] accounts;
}