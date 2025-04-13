#include <iostream>
#include <vector>
#include <string>

#include "RoundUI.h"
#include "Status.h"
#include "Item.h"
#include "AsciiSprite.h"

RoundUI::RoundUI(string name){
	_kid.setName(name);
}

void RoundUI::round(int curYear,int curMonth){

    StatStruct cur = _kid.getStatus();
    int kidState = NORMAL;
    if(cur.emotion<50) kidState = TIRED;
	else if(cur.moral>50) kidState = GOOD;
    else if(cur.moral<-50) kidState = BAD;
	
	char uiInput;
	enum flag {TALK,INVEN};
	bool flag[2] = {false};
	_tempStat.resetTemp();
	Work* monthPlan = new Work[3];
	
	bool monthEnd = false;
	do{
    	cout << endl << string(screenWidth,'-') << endl << endl; // Format
    	for(int i=0;i<artHeight;i++){ // Sprite
        	for(int j=0;j<(artOffset+artWidth);j++){
            	if(j<artOffset)
                	cout << ' ';
            	else
                	cout << asciiArt[kidState][i][j-artOffset];
        	}
	        cout << endl;
    	}
		cout << endl << kidScript[kidState] << endl << endl // Monthly script
    	     << "Year" << curYear << ' ' << monthName[curMonth] << ' ' << string((screenWidth-8/*Year&Month*/-4/*' '*2+" $"*/-to_string(cur.money).length()),'-') << " $" << cur.money << endl // Status
         	 << "(Q) Talk | (W) Plan The Month | (E) Status | (R) Inventory | (T) Shop" << endl // UI instructions
	         << string(screenWidth,'-') << endl; // Format
    	cin >> uiInput;
        if(uiInput>90) uiInput-=32; // Uppercase
        switch(uiInput){
            case('Q'):{
				if(flag[TALK]) cout << endl << "You already talked with " << cur.name << " this month." << endl << endl;
				else flag[TALK] = talk(); // Talk with the kid.
				break;
            } case('W'):{
				do monthPlan = plan(cur.jailed);
				while(monthPlan[2].getInfo().name=="Unknown");
				work(monthPlan);
				delete [] monthPlan;
				monthEnd = true;
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
                // In progress: shop() - Shows the shop and allows buying items
                break;
            } default:
                continue;
        }
    } while(!monthEnd);
}

