#include <iostream>
#include <string>
#include "Status.h"

// _status(name,money,emotion,moral)

Kid::Kid()
	:_status("Your kid",200,0,0);{}

Kid::Kid(string name)
	:_status(name,200,0,0){}

Status Kid::getStatus(){
	return _status;
}
