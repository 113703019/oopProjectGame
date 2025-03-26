/* ----- Introduction -----
 *
 * The game lasts for a year.
 * On each Month's first day, the player can
 * (1) Buy things for the kid.
 * (2) Plan the kid's work for this month.
 * 
 * In short, there are 12 rounds before the ending.
 * The kid's moral value will decide the ending.
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
*/

#include <iostream>
#include "Status.h"
using namespace std;

Kid YourKid;
string playerName = "Player";
const foodMoney = 50; // Monthly expense. Essential to pay for survival.
enum endings = {STARVE,GOOD,NEUTRAL,BAD};

void Talk();
void Work();
void Plan();
void Inventory();
void Shop();
void roundEnd();

void Round(int curMonth){

	cout << YourKid.getStatus().name << ": \"Hello! What should I do this month?\"" << endl << endl /* Temporary script*/
		 << month[curMonth] << ' ' << YourKid.getStatus().money << "                        " << YourKid.getStatus().emotion << ' ' << YourKid.getStatus().moral << endl; /* Status */
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
	} while(1)

	roundEnd();

}

void roundEnd(){
	if(YourKid.getStatus().money < foodMoney){
		cout << "The money wasn't enough to pay for " << YourKid.getStatus().name << "'s meals..." << endl
			 << YourKid.getStatus().name << " died from starvation." << endl;
		// In progress: gameOver(STARVE);
		return;
	}
	// In progress: A summary of this month's money and kid's values should be printed at the end of the month.
}

void ending(int end){
	string name = YourKid.getStatus().name;
	switch(end){
		case(STARVE):{
			cout << "The money wasn't enough to pay for " << name << "'s meals..." << endl
				 << "\"" << playerName << ", I'm so... hungry...\"" << endl
			     << name << " died from starvation." << endl;
			break;
		} case(GOOD):{
			cout << name << " has been dilligently working throughout the year." << endl
				 << "It's time for them to move out and live their own life." << endl << endl
				 << "\"Goodbye, " << playerName << "! I love you!\"" << endl
				 << "Thank you so much for raising me!" << endl;
			break;
		} case(NEUTRAL):{
			cout << name << " feels conflicted." << endl
				 << "\"Is anything acceptable for the sake of money?\"" << endl
				 << "Guess it's now their job to figure that out."
		} case(BAD):{
			cout << "After a year, " << name << " comes to you." << endl << endl
				 << "\"You are so much richer than me, right?\"" << endl
				 << "\"Then, it's only natural...\"" << endl
				 << "\"Goodbye, dear " << playerName << ".\"" << endl << endl
				 << "What have you done?" << endl;
		}
	}
}

int main(){
	string kidName;
	cout << "Please enter your kid's name: ";
	cin >> kidName;
	YourKid.setName(kidName);
	cout << "Please enter how " << kidName << " should call you: ";
	cin >> playerName;
	for(int round=0;round<12;round++)
		Round(round);
	ending(YourKid.getStatus().moral);
		
	return 0;
}
