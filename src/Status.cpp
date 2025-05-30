#include <iostream>
#include <string>
#include "Status.h"
#include "Item.h"

// _status(name,money,emotion,favor,moral,jailed)

Kid::Kid(bool temp){
	if(temp) _status = {"tempStatus",0,0,0,0,0};
	else _status = {"Your kid",200,100,0,0,0};
}

StatStruct Kid::getStatus(){
	return _status;
}

void Kid::resetTemp(){
	_status = {"tempStatus",0,0,0,0,0};
}

void Kid::addValues(Kid& temp){
	_status.money += temp.getStatus().money;
	_status.emotion += temp.getStatus().emotion;
	_status.favor += temp.getStatus().favor;
	_status.moral += temp.getStatus().moral;
	_status.jailed += temp.getStatus().jailed;
}

void Kid::talk(bool nice){
	int niceInt = nice ? 1 : -1;
	srand(time(NULL));
	int randFavor = niceInt*(rand()%5+1);
	_status.favor += randFavor;
	cout << "Favor " << (randFavor>0 ? '+' : '-') << (randFavor>0 ? randFavor : randFavor*(-1)) << endl;
}

void Kid::setName(string name){
	_status.name = name;
}

void Kid::payFoodMoney(){
	_status.money -= foodMoney;
}

void Kid::buyItem(int money){
	_status.money -= money;
}

void Kid::useItem(int emotion,int moral){
	_status.emotion += emotion;
	_status.moral += moral;
	_status.favor += 5; // Currently, letting your kid use the gift you bought raises favor by 5.
}

void Kid::goToWork(string name,Work work,string event){
	WorkStruct curWork = work.getInfo();
	
	if(curWork.name=="Jail"){
		cout << name << " stayed in jail." << endl << endl;
	}else if(curWork.name=="Rest"){
		cout << name << " took some well deserved rest." << endl
			 << "Emotion +25" << endl << endl; // Currently, resting heals 25 emotion.
		_status.emotion += 25; // Currently, resting heals 25 emotion.
	}else{
		cout << name << " worked as a " << curWork.name << "." << endl
			 << "Moral " << (curWork.moral>0 ? "+" : "") << curWork.moral << endl;
		if(event=="Economic boom") cout << "Money +" << curWork.money*1.25 << endl;
		else if(event=="Recession") cout << "Money +" << curWork.money*0.75 << endl;
		else cout << "Money +" << curWork.money << endl;
		cout << "Emotion -5" << endl << endl; // Currently, every work causes -5 emotion.
    	_status.moral += curWork.moral;
		_status.money += curWork.money;
    	_status.emotion -= 5; // Currently, every work causes -5 emotion.
		if(curWork.moral<0){ // Risk system
			// The lower curWork.moral is, the more dangerous.
			// curWork.moral also decides how long the kid will get jailed.
			srand(time(NULL));
			int risk = rand()%100;
			if(risk+curWork.moral<=0){ // Go to jail
				_status.jailed += curWork.moral*(-1)/10;
				cout << "A police found " << name << " suspicious!" << endl
					 << name << " will be jailed for the next " << curWork.moral*(-1)/10 << " months..." << endl << endl;
			} else // Safe for now
				cout << "Luckily, " << name << " didn't attract any police." << endl << endl;
		}
	}
}

void Kid::stayInJail(){
	_status.jailed--;
}

void Kid::outOfJail(){
	_status.money -= _status.jailed*100;
	_status.jailed = 0;
}

const char monthName[12][3+1] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

const char statResult[resultHeight][resultWidth+1] = // The x's are placeholders for actual data
{   "------------------------",
    "|                      |",
    "|  xxxxxxxxxxxxxxxxxx  |",
    "|                      |",
    "|                      |",
    "|  Moral         xxxx  |",
    "|                      |",
    "|  Favor         xxxx  |",
    "|                      |",
    "|  Money         xxxx	|",
	"|                      |",
	"|  Emotion       xxxx  |",
    "|                      |",
    "|----------------------|",
    "|                      |",
    "|  xxxxxxxxxxxxxxxxxx  |",
    "|                      |",
    "------------------------"
};

const char monthResult[resultHeight][resultWidth+1] = // The x's are placeholders for actual data
{   "------------------------",
    "|                      |",
    "|  Yearx xxx   Report  |",
    "|                      |",
    "|                      |",
    "|  Moral         xxxx  |",
    "|                      |",
    "|  Favor         xxxx  |",
    "|                      |",
    "|  Money         xxxx  |",
	"|                      |",
	"|  Emotion       xxxx  |",
    "|                      |",
    "|----------------------|",
    "|                      |",
    "|  xxxxxxxxxxxxxxxxxx  |",
    "|                      |",
    "------------------------"
};
