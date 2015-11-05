#ifndef ITEM_H
#define ITEM_H

typedef class Item
{
	char* description;
	double price;
public:
	Item();
	Item(Item&);
	Item(char*,double);
	~Item();
	friend ostream& operator<<(ostream&, Item&); 
}*pItem,**ppItem;

#endif