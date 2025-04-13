#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <cmath>

#include "RoundUI.h"
#include "Status.h"
#include "Item.h"
#include "AsciiSprite.h"

RoundUI::RoundUI(string name)
	:_event{"None",0}{
	_kid.setName(name);
}

Kid RoundUI::getKid(){
	return _kid;
}

Kid RoundUI::getTemp(){
	return _tempStat;
}

void RoundUI::payFoodMoney(){
	_tempStat.payFoodMoney();
}

void RoundUI::round(int curYear,int curMonth){

	char uiInput;
	enum flag {TALK,PLAN,INVEN,SHOP};
	bool flag[4] = {false};
	_tempStat.resetTemp();
	Work* monthPlan = new Work[3];

	// 15% chance for economic boom.
	// 15% chance for recession.
	srand(time(NULL));
	int randEvent = rand()%100;
	if(_event.name!="None"&&_event.months<=0){ // Reset
		_event.name = "None";
		_event.months = 0;
	}
	if(_event.name=="None"){
		if(randEvent>=0&&randEvent<15){ // Economic boom
			_event.name = "Economic boom";
			_event.months = 3;	
		} else if(randEvent>=15&&randEvent<30){ // Recession
			_event.name = "Recession";
			_event.months = 3;
		}
	} else _event.months--;

	bool monthEnd = false;
	do{
		StatStruct cur = _kid.getStatus();
		int kidState = NORMAL;
		if(cur.jailed) kidState = JAIL;
		else if(cur.emotion<emotionSwitchMonth) kidState = TIRED;
		else if(cur.moral>50) kidState = GOOD;
		else if(cur.moral<-50) kidState = BAD;

    	cout << endl << string(screenWidth,'-') << endl << endl; // Format
    	if(_event.months){
			cout << _event.name << " is going on for " << _event.months << " months!" << endl;
			if(_event.name=="Economic boom") cout << "All jobs pay more. Items will be more expensive." << endl << endl;
			else if(_event.name=="Recession") cout << "All jobs pay less. Items will be cheaper." << endl << endl;
		}
		
		for(int i=0;i<artHeight;i++){ // Sprite
        	for(int j=0;j<(artOffset+artWidth);j++){
            	if(j<artOffset)
                	cout << ' ';
            	else
                	cout << asciiArt[(kidState==JAIL ? TIRED : kidState)][i][j-artOffset];
        	}
	        cout << endl;
    	}
		cout << endl << kidScript[kidState] << endl << endl // Monthly script
    	     << "Year" << curYear << ' ' << monthName[curMonth] << ' ' << string((screenWidth-8/*Year&Month*/-4/*' '*2+" $"*/-to_string(cur.money).length()),'-') << " $" << cur.money << endl // Status
         	 << "(Q) Talk | (W) Plan The Month | (E) Status | (R) Inventory | (T) Shop" << endl; // UI instructions
		if(cur.jailed) cout << "(A) Bribe" << endl;
	    cout << string(screenWidth,'-') << endl; // Format
    	cin >> uiInput;
        if(uiInput>90) uiInput-=32; // Uppercase
        switch(uiInput){
            case('Q'):{
				if(flag[TALK]) cout << endl << "You already talked with " << cur.name << " this month." << endl << endl;
				else flag[TALK] = talk(); // Talk with the kid.
				break;
            } case('W'):{
				do{
					// Note: cur.jailed stays 0, but plan() thinks kid is jailed anyway.
					monthPlan = plan(cur.jailed);
					string result = monthPlan[2].getInfo().name;

					if(result=="Quit")
						flag[PLAN] = true; // Quit
					else if(result!="Unknown"){
						 work(monthPlan); // Work
						 monthEnd = true;
						 flag[PLAN] = true;
					}

					delete [] monthPlan;
				} while(!flag[PLAN]);

				flag[PLAN] = false;
				break;
            } case('E'):{
                status();
                break;
            } case('R'):{
                do flag[INVEN] = inventory();
				while(!flag[INVEN]);
				flag[INVEN] = false;
                break;
            } case('T'):{
                do flag[SHOP] = shop();
				while(!flag[SHOP]);
				flag[SHOP] = false;
                break;
			} case('A'):{
				bribe();
				break;
            } default:
                continue;
        } // switch(uiInput)
    } while(!monthEnd);
}

