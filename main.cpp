#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

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

	printTextScreen({ "PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS", "PRESS ENTER TO CONTINUE" });
	printTextScreen({ "INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam"});


	cout << "pee pee";

	cin.ignore();


	return 0;
}