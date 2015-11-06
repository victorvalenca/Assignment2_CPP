/******************************************************************************
Filename:				Item.cpp
Version:				2.1
Author:					Victor Fernandes
Student No.:			040772243
Course Name/Number:		CST8219 - C++ Programming
Lab Section:			302
Assignment #:			1
Assignment Name:		FleaBay in C++
Due Date:				October 22, 2015
Submission Date:		October 21, 2015
Professor:				Andrew Tyler
Purpose:				The Item class holds information for an item an Account
						object may hold. It contains a description, price, and
						reports itself when called.
******************************************************************************/
#include <iostream>

using namespace std;
#include "Item.h"

/******************************************************************************
Function Name:			Item::Item()
Purpose:				Constructor for the Item object to be used with its
						respective Account object.
In Parameters:			N/A
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
Item::Item(){
	description = nullptr;
	price = 0.0;
}

/******************************************************************************
Function Name:			Item::Item()
Purpose:				Constructor for the Item object to be used with its
						respective Account object that takes in parameters for
						creation.
In Parameters:			char*, double
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
Item::Item(char* desc, double p) {
	this->description = new char[strlen(desc)+1];
	strcpy(description, desc);
	this->price = p;
}

/******************************************************************************
Function Name:			Item::Item()
Purpose:				Copy constructor for Item
In Parameters:			Item&
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
Item::Item(Item &it) {
	this->description = new char[strlen(it.description)+1];
	strcpy(description, it.description);
	this->price = it.price;
}

/******************************************************************************
Function Name:			Item::operator<<
Purpose:				Overloaded << operator for std::ostream
In Parameters:			ostream&, Item&
Out Parameters:			ostream&
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
ostream& operator<<(ostream& os, Item& it) {
	os << it.description << " , Cost: $" << it.price;
	return os;
}

/******************************************************************************
Function Name:			Item::~Item()
Purpose:				Destructor for the Item object.
In Parameters:			N/A
Out Parameters:			N/A
Version:				1.0
Author:					Victor Fernandes
******************************************************************************/
Item::~Item(){
	delete description;
}
