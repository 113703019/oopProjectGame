#ifndef _ROUNDUI_H_
#define _ROUNDUI_H_

#include "Status.h"

const int screenWidth = 69; // For UI formatting.
const int artOffset = 30; // For UI formatting.

class RoundUI{
	private:
		Kid _kid{false};
		Kid _tempStat{true};
	public:
		RoundUI(string name);
		Kid getKid();
		Kid getTemp();
		void payFoodMoney();

		void round(int curYear,int curMonth);
		void roundEnd(int curYear,int curMonth);
		bool talk();
		Work* plan(bool jailed);
		void work(Work* plan);
		void status();
		bool inventory();
		bool shop();
};

#endif
