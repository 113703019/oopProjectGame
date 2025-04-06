#include <iostream>
#include <string>
#include <vector>
#include "Work.h"

Work::Work()
	:_info{"Rest",0,0}{}

Work::Work(string name,int moral,int money)
	:_info{name,moral,money}{}

Work::Work(const Work& ogWork){
	WorkStruct og = ogWork._info;
	_info = {og.name,og.money,og.moral};
}

Work& Work::operator = (const Work& ogWork){
	if(this == &ogWork) return *this;
	// No pointers, this can be kept simple
	WorkStruct og = ogWork._info;
	_info = {og.name,og.money,og.moral};
	return *this;
}

Work::~Work(){}

WorkStruct Work::getInfo(){
	return _info;
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
