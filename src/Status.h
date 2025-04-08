#ifndef _STATUS_H_
#define _STATUS_H_

#include <iostream>
#include <vector>
#include "Work.h"
using namespace std;

extern const char monthName[12][3+1];

struct StatStruct{
	string name;
	int money;
    int emotion;
	int favor;
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
		void talk(bool nice);
		void useItem(int emotion,int moral);
		void goToWork(Work work);
};

static const int resultHeight = 16;
static const int resultWidth = 24;

extern char monthResult[resultHeight][resultWidth+1];

#endif
