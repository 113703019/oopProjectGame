#ifndef _STATUS_H_
#define _STATUS_H_

#include <iostream>
#include <vector>
using namespace std;

string month = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};

class Kid{
	private:
		struct Status{
			string name;
			int money;
			int emotion;
			int moral;
		};
		Status _status;
	public:
		Kid();
		Kid(string name);
		void setName(string name);
		Status getStatus();
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
	"|----------------------|"
	"|                      |",
	"|  xxxxxxxxxxxxxxxxxx  |",
	"|                      |",
	"------------------------"
};

#endif
