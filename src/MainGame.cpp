/* ----- Introduction -----
 *
 * The game lasts for two years.
 * On each Month's first day, the player can
 * (1) Buy things for the kid.
 * (2) Plan the kid's work for this month.
 *	   The kid has 3 time slots each month.
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
#include "RoundUI.h"
#include "Item.h"
#include "Work.h"
using namespace std;

Kid yourKid;
ItemManager iManager;
string playerName = "Player";
enum endings {STARVE,GGG,BGG,GBG,GGB,BBG,BGB,GBB,BBB}; // MoralMoneyFavor

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
	string name = yourKid.getStatus().name;
	switch(endCode){ // In progress: 9 endings based on moral, money and favor in order
		case(STARVE):{ // Ending(0): Starved
			cout << "The money wasn't enough to pay for " << name << "'s meals..." << endl
				 << "\"" << playerName << ", I'm so... hungry...\"" << endl
			     << name << " died from starvation." << endl;
			break;
		}case(GGG):{ // Ending(1): Happily ever after
			cout << name << " said they wanted to show you something." << endl
				 << "When you arrived at the place, the beauty almost got you stunned." << endl
				 << "With all the money," << name << " bought a beautiful place for you both to live in." << endl << endl
				 << "\"" << playerName << ", thank you so much for raising me.\"" << endl
				 << "You and " << name << " live a peaceful, happy life ever after." << endl << endl
				 << "Ending(1): Happily ever after" << endl;
			break;
		}case(BGG):{ // Ending(2): Mafia gang for you
			cout << "It's when you see two rows of people in suits bow down at you." << endl
				 << "It's when you hear they call " << name << " their boss." << endl
				 << "You finally started to grasp what's going on." << endl << endl
				 << "\"" << playerName << ", I have my very own gang now...\"" << endl
				 << "\"You will be forever safe under our care.\"" << endl << endl
				 << "Ending(2): Mafia gang for you" << endl;
			break;
		}case(GBG):{ // Ending(3): Life is difficult but happy
			cout << "You and " << name << " struggle to make ends meet every month." << endl
				 << "Making money is very difficult and tiring." << endl
				 << "Despite so, " << name << " seems content." << endl << endl
				 << "\"Even if things get tough at times...\"" << endl
				 << "\"As long as I'm with you, " << playerName << ", I'm sure everything will be fine.\"" << endl << endl
				 << "Ending(3): Life is difficult but happy" << endl;
			break;
		}case(GGB):{ // Ending(4): May we never meet again
			cout << "You see " << name << "standing at the front door with their stuff packed up." << endl
				 << "Their expression seems determined and serious." << endl << endl
				 << "\"Thank you for raising me, " << playerName << ", but...\"" << endl
				 << "\"I am moving to somewhere very, very far away.\"" << endl
				 << "\"Sincerely, may we never meet again.\"" << endl << endl
				 << "Ending(4): May we never meet again" << endl;
			break;
		}case(BBG):{ // Ending(5): Got my hands dirty for you
			cout << name << " has become a slick criminal." << endl
				 << "Life has been tough, but they are tougher." << endl
				 << "They do not care whose blood they have to spill, just for you two to survive." << endl << endl
				 << "\"In this world, it's killed or be killed...\"" << endl << endl
				 << "Ending(5): Got my hands dirty for you" << endl;
			break;
		}case(BGB):{ // Ending(6): Erased
			cout << "One day, you hear footsteps behind you." << endl
				 << "Then, before you could react-" << endl
				 << "Something got injected into your neck." << endl
				 << "You feel... breathless..." << endl << endl
				 << "The distant voices of two in a phone call can be heard." << endl
				 << "\"Yes, boss. The target is eliminated.\"" << endl
				 << "\"No worries, I get payed, surely I'll get the work done, 'kay?\"" << endl << endl
				 << "\" That '" << playerName << "' of yours doesn't exist anymore." << endl << endl
				 << "Ending(6): Erased" << endl;
			break;
		}case(GBB):{ // Ending(7): I gently opened the door
			cout << name << "'s anxiety seems to be getting worse and worse lately." << endl
				 << "They suffer from constant nightmares." << endl
				 << "Whether it's about starving to death anytime, or about your harsh words." << endl
				 << "Still, they stayed silent, and endured everything..." << endl << endl
				 << "Until they couldn't pull their neck away from the noose anymore." << endl << endl
				 << "What have you done?" << endl << endl
				 << "Ending(7): I gently opened the door" << endl;
	 			 break;
		}case(BBB):{ // Ending(8): It's all for my sake
			cout << "At the end of the year, " << name << " comes to you." << endl << endl
				 << "\"You are so much richer than me, right?\"" << endl
				 << "\"You kept all the money to yourself and let me do the dirty work, right?\"" << endl
				 << "Their hands are trembling under fury." << endl << endl
				 << "\"Right, it's only natural to... take what's rightfully mine.\"" << endl
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
	yourKid.setName(kidName);
	RoundUI ui(kidName);
	cout << "Please enter how " << kidName << " should call you: ";
	cin >> playerName;
	for(int rnd=0;rnd<24;rnd++){
		ui.round(rnd/12,rnd%12);
		if(yourKid.getStatus().money < foodMoney) ending(STARVE);
    	else ui.roundEnd(rnd/12,rnd%12);
	}
	StatStruct end = yourKid.getStatus();
	int endCode = endCoding(end.moral,end.money,end.favor);
	ending(endCode);
	return 0;
}
