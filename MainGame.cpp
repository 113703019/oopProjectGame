/* ----- Introduction -----
 *
 * The game lasts for a year.
 * On each Month's first day, the player can
 * (1) Buy things for the kid.
 * (2) Plan the kid's work for this month.
 * 
 * In short, there are 12 rounds before the ending.
 * The kid's moral bar will decide the ending.
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

Kid YourKid;

void Round(int month){

	cout << YourKid.getStatus().name << ": \"Hello! What should I do this month?\"" << endl << endl; // Temporary script
	cout << month+1 << YourKid.getStatus().money << "                        " << YourKid.getStatus().emotion << YourKid.getStatus().moral << endl; // Status
	cout << "(Q) Talk | (W) Plan | (E) Inventory | (R) Shop" << endl; // UI instructions

} // Round

int main(){
	for(int round=0;round<12;round++)
		Round(round);
	return 0;
}
