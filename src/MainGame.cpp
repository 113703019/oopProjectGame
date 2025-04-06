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
#include "Status.h"
#include "Item.h"
using namespace std;

Kid YourKid;
ItemManager IManager;
string playerName = "Player";
const int foodMoney = 50; // Monthly expense. Essential to pay for survival.
const int moneySwitch = 500; // < switch: Bad, > switch: Good
const int moralSwitch = 0;
const int favorSwitch = 0;
enum endings {STARVE,GGG,BGG,GBG,GGB,BBG,BGB,GBB,BBB}; // MoralMoneyFavor

void Talk();
void Work();
void Plan();
void Inventory();
void Shop();
void roundEnd(int curMonth);

void Round(int curMonth){

	StatStruct cur = YourKid.getStatus();
	cout << cur.name << ": \"Hello! What should I do this month?\"" << endl << endl /* Temporary script*/
		 << monthName[curMonth] << ' ' << cur.money << "                        " << cur.emotion << ' ' << cur.moral << endl /* Status */
	 	 << "(Q) Talk | (W) Plan The Month | (E) Inventory | (R) Shop" << std::endl; // UI instructions
	char uiInput;
	do{
		cin >> uiInput;
		switch(uiInput){
			case('Q'):{
				// In progress: Talk() - Talk with the kid. Response varies depending on moral & emotion.
				break;
			} case('W'):{
				// In progress: Plan() - Plan the month and start Work()
				break;
			} case('E'):{
				// In progress: Inventory() - Shows the inventory and allows using items.
				break;
			} case('R'):{
				// In progress: Shop() - Shows the shop and allows buying items
				break;
			} default:
				continue;
		}
	} while(1);

	roundEnd(curMonth);

}

void ending(int end);

void roundEnd(int curMonth){
	StatStruct curStats = YourKid.getStatus();
	if(curStats.money < foodMoney){
		ending(STARVE);
		return;
	} else{
		// In progress: A summary of this month's money and kid's values should be printed at the end of the month.
		int offset = 0;
		for(int i=0;i<resultHeight;i++){
			for(int j=0;j<resultWidth;j++){
				if((i!=9 && offset>=2) || (i==9 && offset>=3)) offset = 0; // Reset offset
				if(monthResult[i][j]=='x'){ // Replace placeholder
					switch(i){
						case(2):{ // Month
							monthResult[i][j] = monthName[curMonth][offset++];
							break;
						}case(5):{ // Moral
							if(offset==0)
								monthResult[i][j] = curStats.moral>0 ? '+' : '-';
							else
								monthResult[i][j] = curStats.moral%(2-(offset++));
							break;
						}case(7):{ // Favor
							// Favorbility in progress...
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
	for(int round=0;round<12;round++)
		Round(round);
	StatStruct end = YourKid.getStatus();
	int endCode = endCoding(end.moral,end.money,1/* In progress: end.favor */);
	ending(endCode);
	return 0;
}
