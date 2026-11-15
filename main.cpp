#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "OutputScreens.h"
#include "Player.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

/*void clearScreen(){
	for (int i = 0; i < 200; i++){
		cout << " " << endl;
	}
}

void printTextScreen(vector<string> lines) {
	int upperBlankLines = ( (23 - lines.size()) / 2 );
	int lowerBlankLines = (23 - lines.size() - upperBlankLines);

	cout << "--------------------------------------------------------------------------------" << endl;
	//this_thread::sleep_for(0.1s);

	for (int i = 0; i < upperBlankLines; i++) {
		cout << "|                                                                              |" << endl;
	}

	for (int i = 0; i < lines.size(); i++) {
		int leftBlankChars = ( (78 - lines[i].length()) / 2);
		int rightBlankChars = (78 - lines[i].length() - leftBlankChars);
		cout << "|";
		for (int j = 0; j < leftBlankChars; j++) {
			cout << " ";
		}
		cout << lines[i];
		for (int j = 0; j < rightBlankChars; j++) {
			cout << " ";
		}
		cout << "|" << endl;
	}

	for (int i = 0; i < lowerBlankLines; i++) {
		cout << "|                                                                              |" << endl;
	}

	cout << "-------------------------------------------------------------------------------";

	cin.ignore();
	clearScreen();
}

string printTextWithInputScreen(vector<string> lines) {
	int upperBlankLines = ( (23 - lines.size()) / 2 );
	int lowerBlankLines = (23 - lines.size() - upperBlankLines);

	cout << "--------------------------------------------------------------------------------" << endl;
	//this_thread::sleep_for(0.1s);

	for (int i = 0; i < upperBlankLines; i++) {
		cout << "|                                                                              |" << endl;
	}

	for (int i = 0; i < lines.size(); i++) {
		int leftBlankChars = ( (78 - lines[i].length()) / 2);
		int rightBlankChars = (78 - lines[i].length() - leftBlankChars);
		cout << "|";
		for (int j = 0; j < leftBlankChars; j++) {
			cout << " ";
		}
		cout << lines[i];
		for (int j = 0; j < rightBlankChars; j++) {
			cout << " ";
		}
		cout << "|" << endl;
	}

	for (int i = 0; i < (lowerBlankLines - 1); i++) {
		cout << "|                                                                              |" << endl;
	}

	cout << "--------------------------------------------------------------------------------" << endl;

	string answer = "";
	getline(cin, answer);

	clearScreen();

	return answer;
}*/

int main() {
	//cout << "\e[8;25;80t"; // resize terminal window to 80 x 25 characters
	Player player;
	OutputScreens outscr;
/*
	outscr.printTextScreen({ "PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS", "", "PRESS ENTER TO CONTINUE"});
	outscr.printTextScreen({ "INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam", "", "PRESS ENTER TO CONTINUE"});
	outscr.printTextScreen({"HOW TO INTERACT WITH GAME:", "", "Options for input will be shown on screen in between [square brackets].", "If you are given an \"[O]ption\", type \"O\" and press Enter to choose it.", "", "When there are no options shown on screen, press Enter to continue."});

	cout << "placeholder";
	cin.ignore();

	bool flag = true;
    while (flag == true)
    {
        string userNameInput;
        player.setUserName(outscr.printTextWithInputScreen({" ENTER NAME NOW "}));
        userNameInput = outscr.printTextWithInputScreen({"You have entered ", player.getUserName(), "Is this correct? (y/N)?"});
        //cin.ignore(streamsize(), '\n');
        //cin >> userNameInput;
        //cin.ignore(streamsize(), '\n');
        if (userNameInput == "y" || userNameInput == "Y")
        {
            flag = false;
        }
        else
        {
            cin.ignore(streamsize(), '\n');
        }
    }
	for (int i=0; i<2; i++)
	{
		outscr.printTextScreenNoInput({"Welcome To The ___________", "Surveillance System!"});
		cout << endl;
		this_thread::sleep_for(0.8s);
		outscr.printTextScreenNoInput({"Welcome To The ___________", "Surveillance System!. ",});
		cout << endl;
		this_thread::sleep_for(0.8s);
		outscr.printTextScreenNoInput({"Welcome To The ___________", "Surveillance System!. . ",});
		cout << endl;
		this_thread::sleep_for(0.8s);
		outscr.printTextScreenNoInput({"Welcome To The ___________", "Surveillance System!. . . ",});
		cout << endl;
		this_thread::sleep_for(0.8s);
	}*/
	outscr.printTextScreenNoInput({"Please select a camera to view:"});
	cout << endl;
	this_thread::sleep_for(0.6s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1.| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. F| "});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Fl|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Fli| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flig|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Fligh| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight D|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Di| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Dic|"});
	cout << endl;
	this_thread::sleep_for(0.7s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Di| "});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight D|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight De| "});
	cout << endl;
	this_thread::sleep_for(0.3s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Dec|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2.|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. | "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. C|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Cr| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Cre|"});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew | "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Q|"});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Qu| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Qua|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quar|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quart| "});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarte|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarter| "});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3.| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. B|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Br| "});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Bri|"});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Brie| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Brief|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefi| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefin|"});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing | "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing R|"});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Ro| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Roo|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4.|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. | "});
	this_thread::sleep_for(0.3s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. A|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Ai| "});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Air|"});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airl| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlo|" });
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airloc|"});
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock| "});
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock  "});
	this_thread::sleep_for(0.3s);



	




	return 0;
}
