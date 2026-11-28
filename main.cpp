#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Player.h"
#include "Animation.h"
#include "Rooms.h"
#include "GameState.h"

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__) || defined(__linux__)
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#endif


using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

#if defined(__APPLE__) || defined(__linux__)
char _getch() 
{
    struct termios savedTerm, tempTerm;
    char ch;

    tcgetattr(STDIN_FILENO, &savedTerm);
    tempTerm = savedTerm;//copy settings into temp settings
    tempTerm.c_lflag &= ~(ICANON | ECHO); //turn off line buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &tempTerm);//apply temp settings
    ch = getchar();//get char
    tcsetattr(STDIN_FILENO, TCSANOW, &savedTerm);//restore original settings
    return ch;
}
#endif

int main() {
	//enable ansi sequences in windows
	#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//finds output stream
    if (hOut != INVALID_HANDLE_VALUE) {//checks if its the console/a valid output stream
        DWORD dwMode = 0;//the rest is weird windows OS settings stuff
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
	#endif

	const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string CYAN = "\033[36m";
    const string RESET = "\033[0m";

    cout << "\033[2J\033[H\033[?25l" << flush;
	//cout << "\e[8;25;80t" << flush; // resize terminal window to 80 x 25 characters
	Player player;
	Animation ani;
	Rooms rooms;
	GameState state;

	//ASCII ART STILLS
	/*
	string airlock1 ="███████████████████████████████████████████████████ ████████████████████████";
	string airlock2 ="████████████████████████ ███████████████████████████ ███████████████████████";
	string airlock3 ="██████████████████████  █████████████████████████████  █████████████████████";
	string airlock4 =	"█████████████████████ ████████████████████████████████  ████████████████████";
	string airlock5 =	"█████████████████████ ███████████████████████        ██ ████████████████████";
	string airlock6 =	"███████████████████  ████████  ██████ ███████████ ███ ██  ██████████████████";
	string airlock7 =	"██████████████████  ████████  █████████████░ ████████ ███  █████████████████";
	string airlock8 =	"█████████████████  █████████ █████ ███████ ██████████ ████  ████████████████";
	string airlock9 ="█████████████████████████  ███████████ ███████░░█████ ██████████████████████";
	string airlock10 ="█████████████████████████  ██░██████ ███████████████ ███████████████████████";
	string airlock11 ="█████████████████████████  ███░███ ████░░█████████  ████████████████████████";
	string airlock12 ="█████████████████████████  ██████████████ ████ ██ ██████████ ███████████████";
	string airlock13 =	"████████████████ ████████  ████ ████████████████ ████████ ██ ███████████████";
	string airlock14 =	"████████████████ ████████                      █████████ ██  ███████████████";
	string airlock15 =	"████████████████████  ██████████████████████░█     █████  ██████████████████";
	string airlock16 =	"████████████████████  █                    █░████████████ ██████████████████";
	string airlock17 =	"████████████████████  █████████████████████████████████ █ ██████████████████";
	string airlock18 =	"███████████████████   ███████████████████████████████████  █████████████████";
	string airlock19 =	"███████████████████ ██████████████████████████████████████ █████████████████";
	string airlock20 =	"███████████████████ ██████████████████████████████████████   ███████████████";
	string airlock21 =	"████████████████   ███████████████████████████████████████ █████████████████";
	string airlock22 =	"██████████████████  ████████████████████████████████████████████████████████";
	string airlockInverted1 = "                                                   █                        ";
	string airlockInverted2 = "                        █                           █                       ";
	string airlockInverted3 = "                      ██                             ██                     ";
	string airlockInverted4 = "                     █                                ██                    ";
	string airlockInverted5 = "                     █                       ████████  █                    ";
	string airlockInverted6 = "                   ██        ██      █           █   █  ██                  ";
	string airlockInverted7 = "                  ██        ██             ▓█        █   ██                 ";
	string airlockInverted8 = "                 ██         █     █       █          █    ██                ";
	string airlockInverted9 = "                         ██           █       ▓▓     █                      ";
	string airlockInverted10 = "                         ██  ▓      █               █                       ";
	string airlockInverted11 = "                         ██   ▓   █    ▓▓         ██                        ";
	string airlockInverted12 = "                         ██              █    █  █          █               ";
	string airlockInverted13 = "                █        ██    █                █        █  █               ";
	string airlockInverted14 = "                █        ██████████████████████         █  ██               ";
	string airlockInverted15 = "                    ██                      ▓ █████     ██                  ";
	string airlockInverted16 = "                    ██ ████████████████████ ▓            █                  ";
	string airlockInverted17 = "                    ██                                 █ █                  ";
	string airlockInverted18 = "                   ███                                   ██                 ";
	string airlockInverted19 = "                   █                                      █                 ";
	string airlockInverted20 = "                   █                                      ███               ";
	string airlockInverted21 = "                ███                                       █                 ";
	string airlockInverted22 = "                  ██                                                        ";
//copyable
string airlockCopy = R"(██████████████████████████████████████████████████████ █████████████████████████
██████████████████████████████████████████████████████ █████████████████████████
██████████████████████████ ████████████████████████████ ████████████████████████
████████████████████████  ██████████████████████████████  ██████████████████████
███████████████████████ █████████████████████████████████  █████████████████████
███████████████████████ ████████████████████████        ██ █████████████████████
████████████████████   ████████  ██████ ████████████ ███ ██   ██████████████████
███████████████████   ████████  ██████████████░ ████████ ███   █████████████████
██████████████████  ██████████ █████ ████████ ██████████ █████  ████████████████
██████████████████  ██████████ █████ ████████ ██████████ █████  ████████████████
███████████████████████████  ███████████  ███████░░█████ ███████████████████████
███████████████████████████  ██░██████ ████████████████ ████████████████████████
███████████████████████████  ███░███ █████░░█████████  █████████████████████████
███████████████████████████  ███████████████ ████ ██ ███████████ ███████████████
█████████████████ █████████  ████ █████████████████ ████████  ██ ███████████████
█████████████████ █████████                       █████████ ███  ███████████████
██████████████████████  ███████████████████████░█     █████   ██████████████████
██████████████████████  ███████████████████████░█     █████   ██████████████████
██████████████████████  █                     █░████████████  ██████████████████
██████████████████████  ██████████████████████████████████ █  ██████████████████
████████████████████    ████████████████████████████████████   █████████████████
████████████████████  ████████████████████████████████████████ █████████████████
████████████████████  ████████████████████████████████████████   ███████████████
█████████████████   ██████████████████████████████████████████ █████████████████
███████████████████   ██████████████████████████████████████████████████████████)";
string invertedAirlockCopy = R"(                                                      █                         
                                                      █                         
                          █                            █                        
                        ██                              ██                      
                       █                                 ██                     
                       █                        ████████  █                     
                    ███        ██      █            █   █  ███                  
                   ███        ██              ▓█        █   ███                 
                  ██          █     █        █          █     ██                
                  ██          █     █        █          █     ██                
                           ██           ██       ▓▓     █                       
                           ██  ▓      █                █                        
                           ██   ▓   █     ▓▓         ██                         
                           ██               █    █  █           █               
                 █         ██    █                 █        ██  █               
                 █         ███████████████████████         █   ██               
                      ██                       ▓ █████     ███                  
                      ██                       ▓ █████     ███                  
                      ██ █████████████████████ ▓            ██                  
                      ██                                  █ ██                  
                    ████                                    ███                 
                    ██                                        █                 
                    ██                                        ███               
                 ███                                          █                 
                   ███                                                          
)";
*/



	//rooms.briefingRoom();
	
	//ani.centeredTyping({ "PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS", "", "PRESS ENTER TO CONTINUE" }, { "PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS", "", "PRESS ENTER TO CONTINUE" });
	//ani.centeredTyping({ "INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam", "", "PRESS ENTER TO CONTINUE" }, { "INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam", "", "PRESS ENTER TO CONTINUE" });
	//ani.centeredTyping({ "HOW TO INTERACT WITH GAME:", "", "Options for input will be shown on screen in between [square brackets].", "If you are given an \"[O]ption\", type \"O\" and press Enter to choose it.", "", "When there are no options shown on screen, press Enter to continue." }, { "HOW TO INTERACT WITH GAME:", "", "Options for input will be shown on screen in between [square brackets].", "If you are given an \"[O]ption\", type \"O\" and press Enter to choose it.", "", "When there are no options shown on screen, press Enter to continue." });
	rooms.intro();
	//cout << airlockCopy;
	//cin.ignore();
	//cout << invertedAirlockCopy;
	//cin.ignore();
	/*
	ani.printTextScreen({airlock1, airlock2, airlock3, airlock4, airlock5, airlock6, airlock7,
	airlock8, airlock9, airlock10, airlock11, airlock12, airlock13, airlock14, airlock15, airlock16, airlock17, airlock18, airlock19, airlock20, airlock21, airlock22});
	//inverted
	ani.printTextScreen({
		airlockInverted1, airlockInverted2, airlockInverted3, airlockInverted4,
		airlockInverted5, airlockInverted6, airlockInverted7, airlockInverted8,
		airlockInverted9, airlockInverted10, airlockInverted11, airlockInverted12,
		airlockInverted13, airlockInverted14, airlockInverted15, airlockInverted16,
		airlockInverted17, airlockInverted18, airlockInverted19, airlockInverted20,
		airlockInverted21, airlockInverted22
	});
	*/
	
	bool flag = true;
    while (flag == true)
    {
        string userNameInput;
        player.setUserName(ani.printTextScreenWithInput({" ENTER NAME NOW "}));
        userNameInput = ani.centeredTypingGetChar({"You have entered ", player.getUserName(), "Is this correct? (y/N)?"}, {"You have entered ", player.getUserName(), "Is this correct? (y/N)?"});
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

	ani.centeredTyping({"Welcome To The ___________", "Surveillance System!"});
	ani.centeredTypingNoWait({"Please select a camera to view:", "1. Flight Dic"}, 5);
	this_thread::sleep_for(0.3s);
	ani.centeredTypingNoWait({"Please select a camera to view:", "1. Flight Di"}, {"Please select a camera to view:", "1. Flight Di"}, 5);
	this_thread::sleep_for(0.1s);
	ani.setEcho(true);
	state.enterRoom(GameState::RoomName::RoomList);
	/*
	char roomSelection;
	roomSelection = ani.centeredTypingGetChar({"Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock"}, {"Please select a camera to view:", "1. Flight D"});
	if (roomSelection != '1' && roomSelection != '2' && roomSelection != '3' && roomSelection != '4')
	{
		while (roomSelection != '1' && roomSelection != '2' && roomSelection != '3' && roomSelection != '4')
		{
			roomSelection = ani.centeredTypingGetChar({"Invalid Selection.","Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock"}, {"Invalid Selection.","Please select a camera to view:", "1. Flight Deck", "2. Crew Quarters ", "3. Briefing Room", "4. Airlock"});
		}
	}
	//while (true)
	//{
	switch (roomSelection)
	{
	case '1':
		state.setCurrentRoom(GameState::RoomName::FlightDeck);
		break;
	case '2':
		state.setCurrentRoom(GameState::RoomName::CrewQuarters);
		break;
	case '3':
		//state.setCurrentRoom(GameState::RoomName::BriefingRoom);
		//rooms.briefingRoomIntro();
		state.enterRoom(GameState::RoomName::BriefingRoomIntro);
		break;
	case '4':
		state.setCurrentRoom(GameState::RoomName::Airlock);
		break;

	default:
		break;
	}
*/
	// bool breakerSwitches[6] = { true, true, true, false, false, true }; // A, B, C, D, E, F    true = ON, false = OFF
	// char inputCh = ' ';
	// bool solved = false;
	// rooms.breakerBox(breakerSwitches, solved);
	// while (inputCh != 'x'){
	// 	inputCh = _getch();
	// 	switch (inputCh){
	// 		case ('a'):
	// 			breakerSwitches[0] = !(breakerSwitches[0]);
	// 			break;
	// 		case ('b'):
	// 			breakerSwitches[1] = !(breakerSwitches[1]);
	// 			break;
	// 		case ('c'):
	// 			breakerSwitches[2] = !(breakerSwitches[2]);
	// 			break;
	// 		case ('d'):
	// 			breakerSwitches[3] = !(breakerSwitches[3]);
	// 			break;
	// 		case ('e'):
	// 			breakerSwitches[4] = !(breakerSwitches[4]);
	// 			break;
	// 		case ('f'):
	// 			breakerSwitches[5] = !(breakerSwitches[5]);
	// 			break;
	// 	}

	// 	if ( breakerSwitches[0] && breakerSwitches[1] && breakerSwitches[2] && breakerSwitches[3] && breakerSwitches[4] && breakerSwitches[5] ){
	// 		solved = true;
	// 	}

	// 	rooms.breakerBox(breakerSwitches, solved);

	// 	if (solved){
	// 		this_thread::sleep_for(3s);
	// 		break;
	// 	}
	// }
	
	// if (solved){
	// 	state.powerRestored = true;
	// 	rooms.cameraScreen();
	// }
	// else { // user just exited
	// 	ani.centeredTyping({"L"});
	// 	rooms.cameraScreen();

	// }


	return 0;
}
/*
	const string PASSPHRASEFLIGHTDECK = "What if the truth that I find is just a prettier lie?";
	bool flag = true;
    while (flag == true)
    {
        string passphrase = "";
		char ch = "0";
        passphrase = ani.printTextScreenWithInput({" ENTER NAME NOW "});
        if (passphrase == PASSPHRASEFLIGHTDECK)
        {
            flag = false;
        }
        else
        {
            ch = ani.centeredTypingGetChar({"Try Again? (Y/n)"});
			if (ch == "n")
			{
				enterRoom(GameState::RoomName::RoomList);
			}
        }
    }
		*/