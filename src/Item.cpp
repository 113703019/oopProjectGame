#include <iostream>
#include <vector>
#include "Status.h"
#include "Item.h"
using namespace std;

int Item::_itemIDcounter = 0;

Item::Item()
	:_item{_itemIDcounter++,"UnknownItem","Default description.",0,0,0}{}

Item::Item(string name,string desc,int money,int moral,int emotion)
	:_item{_itemIDcounter++,name,desc,money,moral,emotion}{}

Item::Item(const Item& ogItem){
	ItemStruct og = ogItem._item;
	_item = {og.itemID,og.name,og.desc,og.money,og.moral,og.emotion};
}

Item& Item::operator = (const Item& ogItem){
	if(this == &ogItem) return *this;
	// No pointers, this can be kept simple
	ItemStruct og = ogItem._item;
	_item = {og.itemID,og.name,og.desc,og.money,og.moral,og.emotion};
	return *this;
}
	
Item::~Item(){}

ItemStruct Item::getInfo(){
	return _item;
}

ItemManager::ItemManager(){
	// Add default inventory items here
	// _inventoryVec.emplace_back(name,des,money,moral,emotion);

	// Add shop items here
	// _shopVec.emplace_back(name,des,money,moral,emotion);
	_shopVec.emplace_back("Doll","Cute and fluffy.",50,5,10);
	_shopVec.emplace_back("Game Console","Lots of interesting games!",200,0,50);
	_shopVec.emplace_back("Toy Knife","The shop owner found it in some ruins.",50,-5,10);
}

vector<Item> ItemManager::getInventory(){
	return _inventoryVec;
}

vector<Item> ItemManager::getShop(){
    return _shopVec;
}

Item* ItemManager::getInfoViaID(int id){
	for(auto& item : _shopVec)
		if(item.getInfo().itemID==id) return &item;
	return nullptr;
}

void ItemManager::buyItem(int id){
   	// Technically, I could just pass an item...
	// Though, I want to implement copying somewhere somehow.
	Item* result = getInfoViaID(id);
	if(result==nullptr)
		cout << "No such item in shop!" << endl;
	else
		_inventoryVec.push_back(*result);
}

void ItemManager::useItem(int id,Kid& kid){
	Item* result = getInfoViaID(id);
	if(result==nullptr)
		cout << "No such item in inventory!" << endl;
	else{
		kid.useItem(result->getInfo().emotion,result->getInfo().moral);
		_inventoryVec.erase(_inventoryVec.begin()+id);
	}
}
