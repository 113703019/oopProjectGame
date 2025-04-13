#ifndef _STATUS_H_
#define _STATUS_H_

#include <iostream>
#include <vector>
#include "Work.h"
using namespace std;

extern const char monthName[12][3+1];
static const int foodMoney = 50; // Monthly expense. Essential to pay for survival.

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
		Kid(bool temp);
		void setName(string name);

		StatStruct getStatus();
		void resetTemp();
		void addValues(Kid& temp);
		void talk(bool nice);
		void payFoodMoney();
		void useItem(int emotion,int moral);
		void goToWork(string name,Work work);
};

static const int moneySwitch = 500; // < switch: Bad, > switch: Good
static const int moralSwitch = 0; // Moral: -100 ~ 100
static const int favorSwitch = 0; // Favor: -100 ~ 100
static const int emotionSwitchMonth = 20; // Emotion: 0 ~ 100
static const int moneySwitchMonth = 100; // -50 each month

static const char kidScript[4][46] = {
	"Hello! What should I do this month?",
	"I will work hard for this month too!",
	"...For real, why should I behave?",
	"Nooo... I don't wanna work...",
};

enum kidTalk {T_NORMAL,T_LOVE,T_HATE,T_JAIL};
static const char kidTalkLove[4][16] = {
	"Aww, thank you.",
	"I love you too!",
	"Tsk, whatever.",
	"...Sorry."
};
static const char kidTalkHate[4][33] = {
	"Ouch, that's mean...",
	"W-What, but why?",
	"The feeling's mutual, bastard.",
	"To be fair, I kinda deserved it."
};

static const int resultHeight = 18;
static const int resultWidth = 24;

enum monthAdvice {M_NORMAL,M_TIRED,M_POOR,M_JAIL};
static const char monthAdvice[4][19] = {"Doing great!","Kind of tired...","We need money!","Staying in jail..."};

extern const char statResult[resultHeight][resultWidth+1];
extern const char monthResult[resultHeight][resultWidth+1];

#endif

