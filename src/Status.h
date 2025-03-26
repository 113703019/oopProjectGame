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
		Status getStatus();
};

#endif
