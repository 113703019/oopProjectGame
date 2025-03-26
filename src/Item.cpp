#include <iostream>
#include <vector>
#include "Item.h"
#include "Status.h"
using namespace std;

int shopID = 0;

Item::Item()
	:_item{itemID++,"UnknownItem",0,0}{}

Item::Item(string name,int money,int emotion)
	:_item{itemID++,name,money,emotion}{}

Item::Item(const Item& ogItem){
	// In progress: Copy constructor
}

Item& Item::operator = Item(const Item& ogItem){
	// In progress: Copy assignment constructor
}

Item::~Item(){
	// In progress: Destructor
}

ItemStruct Item::getInfo(){
	return _item;
}