void RoundUI::roundEnd(int curYear,int curMonth){
    StatStruct curStats = _tempStat.getStatus();
	int offset = 0;
	bool flag = false;
	string strNum[4] = {
		to_string(abs(curStats.moral)),
		to_string(abs(curStats.favor)),
		to_string(abs(curStats.money)),
		to_string(abs(curStats.emotion))};

	// Add the temp values to the main values.
	_kid.addValues(_tempStat);

	// A summary of this month's money and kid's values should be printed at the end of the month.
    for(int i=0;i<resultHeight;i++){
		offset = 0; // Reset offset
		flag = false; // Reset flag
        for(int j=0;j<resultWidth;j++){
            if(monthResult[i][j]=='x'){ // Replace placeholder
                switch(i){
                    case(2):{ // Year & Month
                        if(offset==0){
						   	cout << curYear;
							offset++;
						}else{
							cout << monthName[curMonth][--offset];
							offset += 2;
						} break;
                    }case(5):{ // Moral
                        if(offset>3||strNum[0][offset]<'0'||strNum[0][offset]>'9')
							cout << ' ';
                        else if(!flag){
							cout << (curStats.moral>=0 ? '+' : '-');
							flag = true;
						} else cout << strNum[0][offset++];
						break;
                    }case(7):{ // Favor
                        if(offset>3||strNum[1][offset]<'0'||strNum[1][offset]>'9')
                            cout << ' ';
                        else if(!flag){
						   	cout << (curStats.favor>=0 ? '+' : '-');
							flag = true;
						} else cout << strNum[1][offset++];
						break;
                    }case(9):{ // Money
						if(offset>3||strNum[2][offset]<'0'||strNum[2][offset]>'9')
							cout << ' ';
						else if(!flag){
							cout << (curStats.money>=0 ? '+' : '-');
							flag = true;
						} else cout << strNum[2][offset++];
                        break;
					}case(11):{ // Emotion
						if(offset>3||strNum[3][offset]<'0'||strNum[3][offset]>'9')
							cout << ' ';
						else if(!flag){
							cout << (curStats.emotion>=0 ? '+' : '-');
							flag = true;
						} else cout << strNum[3][offset++];
						break;
					}case(15):{ // Monthly summary & advices
						char output;
                        if(_kid.getStatus().jailed) output = monthAdvice[M_JAIL][offset++];
                        else if(_kid.getStatus().emotion<emotionSwitchMonth) output = monthAdvice[M_TIRED][offset++];
                        else if(_kid.getStatus().money<moneySwitchMonth) output = monthAdvice[M_POOR][offset++];
                        else output = monthAdvice[M_NORMAL][offset++];

                        if(output) cout << output;
                        else cout << ' ';
                        break;
                    } default:
                        cout << monthResult[i][j];
                } // switch(i)
            } else cout << monthResult[i][j];
		} // for(j)
		cout << endl;
    } // for(i)
}

bool RoundUI::talk(){
    cout << "(1) I love you. | (2) I hate you." << endl;
	int kidFavor = T_NORMAL;
	if(_kid.getStatus().jailed) kidFavor = T_JAIL;
	else if(_kid.getStatus().favor>50) kidFavor = T_LOVE;
	else if(_kid.getStatus().favor<-50) kidFavor = T_HATE;

	int numInput;
    cin >> numInput;
    switch(numInput){
        case(1):{
            cout << kidTalkLove[kidFavor] << endl;
            _tempStat.talk(true);
            return true;
        }case(2):{
            cout << kidTalkHate[kidFavor] << endl;
            _tempStat.talk(false);
            return true;
        }default:
            return false;
    }
}


