#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

void clearScreen(){
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
}

int main() {
	/*cout << "--------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < 11; i++) {
		cout << "|                                                                              |" << endl;
	}

	cout << "|              PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS               |" << endl;
	cout << "|                           PRESS ENTER TO CONTINUE                            |" << endl;

	for (int i = 0; i < 10; i++) {
		cout << "|                                                                              |" << endl;
	}

	cout << "-------------------------------------------------------------------------------";*/

	/*clearScreen();
	cout << "\e[8;25;80t";*/ // resize terminal window to 80 x 25 characters

	printTextScreen({ "INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam", "", "PRESS ENTER TO CONTINUE"});
	printTextScreen({"HOW TO INTERACT WITH GAME:", "", "Options for input will be shown on screen in between [square brackets].", "If you are given an \"[O]ption\", type \"O\" and press Enter to choose it.", "", "When there are no options shown on screen, press Enter to continue."});


	cout << "placeholder";

	cin.ignore();


	return 0;
}
