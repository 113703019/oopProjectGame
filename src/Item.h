#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Status.h"
using namespace std;

struct ItemStruct{
	static int itemID;
	string name;
	string des;
	int money;
	int moral;
	int emotion;
};

class Item{
	private:
		Itemstruct _item;
	public:
		Item();
		Item(string name,string des,int money,int moral,int emotion);
		Item(const Item& ogItem);
		Item& operator = (const Item& ogItem);
		~Item();

		ItemStruct getInfo();
		void buyItem(int id);
};

vector<Item> inventoryVec;
// Add default inventory items here

vector<Item> shopVec;
// Add shop items here
// shopVec.push_back(name,des,money,moral,emotion);
shopVec.push_back("Doll","",50,5,10);
shopVec.push_back("Game Console",200,0,50);
shopVec.push_back("")

#endif
