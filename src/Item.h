#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <iostream>
#include <vector>
#include "Status.h"
using namespace std;

struct ItemStruct{
	int itemID;
	string name;
	string desc;
	int money;
	int moral;
	int emotion;
};

class Item{
	private:
		ItemStruct _item;
		static int _itemIDcounter;
	public:
		Item();
		Item(string name,string desc,int money,int moral,int emotion);
		Item(const Item& ogItem);
		Item& operator = (const Item& ogItem);
		~Item();

		ItemStruct getInfo();
};

class ItemManager{
	private:
		vector<Item> _inventoryVec;
		vector<Item> _shopVec;
	public:
		ItemManager();
		
		vector<Item> getInventory();
		vector<Item> getShop();
		Item* getInfoViaID(int id);
		void buyItem(int id);
		void useItem(int id,Kid& kid);
};

#endif
