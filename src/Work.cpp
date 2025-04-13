#include <iostream>
#include <string>
#include <vector>
#include "Work.h"

Work::Work()
	:_info{"Unknown",0,0}{}

Work::Work(string name,int moral,int money)
	:_info{name,moral,money}{}

Work::Work(const Work& ogWork){
	_info = ogWork._info;
}

Work& Work::operator = (const Work& ogWork){
	if(this == &ogWork) return *this;
	// No pointers, this can be kept simple
	_info = ogWork._info;
	return *this;
}

Work::~Work(){}

WorkStruct Work::getInfo(){
	return _info;
}

PlanManager::PlanManager(){
	// Add new works here
	// _workVec.push_back(_name,_moral,_money);
	_workVec.emplace_back("Jail",0,0); // Jail (No emotion refill)
	_workVec.emplace_back("Rest",0,0); // Rest (With emotion refill)
	_workVec.emplace_back("Clerk",10,120);
	_workVec.emplace_back("Vet",25,200);
	_workVec.emplace_back("Thief",-10,200);
	_workVec.emplace_back("Robber",-25,450);
	_workVec.emplace_back("Drug dealer",-60,1500);
	_workVec.emplace_back("Fucking kill a police",-100,0); //debug
}

vector<Work> PlanManager::getWork(){
	return _workVec;
}
