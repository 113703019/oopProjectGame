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
// workVec.push(_name,_moral,_money);
workVec.push(); // Default: Rest
workVec.push("Clerk",10,100);
workVec.push("Thief",10,-200);

#endif
