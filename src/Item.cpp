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
