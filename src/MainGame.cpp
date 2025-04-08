/* ----- Introduction -----
 *
 * The game lasts for a year.
 * On each Month's first day, the player can
 * (1) Buy things for the kid.
 * (2) Plan the kid's work for this month.
 * 
 * In short, there are 12 rounds before the ending.
 * The kid's moral, favor and money values will decide the ending.
 * There are 8 endings in total.
 *
 * ----- Monthly Expense -----
 *
 * The kid needs food to survive.
 * If there's no money to buy food for the month, it's game over.
 * Therefore, working is essential.
 *
 * ----- Emotion Bar -----
 *
 * Keep an eye on the kid's emotion bar.
 * If it's too low, the kid will refuse to work.
 * You can buy gifts for the kid to be happier.
 * Or, you can let the kid rest for this month.
 *
 * ----- Jail -----
 *
 * Bad works are risky.
 * The kid might get caught and get jailed.
 * The player can get them back by paying a huge amount of money.
 * Else, the kid will stay in jail for months and cannot work or rest.
*/

#include <iostream>
#include <array>
#include <string>
#include "Status.h"
#include "Item.h"
#include "AsciiSprite.h"
using namespace std;

Kid YourKid;
ItemManager IManager;
string playerName = "Player";
const int screenWidth = 69; // For UI formatting.
const int artOffset = 30; // For UI formatting.

const int foodMoney = 50; // Monthly expense. Essential to pay for survival.
const int moneySwitch = 500; // < switch: Bad, > switch: Good
const int moralSwitch = 0; // Moral: -100 ~ 100
const int favorSwitch = 0; // Favor: -100 ~ 100
enum endings {STARVE,GGG,BGG,GBG,GGB,BBG,BGB,GBB,BBB}; // MoralMoneyFavor

int numInput = 0;
void Talk(Kid& kid);
void Plan(Kid& kid);
void Inventory();
void Shop();
void roundEnd(int curYear,int curMonth);
void ending(int end);

void Round(int curYear,int curMonth){

	StatStruct cur = YourKid.getStatus();
	int kidArt = NORMAL;
	if(cur.emotion<50) kidArt = TIRED;
	else if(cur.moral>50) kidArt = GOOD;
	else if(cur.moral<-50) kidArt = BAD;

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
	char uiInput;
	do{
		cin >> uiInput;
		switch(uiInput){
			case('Q'):{
				Talk(YourKid); // Talk with the kid. Response varies depending on moral & emotion.
				break;
			} case('W'):{
				// In progress: Plan() - Plan the month and start Work()
				break;
			} case('E'):{
				// In progress: Status() - Shows the character's status.
				break;
			} case('R'):{
				// In progress: Inventory() - Shows the inventory and allows using items.
				break;
			} case('T'):{
				// In progress: Shop() - Shows the shop and allows buying items
				break;
			} default:
				continue;
		}
	} while(1);

	roundEnd(curYear,curMonth);

}

void roundEnd(int curYear,int curMonth){
	StatStruct curStats = YourKid.getStatus();
	if(curStats.money < foodMoney){
		ending(STARVE);
		return;
	} else{
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
	} // if
}

void Talk(Kid& kid){
	cout << "(1) I love you. | (2) I hate you." << endl;
	cin >> numInput;
	switch(numInput){
		case(1):{
			cout << "Your kid seems happy with your words!" << endl
				 << "Favor +5" << endl;
			kid.talk(true);
			break;
		}case(2):{
			cout << "Your kid seems sad..." << endl
				 << "Favor -5" << endl;
			kid.talk(false);
			break;
		}default:
			return;
	}
}

void Plan(Kid& kid){
	cout << endl << "What should" << kid.getStatus().name << "do for this month?" << endl;
	for(int i=1;i<workVec.size()+1;i++){
		cout << '(' << i << ") " << workVec[i-1] << endl;
	cout << endl << "(0) Done" << endl;
	cin >> numInput;
	if(numInput==0) return; // In progress: Start working according to monthPlan(arr).
	else if(numInput<=workVec.size()) return; // In progress: Record the plan in monthPlan(arr).
	else return;
}

int endCoding(int money,int moral,int favor){
	// Decide the ending code
	array<bool,3> endBool = {money>=moneySwitch,moral>=moralSwitch,favor>=favorSwitch};
	if(endBool==array<bool,3>{true,true,true}) return GGG;
	else if(endBool==array<bool,3>{false,true,true}) return BGG;
	else if(endBool==array<bool,3>{true,false,true}) return GBG;
	else if(endBool==array<bool,3>{true,true,false}) return GGB;
	else if(endBool==array<bool,3>{false,false,true}) return BBG;
	else if(endBool==array<bool,3>{false,true,false}) return BGB;
	else if(endBool==array<bool,3>{true,false,false}) return GBB;
	else return BBB;
}

void ending(int endCode){
	string name = YourKid.getStatus().name;
	switch(endCode){ // In progress: 9 endings based on moral, money and favor in order
		case(STARVE):{ // Ending(0): Starved
			cout << "The money wasn't enough to pay for " << name << "'s meals..." << endl
				 << "\"" << playerName << ", I'm so... hungry...\"" << endl
			     << name << " died from starvation." << endl;
			break;
		}case(GGG):{ // Ending(1): Happily ever after
			cout << name << " has been working hard. They have saved quite the amount of money." << endl
				 << "With all the money," << name << " bought a beautiful place for you both to live in." << endl << endl
				 << "\"" << playerName << ", thank you so much for raising me.\"" << endl
				 << "You and " << name << " live a peaceful, happy life ever after." << endl << endl
				 << "Ending(1): Happily ever after" << endl;
			break;
		}case(BGG):{ // Ending(2): Mafia gang for you
			// In progress
			break;
		}case(GBG):{ // Ending(3): Life is difficult but happy
			// In progress
			break;
		}case(GGB):{ // Ending(4): May we never meet again
			// In progress
			break;
		}case(BBG):{ // Ending(5): Got my hands dirty for you
			// In progress
			break;
		}case(BGB):{ // Ending(6): Erased
			// In progress
			break;
		}case(GBB):{ // Ending(7): Suicide/Escaped
			// In progress
			break;
		}case(BBB):{ // Ending(8): It's all for my sake
			cout << "After a year, " << name << " comes to you." << endl << endl
				 << "\"You are so much richer than me, right?\"" << endl
				 << "\"You kept all your money to yourself and let me do the dirty work, right?\"" << endl
				 << "\"Then, it's only natural...\"" << endl << endl
				 << "\"Goodbye, you f*cking bastard.\"" << endl << endl
				 << "What have you done?" << endl << endl
				 << "Ending(8): It's all for my sake" << endl;
		}
	}
}

int main(){
	// Game start
	string kidName;
	cout << "Please enter your kid's name: ";
	cin >> kidName;
	YourKid.setName(kidName);
	cout << "Please enter how " << kidName << " should call you: ";
	cin >> playerName;
	for(int round=0;round<24;round++)
		Round(round/12,round%12);
	StatStruct end = YourKid.getStatus();
	int endCode = endCoding(end.moral,end.money,end.favor);
	ending(endCode);
	return 0;
}
