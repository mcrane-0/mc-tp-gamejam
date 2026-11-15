#include "OutputScreens.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

OutputScreens::OutputScreens(){ };

void OutputScreens::clearScreen(){
	//for (int i = 0; i < 200; i++){
	//	cout << " " << endl;
	//}
	
	// \033[ indicates this is a format sequence
	// 2J means clear visible screen, 3J clears everything from the scroll buffer, 999;1H moves cursor to bottom of screen  
    std::cout << "\033[2J\033[3J\033[999;1H" << std::flush;


}

void OutputScreens::printTextScreen(const vector<string>& lines) {
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

void OutputScreens::printTextScreenNoInput(const vector<string>& lines){
	clearScreen();
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
}

string OutputScreens::printTextWithInputScreen(const vector<string>& lines) {
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

char OutputScreens::printTextWithCharInputScreen(const vector<string>& lines){
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

	char answer;
	cin >> answer;

	clearScreen();

	return answer;
}


void OutputScreens::printCameraScreen(int page, int camerasAvailable, string bottomText){
    cout << "-------------------------- -------------------------- --------------------------" << endl;
    cout << "| [1]                    | | [2]                    | | [3]                    |" << endl;
    for (int i = 0; i < 5; i++){
        cout << "|                        | |                        | |                        |" << endl;
    }
    cout << "-------------------------- -------------------------- --------------------------" << endl;

    cout << "-------------------------- -------------------------- --------------------------" << endl;
    cout << "| [4]                    | |                        | | [5]                    |" << endl;
    cout << "|                        | |      [N]ext Page       | |                        |" << endl;
    cout << "|                        | |    [P]revious Page     | |                        |" << endl;
    cout << "|                        | |     [J]ump to Page     | |                        |" << endl;
    cout << "|                        | |                        | |                        |" << endl;
    cout << "|                        | |        Page " << page << "/4        | |                        |" << endl;
    cout << "-------------------------- -------------------------- --------------------------" << endl;

    cout << "-------------------------- -------------------------- --------------------------" << endl;
    cout << "| [6]                    | | [7]                    | | [8]                    |" << endl;
    for (int i = 0; i < 5; i++){
        cout << "|                        | |                        | |                        |" << endl;
    }
    cout << "-------------------------- -------------------------- --------------------------" << endl;
}
void OutputScreens::printCameraScreen(int page, int camerasAvailable){
    printCameraScreen(page, camerasAvailable, "SELECT A CAMERA");
}
void OutputScreens::printCameraScreen(){
    printCameraScreen(1, 4, "SELECT A CAMERA");
}

