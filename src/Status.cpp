#include <iostream>
#include <string>
#include "Status.h"
#include "Item.h"

// _status(name,money,emotion,favor,moral)

Kid::Kid()
	:_status{"Your kid",200,100,0,0}{}

StatStruct Kid::getStatus(){
	return _status;
}

void Kid::talk(bool nice){
	int niceInt = nice ? 1 : -1;
	_status.favor += niceInt*5;
}

void Kid::setName(string name){
	_status.name = name;
}

void Kid::useItem(int emotion,int moral){
	_status.emotion += emotion;
	_status.moral += moral;
	_status.favor += 5; // Currently, letting your kid use the gift you bought raises favor by 5.
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
    "|  Yearx xxx   Report  |",
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
