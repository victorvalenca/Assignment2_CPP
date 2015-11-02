#ifndef FLEABAY_H
#define FLEABAY_H

typedef class FleaBay
{
	unsigned int numAccounts;
	ppAccount accounts;
	bool AddNewAccount();
public:
	FleaBay();						
	~FleaBay();
	bool Login();				
	Account operator[](char*);
	friend ostream& operator<<(ostream&,FleaBay&);
}* pFleaBay;

#endif