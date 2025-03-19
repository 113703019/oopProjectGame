#ifndef _STATUS_H_
#define _STATUS_H_

#include <iostream>
#include <vector>

class Kid{

	private:
		struct Status{
			std::string name;
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
