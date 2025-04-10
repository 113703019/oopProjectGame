#include <iostream>
#include <vector>
#include "RoundUI.h"
#include "Status.h"
#include "AsciiSprite.h"

RoundUI::RoundUI(string name){
	_kid.setName(name);
}

void RoundUI::round(int curYear,int curMonth){

    StatStruct cur = _kid.getStatus();
    int kidArt = NORMAL;
    if(cur.emotion<50) kidArt = TIRED;
    else if(cur.moral>50) kidArt = GOOD;
    else if(cur.moral<-50) kidArt = BAD;
	
	char uiInput;
	bool talkFlag = false; // You can only talk to the kid once every month.
	do{
    	cout << endl << string(screenWidth,'-') << endl << endl; // Format
    	for(int i=0;i<artHeight;i++){ // Sprite
        	for(int j=0;j<(artOffset+artWidth);j++){
            	if(j<artOffset)
                	cout << ' ';
            	else
                	cout << asciiArt[kidArt][i][j-artOffset];
        	}
	        cout << endl;
    	}
	    cout << endl << cur.name << ": \"Hello! What should I do this month?\"" << endl << endl // Temporary script
    	     << "Year" << curYear << ' ' << monthName[curMonth] << ' ' << string((screenWidth-8/*Year&Month*/-4/*' '*2+" $"*/-to_string(cur.money).length()),'-') << " $" << cur.money << endl // Status
         	 << "(Q) Talk | (W) Plan The Month | (E) Status | (R) Inventory | (T) Shop" << endl // UI instructions
	         << string(screenWidth,'-') << endl; // Format
    	cin >> uiInput;
        if(uiInput>90) uiInput-=32; // Uppercase
        switch(uiInput){
            case('Q'):{
				if(talkFlag) cout << endl << "You already talked with " << cur.name << " this month." << endl << endl;
				else talkFlag = talk(); // Talk with the kid. Response varies depending on moral & emotion.
				break;
            } case('W'):{
                // In progress: plan() - Plan the month and start Work()
                break;
            } case('E'):{
                // In progress: status() - Shows the character's status.
                break;
            } case('R'):{
                // In progress: inventory() - Shows the inventory and allows using items.
                break;
            } case('T'):{
                // In progress: shop() - Shows the shop and allows buying items
                break;
            } default:
                continue;
        }
    } while(1);

    roundEnd(curYear,curMonth);

}

void RoundUI::roundEnd(int curYear,int curMonth){
    StatStruct curStats = _kid.getStatus();
    
	// A summary of this month's money and kid's values should be printed at the end of the month.
    int offset = 0;
    for(int i=0;i<resultHeight;i++){
        for(int j=0;j<resultWidth;j++){
            if((i!=9 && offset>=2) || (i==9 && offset>=3)) offset = 0; // Reset offset
            if(monthResult[i][j]=='x'){ // Replace placeholder
                switch(i){
                    case(2):{ // Year & Month
                        if(offset==0)
                            monthResult[i][j] = curYear;
                        else
                            monthResult[i][j] = monthName[curMonth][offset++];
                        break;
                    }case(5):{ // Moral
                        if(offset==0)
                            monthResult[i][j] = curStats.moral>0 ? '+' : '-';
                        else
                            monthResult[i][j] = curStats.moral%(2-(offset++));
                        break;
                    }case(7):{ // Favor
                        if(offset==0)
                            monthResult[i][j] = curStats.favor>0 ? '+' : '-';
                        else
                            monthResult[i][j] = curStats.favor%(2-(offset++));
                        break;
                    }case(9):{ // Money
                        if(offset==0)
                            monthResult[i][j] = curStats.money>0 ? '+' : '-';
                        else
                            monthResult[i][j] = curStats.money%(3-(offset++));
                        break;
                    } default:
                        continue;
                } // switch(i)
            } // if(monthResult[i][j])
            cout << monthResult[i][j];
		} // for(j)
    } // for(i)
}

bool RoundUI::talk(){
    cout << "(1) I love you. | (2) I hate you." << endl;
	int numInput;
    cin >> numInput;
    switch(numInput){
        case(1):{
            cout << "Your kid seems happy with your words!" << endl
                 << "Favor +5" << endl;
            _kid.talk(true);
            return true;
        }case(2):{
            cout << "Your kid seems sad..." << endl
                 << "Favor -5" << endl;
            _kid.talk(false);
            return true;
        }default:
            return false;
    }
}


void RoundUI::plan(){
	PlanManager pManager;
	vector<Work> allWorks = pManager.getWork();
	Work monthPlan[3];
    cout << endl << "What should" << _kid.getStatus().name << "do for this month?" << endl;
    for(int i=1;i<int(allWorks.size())+1;i++){
        cout << '(' << i << ") " << allWorks[i-1].getInfo().name << endl;
	    cout << endl << "(0) Done" << endl;
		int numInput = 0;
    	cin >> numInput;
    	int planOffset = 0;
    	while(true){
        	if(numInput==0)
            	return; // In progress: Start working according to monthPlan(arr).
	        else if(numInput<=int(allWorks.size()))
				return; // monthPlan[planOffset++] = /* The work */;
        	else return;
		}
    }
}

void RoundUI::inventory(){

}

void RoundUI::shop(){

}
