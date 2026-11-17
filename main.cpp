#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "OutputScreens.h"
#include "Player.h"
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;


int main() {
	#ifdef _WIN32
    
#endif
    cout << "\033[2J\033[H\033[?25l" << flush;
	//cout << "\e[8;25;80t"; // resize terminal window to 80 x 25 characters
	Player player;
	OutputScreens outscr;

	outscr.printTextScreen({ "PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS", "", "PRESS ENTER TO CONTINUE"});
	outscr.printTextScreen({ "INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam", "", "PRESS ENTER TO CONTINUE"});
	outscr.printTextScreen({"HOW TO INTERACT WITH GAME:", "", "Options for input will be shown on screen in between [square brackets].", "If you are given an \"[O]ption\", type \"O\" and press Enter to choose it.", "", "When there are no options shown on screen, press Enter to continue."});
	//outscr.setEcho(false);
	//outscr.printCameraList();
	//outscr.setEcho(true);

	cin.ignore();


	bool flag = true;
    while (flag == true)
    {
        string userNameInput;
        player.setUserName(outscr.printTextScreenWithInput({" ENTER NAME NOW "}));
        userNameInput = outscr.printTextScreenWithInput({"You have entered ", player.getUserName(), "Is this correct? (y/N)?"});
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
	
	outscr.setEcho(false);
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
	}
	outscr.printTextScreenNoInput({"Please select a camera to view:"});
	cout << "\n";
	this_thread::sleep_for(0.6s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1.| "});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. F| "});
	cout << "\n";
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Fl|"});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Fli| "});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flig|"});
	cout << "\n";
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Fligh| "});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight|"});
	cout << "\n";
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight D|"});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Di| "});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Dic|"});
	cout << "\n";
	this_thread::sleep_for(0.7s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Di| "});
	cout << "\n";
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight D|"});
	cout << "\n";
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight De| "});
	cout << "\n";
	this_thread::sleep_for(0.3s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Dec|"});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck|"});
	cout << "\n";
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2.|"});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. | "});
	cout << "\n";
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. C|"});
	//cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Cr| "});
	//cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Cre|"});
	//cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew| "});
	//cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew | "});
	//cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Q|"});
	//cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Qu| "});
	//cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Qua|"});
	//cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quar|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quart| "});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarte|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarter| "});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3.| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. B|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Br| "});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Bri|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Brie| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Brief|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefi| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefin|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing | "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing R|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Ro| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Roo|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4.|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. | "});
	cout << endl;
	this_thread::sleep_for(0.3s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. A|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Ai| "});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Air|"});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airl| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlo|" });
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airloc|"});
	cout << endl;
	this_thread::sleep_for(0.2s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock| "});
	cout << endl;
	this_thread::sleep_for(0.1s);
	outscr.printTextScreenNoInput({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock  "});
	cout << endl;
	this_thread::sleep_for(0.3s);
	outscr.setEcho(true);



	




	return 0;
}
