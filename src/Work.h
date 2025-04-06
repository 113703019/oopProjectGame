#ifndef _WORK_H_
#define _WORK_H_

#include <string>
#include <vector>
using namespace std;

struct WorkStruct{
	string name;
	int moral; // Good work > 0
				// Bad work < 0
	int money;
};

class Work{
	private:
		WorkStruct _info;
	public:
		Work();
		Work(string nm,int mr,int mn);
		Work(const Work& ogWork);
		Work& operator = (const Work& ogWork);
		~Work();

		WorkStruct getInfo();
};

class PlanManager{
	private:
		vector<Work> _workVec;
	public:
		PlanManager();
};

#endif
