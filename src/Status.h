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
	int jailed;
};

class Kid{
	private:
		StatStruct _status;
	public:
		Kid();
		void setName(string name);

		StatStruct getStatus();
		void talk(bool nice);
		void useItem(int emotion,int moral);
		void goToWork(Work work);
};

static const int moneySwitch = 500; // < switch: Bad, > switch: Good
static const int moralSwitch = 0; // Moral: -100 ~ 100
static const int favorSwitch = 0; // Favor: -100 ~ 100
static const int emotionSwitchMonth = 20; // Emotion: 0 ~ 100
static const int moneySwitchMonth = 100; // -50 each month

static const int resultHeight = 16;
static const int resultWidth = 24;

enum monthAdvice {M_NORMAL,M_TIRED,M_POOR,M_JAIL};
static const char monthAdvice[4][19] = {"Doing great!","Kind of tired...","We need money!","Staying in jail..."};

extern const char statResult[resultHeight][resultWidth+1];
extern const char monthResult[resultHeight][resultWidth+1];

#endif
