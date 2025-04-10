#ifndef _ROUNDUI_H_
#define _ROUNDUI_H_

#include "Status.h"

const int screenWidth = 69; // For UI formatting.
const int artOffset = 30; // For UI formatting.
const int foodMoney = 50; // Monthly expense. Essential to pay for survival.

class RoundUI{
	private:
		Kid _kid;
	public:
		RoundUI(string name);
		void round(int curYear,int curMonth);
		void roundEnd(int curYear,int curMonth);
		bool talk();
		bool plan(bool jailed);
		void status();
		void inventory();
		void shop();
};

#endif
