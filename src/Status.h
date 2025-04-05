#ifndef _STATUS_H_
#define _STATUS_H_

#include <iostream>
#include <vector>
using namespace std;

char month[12][3+1] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

struct StatStruct{
	string name;
	int money;
    int emotion;
	int moral;
};

class Kid{
	private:
		StatStruct _status;
	public:
		Kid();
		Kid(string name);
		void setName(string name);
		StatStruct getStatus();
		void useItem(Item targetItem){
};

const int resultHeight = 16;
const int resultWidth = 24;

char monthResult[resultHeight][resultWidth+1] = // The x's are placeholders for actual data
{	"------------------------",
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

#endif
