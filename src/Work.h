#ifndef _WORK_H_
#define _WORK_H_

#include <string>
#include <vector>
#include "Status.h"

class Work{
	private:
		string _name;
		int _moral; // Good work > 0
					// Bad work < 0
		int _money;
	public:
		Work();
		Work(string nm,int mr,int mn);
		Work(const Work& ogWork);
		Work& operator = (const Work& ogWork);
		~Work();
		void goToWork(Work work);
};

class PlanManager{
	private:
		vector<Work> _workVec;
	public:
		PlanManager();
};

#endif