void RoundUI::roundEnd(int curYear,int curMonth){ // In progress: This shit's so broken. Fix it.
    StatStruct curStats = _tempStat.getStatus();
	int offset = 0;
	string strNum[3] = {to_string(curStats.moral),to_string(curStats.favor),to_string(curStats.money)};
    
	// Add the temp values to the main values.
	_kid.addValues(_tempStat);

	// A summary of this month's money and kid's values should be printed at the end of the month.
    for(int i=0;i<resultHeight;i++){
		offset = 0; // Reset offset
        for(int j=0;j<resultWidth;j++){
            if(monthResult[i][j]=='x'){ // Replace placeholder
                switch(i){
                    case(2):{ // Year & Month
                        if(offset==0) cout << curYear;
                        else cout << monthName[curMonth][offset++];
                        break;
                    }case(5):{ // Moral
                        if(offset>2||strNum[0][offset]<'0'||strNum[0][offset]>'9')
							cout << ' ';
                        else if(offset==0)
                            cout << (curStats.moral>0 ? "+" : "");
						else cout << strNum[0][offset++];
                        break;
                    }case(7):{ // Favor
                        if(offset>2||strNum[1][offset]<'0'||strNum[1][offset]>'9')
                            cout << ' ';
                        else if(offset==0)
							cout << (curStats.favor>0 ? "+" : "");
                    	else cout << strNum[1][offset++];
                        break;
                    }case(9):{ // Money
						if(offset>3||strNum[2][offset]<'0'||strNum[2][offset]>'9')
							cout << ' ';
						else if(offset==0)
                            cout << (curStats.money>0 ? "+" : "");
                        else cout << strNum[2][offset++];
                        break;
					}case(13):{ // Monthly summary & advices
						char output;
                        if(_kid.getStatus().jailed) output = monthAdvice[M_JAIL][offset++];
                        else if(curStats.emotion<emotionSwitchMonth) output = monthAdvice[M_TIRED][offset++];
                        else if(curStats.money<moneySwitchMonth) output = monthAdvice[M_POOR][offset++];
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
	if(_kid.getStatus().favor>50) kidFavor = T_LOVE;
	else if(_kid.getStatus().favor<-50) kidFavor = T_HATE;

	int numInput;
    cin >> numInput;
    switch(numInput){
        case(1):{
            cout << kidTalkLove[kidFavor] << endl
                 << "Favor +5" << endl;
            _tempStat.talk(true);
            return true;
        }case(2):{
            cout << kidTalkHate[kidFavor] << endl
                 << "Favor -5" << endl;
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
    		cin >> numInput;
        	if(numInput<=int(allWorks.size()))
				monthPlan[planOffset++] = Work(allWorks[numInput]);
		}
	}

	cout << endl << endl << "Plan for the month:" << endl;
	for(int i=0;i<3;i++)
		cout << monthPlan[i].getInfo().name << endl;
	cout << endl << "(0) Done | (1) Reset" << endl;
	cin >> numInput;
	if(numInput==0)
		return monthPlan; // Start working according to monthPlan.
	else if(numInput==1){
		for(int i=0;i<3;i++)
			monthPlan[i] = {"Unknown",0,0};
	}	
	return monthPlan; // Do plan() again.
}

void RoundUI::work(Work* plan){
	for(int i=0;i<3;i++)
		_tempStat.goToWork(_kid.getStatus().name,plan[i]);

}

void RoundUI::status(){
	StatStruct curStats = _kid.getStatus();
	int offset = 0;
	string strNum[3] = {to_string(curStats.moral),to_string(curStats.favor),to_string(curStats.money)};
    for(int i=0;i<resultHeight;i++){
		offset = 0; // Reset offset
        for(int j=0;j<resultWidth;j++){
            if(statResult[i][j]=='x'){ // Replace placeholder
                switch(i){
					case(2):{ // Kid's name
						// In progress: Slight offset needed
						if(offset>int(curStats.name.size())) cout << ' ';
                        else cout << curStats.name[offset++];
                        break;
                    }case(5):{ // Moral
						if(offset>4||strNum[0][offset]<'0'||strNum[0][offset]>'9')
							cout << ' ';
						else cout << strNum[0][offset++];
                        break;
                    }case(7):{ // Favor
                        if(offset>4||strNum[1][offset]<'0'||strNum[1][offset]>'9')
							cout << ' ';
						else cout << strNum[1][offset++];
                        break;
                    }case(9):{ // Money
                        if(offset>4||strNum[2][offset]<'0'||strNum[2][offset]>'9')
							cout << ' ';
						else cout << strNum[2][offset++];
                        break;
                    }case(13):{ // Monthly summary & advices
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
    	cout << endl << endl << "(Q) Quit" << endl << endl;
		int numInput;
		cin >> numInput;
		if(numInput=='Q') return true;
		else numInput--;
        if(numInput<=int(curPack.size())){
			ItemStruct item = curPack[numInput].getInfo();
			cout << item.name << endl
			     << item.desc << endl
				 << "Emotion: +" << item.emotion << endl;
			if(item.moral!=0)
				cout << "Moral: " << (item.moral>0 ? "+" : "") << item.moral;
            cout << endl << "(0) Use | (1) Return" << endl;
			int numInput2;
			cin >> numInput2;
			if(numInput2==0){
				iManager.useItem(numInput,_tempStat);
				cout << "Used " << item.name << "!" << endl;
				return true; // Done.
			}else if(numInput2==1)
				return false; // Do inventory() again.
		}
	} return true;
}

void RoundUI::shop(){

}
