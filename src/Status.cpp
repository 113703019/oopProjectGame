#include <iostream>
#include <string>
#include "Status.h"
#include "Item.h"

// _status(name,money,emotion,moral)

Kid::Kid()
	:_status{"Your kid",200,0,0}{}

Kid::Kid(string name)
	:_status{name,200,0,0}{}

StatStruct Kid::getStatus(){
	return _status;
}

void Kid::setName(string name){
	_status.name = name;
}

void Kid::useItem(int emotion,int moral){
	_status.emotion += emotion;
	_status.moral += moral;
}

void Kid::goToWork(Work work){
    _status.moral += work.getInfo().moral;
    _status.money += work.getInfo().money;
    _status.emotion -= 15; // Currently, every work causes -15 emotion.
}

const char monthName[12][3+1] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

char monthResult[resultHeight][resultWidth+1] = // The x's are placeholders for actual data
{   "------------------------",
    "|                      |",
    "|  xxx Monthly Report  |",
    "|                      |",
    "|                      |",
    "|  Moral          xxx  |",
    "|                      |",
    "|  Favor          xxx  |",
    "|                      |",
    "|  Money         xxxx  |",
    "|                      |",
    "|----------------------|",
    "|                      |",
    "|  xxxxxxxxxxxxxxxxxx  |",
    "|                      |",
    "------------------------"
};
