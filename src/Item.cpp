#include <iostream>
#include <vector>
#include "Item.h"
#include "Status.h"
using namespace std;

Item::Item()
	:_item{itemID++,"UnknownItem",0,0}{}

Item::Item(string name,int money,int emotion)
	:_item{itemID++,name,money,emotion}{}

Item::Item(const Item& ogItem)
	:_item{itemID,name,money,emotion}{}

Item& Item::operator = Item(const Item& ogItem){
	if(this == &ogItem) return *this;
	// No pointers, this can be kept simple
	_item = ogItem;
	return *this;
}
	
:~Item(){}

ItemStruct Item::getInfo(){
	return _item;
}

void Item::buyItem(int id)
   	// Technically, I could just pass an item...
	// Though, I want to implement copying somewhere somehow.
	if(find(shopVec.begin(),shopVec.end(),getInfo().itemID)==shopVec.end())
		cout << "No such item in shop!" << endl;
	else
		inventoryVec.push_back(shopVec[id]);
}
