#include <iostream>
#include <string>
#include <vector>
#include "Status.h"
#include "Work.h"

Work::Work(){
	_name = "Rest";
	_moral = 0;
	_money = 0;
}

Work::Work(string &name,int moral,int money)
	:_name(name), _moral(moral), _money(money){}

void Work::goToWork(Work work){
	getStatus().moral += work._moral;
	getStatus().money += work._money;
	getStatus().emotion -= 15;
}

Work::~Work(){
	delete _name;
	delete _moral;
	delete _money;
}

PlanManager::PlanManager(){
	// Add new works here
	// _workVec.push_back(_name,_moral,_money);
	_workVec.emplace_back(); // Default: Rest
	_workVec.emplace_back("Clerk",10,120);
	_workVec.emplace_back("Vet",25,200);
	_workVec.emplace_back("Thief",-10,200);
	_workVec.emplace_back("Robber",-25,450);
	_workVec.emplace_back("Drug dealer",-60,1500);
}
