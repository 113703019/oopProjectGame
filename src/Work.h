#ifndef _WORK_H_
#define _WORK_H_

#include <string>
#include <vector>
#include "Status.h"

class Work{
	public:
		Work();
		Work(string nm,int mr,int mn);
		~Work();
		void goToWork(Work work);
	private:
		string _name;
		int _moral; // Good work > 0
					// Bad work < 0
		int _money;
};

vector<Work> workVec;

// Add new works here
// workVec.push_back(_name,_moral,_money);
workVec.push_back(); // Default: Rest
workVec.push_back("Clerk",10,100);
workVec.push_back("Thief",10,-200);

#endif