Work* RoundUI::plan(bool jailed){
	PlanManager pManager;
	vector<Work> allWorks = pManager.getWork();
	Work* monthPlan = new Work[3];
	int numInput = 0;
	int planOffset = 0;

	if(jailed){
		for(int i=0;i<3;i++)
			monthPlan[i] = Work(allWorks[0]); // Jailed for the month
		cout << endl << _kid.getStatus().name << " is in jail for this month." << endl;
	}else{
		cout << endl << "What should " << _kid.getStatus().name << " do for this month?" << endl;

		for(int plans=0;plans<3;plans++){
    		for(int i=1;i<int(allWorks.size());i++){
        		cout << endl << '(' << i << ") " << allWorks[i].getInfo().name;
			} cout << endl << endl << "Current plans:" << endl; // Format
			for(int i=0;i<3;i++){
				if(monthPlan[i].getInfo().name=="Unknown") cout << "(Nothing yet)" << endl;
				else cout << monthPlan[i].getInfo().name << endl;
			}
			//cout << endl << endl << "(Q) Quit" << endl << endl;
    		cin >> numInput;
			//if(numInput=='Q'){ // Quit
			//	monthPlan[2] = Work("Quit",0,0);
			//	return monthPlan;
			/*} else */
			if(numInput<=int(allWorks.size())){
				WorkStruct work = allWorks[numInput].getInfo();
				cout << endl << work.name << endl;
				if(work.name!="Rest"){
					cout << "Money +";
					if(_event.name=="Economic boom") cout << work.money*1.25 << endl;
					else if(_event.name=="Recession") cout << work.money*0.75 << endl;
					else cout << "Money +" << work.money << endl;
				}
				cout << "Emotion: " << (work.name=="Rest" ? "+25" : "-5") << endl; // Currently, all work minus emotion by 5.
				if(work.moral!=0)
					cout << "Moral: " << (work.moral>0 ? "+" : "") << work.moral;
				cout << endl << "(0) Plan | (1) Return & Reset" << endl; // In progress: Fix return.
				int numInput2;
				cin >> numInput2;
				if(numInput2==0)
					monthPlan[planOffset++] = Work(allWorks[numInput]);
				else if(numInput2==1)
					return monthPlan; // Do plan() again.
			}
		}
	}

	cout << endl << endl << "Plan for the month:" << endl;
	for(int i=0;i<3;i++)
		cout << monthPlan[i].getInfo().name << endl;
	cout << endl << "(0) Done | (1) Reset" << endl;
	do{
		cin >> numInput;
		if(numInput==0)
			return monthPlan; // Start working according to monthPlan.
		else if(numInput==1){
			for(int i=0;i<3;i++)
				monthPlan[i] = {"Unknown",0,0};
			return monthPlan; // Do plan() again.
		}
	} while(true);
}

void RoundUI::work(Work* plan){
	cout << endl << string(screenWidth,'-') << endl << endl; // Format
	// If the kid is in jail, you don't have to pay for food.
	if(_kid.getStatus().jailed) _kid.stayInJail();
	else cout << "Food money for the month" << endl << "Money -50" << endl << endl;
	for(int i=0;i<3;i++){
		_tempStat.goToWork(_kid.getStatus().name,plan[i],_event.name);
		sleep(1);
	}
}

void RoundUI::status(){
	StatStruct curStats = _kid.getStatus();
	int offset = 0;
	bool offsetFlag = false;
	string strNum[4] = {
		to_string(curStats.moral),
		to_string(curStats.favor),
		to_string(curStats.money),
		to_string(curStats.emotion)};
    
	for(int i=0;i<resultHeight;i++){
		offset = 0; // Reset offset
        for(int j=0;j<resultWidth;j++){
            if(statResult[i][j]=='x'){ // Replace placeholder
                switch(i){
					case(2):{ // Kid's name
						if(offset>int(curStats.name.size())){
							if(!offsetFlag){
								cout << "  ";
								offsetFlag = true;
							} else cout << ' ';
						} else
							cout << curStats.name[offset++];
                        break;
                    }case(5):{ // Moral
						if(offset>4||((strNum[0][offset]<'0'||strNum[0][offset]>'9')&&strNum[0][offset]!='-'))
							cout << ' ';
						else cout << strNum[0][offset++];
                        break;
                    }case(7):{ // Favor
                        if(offset>4||((strNum[1][offset]<'0'||strNum[1][offset]>'9')&&strNum[1][offset]!='-'))
							cout << ' ';
						else cout << strNum[1][offset++];
                        break;
                    }case(9):{ // Money // Note: Slight offset
                        if(offset>4||((strNum[2][offset]<'0'||strNum[2][offset]>'9')&&strNum[2][offset]!='-'))
							cout << ' ';
						else cout << strNum[2][offset++];
                        break;
					}case(11):{ // Emotion
						if(offset>4||((strNum[3][offset]<'0'||strNum[3][offset]>'9')&&strNum[3][offset]!='-'))
							cout << ' ';
						else cout << strNum[3][offset++];
						break;
                    }case(15):{ // Monthly summary & advices
						char output;
						if(curStats.jailed) output = monthAdvice[M_JAIL][offset++];
                        else if(curStats.emotion<emotionSwitchMonth) output = monthAdvice[M_TIRED][offset++];
                        else if(curStats.money<moneySwitchMonth) output = monthAdvice[M_POOR][offset++];
                        else output = monthAdvice[M_NORMAL][offset++];

						if(output) cout << output;
						else cout << ' ';
						break;
                    } default:
                        cout << statResult[i][j];
                } // switch(i)
            } else cout << statResult[i][j];
        } // for(j)
		cout << endl;
    } // for(i)	
}

