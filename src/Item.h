#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Status.h"
using namespace std;

struct ItenStruct{
	static int itemID;
	string name;
	int money;
	int emotion;
};

class Item{
	private:
		Itemstruct _item;
	public:
		Item();
		Item(string name,int money,int emotion);
		Item(const Item& ogItem);
		Item& operator = (const Item& ogItem);
		~Item();

		ItemStruct getInfo();
		void buyItem(ItemStruct item);
};

vector<Item> inventoryVec;
// Add default inventory items here

vector<Item> shopVec;
// Add shop items here

#endif