bool RoundUI::inventory(){
	// Show inventory and UI
	ItemManager iManager;
	vector<Item> curPack = iManager.getInventory();
	cout << endl << string(screenWidth,'-') << endl << endl // Format
		 << "Inventory" << endl;
	if(curPack.empty()) cout << endl << "Nothing in inventory!";
	else{
		for(int i=0;i<int(curPack.size());i++)
			cout << endl << '(' << i+1 << ") " << curPack[i].getInfo().name;
    	cout << endl << "(Q) Quit" << endl << endl;
		char numInput;
		cin >> numInput;
		if(numInput=='Q') return true; // Quit
		numInput-='0';
		numInput--;
        if(numInput<=int(curPack.size())){
			ItemStruct item = curPack[numInput].getInfo();
			cout << endl << item.name << endl
			     << item.desc << endl
				 << "Emotion: +" << item.emotion << endl;
			if(item.moral!=0)
				cout << "Moral: " << (item.moral>0 ? "+" : "") << item.moral;
            cout << endl << "(0) Use | (1) Return" << endl;
			int numInput2;
			cin >> numInput2;
			if(numInput2==0){
				iManager.useItem(numInput,_tempStat);
				cout << "Used " << item.name << "!" << endl
					 << _kid.getStatus().name << " appreciate your gift." << endl
					 << "Favor +5" << endl; // Currently, every gift raises favor by 5.
				return true; // Done.
			}else if(numInput2==1)
				return false; // Do inventory() again.
		}
	} return true;
}

bool RoundUI::shop(){
    // Show shop and UI
    ItemManager iManager;
    vector<Item> curShop = iManager.getShop();
    cout << endl << string(screenWidth,'-') << endl << endl // Format
         << "Shop" << endl;
    if(curShop.empty()) cout << endl << "Nothing in shop!";
    else{
        for(int i=0;i<int(curShop.size());i++)
            cout << endl << '(' << i+1 << ") " << curShop[i].getInfo().name;
        cout << endl << "(Q) Quit" << endl << endl;
        char numInput;
        cin >> numInput;
        if(numInput=='Q') return true; // Quit
        numInput-='0';
        numInput--;
        if(numInput<=int(curShop.size())){
            ItemStruct item = curShop[numInput].getInfo();
            cout << endl << item.name << endl
                 << item.desc << endl
                 << "Emotion: +" << item.emotion << endl;
            if(item.moral!=0)
                cout << "Moral: " << (item.moral>0 ? "+" : "") << item.moral << endl;
			cout << "Cost $";
			if(_event.name=="Economic boom") cout << item.money*1.25 << endl;
			else if(_event.name=="Recession") cout << item.money*0.75 << endl;
            cout << endl << "(0) Buy | (1) Return" << endl;
            int numInput2;
            cin >> numInput2;
            if(numInput2==0){
                 iManager.buyItem(numInput,_tempStat,_event.name);
                 cout << "Bought " << item.name << "!" << endl;
                return true; // Done.
            }else if(numInput2==1)
                return false; // Do shop() again.
        }
    } return true;
}

void RoundUI::bribe(){
	StatStruct cur = _kid.getStatus();
	cout << "You can choose to pay $" << cur.jailed*100 << " to immediately bring " << cur.name << " home." << endl
		 << endl << "(0) Pay | (1) Return" << endl << endl;
	int numInput;
	cin >> numInput;
	if(numInput==0){
		if(cur.money<cur.jailed*100)
			cout << "You don't have enough money." << endl << endl;
		else{
			_kid.outOfJail();
			cout << cur.name << " is no longer being jailed." << endl << endl;
		}
	}
	return;
}
