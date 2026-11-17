#include "OutputScreens.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif
using namespace std;
using namespace std::chrono;

bool echo_altered = false;//safety flag prevents overwriting

OutputScreens::OutputScreens(){ };
OutputScreens::~OutputScreens(){ if (echo_altered) {
            setEcho(true);
        }};
        #ifdef __APPLE__
termios saved_tio;
#endif
 void OutputScreens::setEcho(bool echoState) {
    #ifdef __APPLE__
        if (!echoState) {
            if (!echo_altered) {
                tcgetattr(STDIN_FILENO, &saved_tio);//backup terminal settings
                echo_altered = true;
            }
            termios new_tio = saved_tio;
            cout << "\033[?25l" << flush;
            new_tio.c_lflag &= ~ECHO;//disable echo
            tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
        } else if (echo_altered) {
            // Restore terminal settings
            cout << "\033[?25h" << flush;
            tcsetattr(STDIN_FILENO, TCSANOW, &saved_tio);
            echo_altered = false;
        }
        #endif
    }
    void OutputScreens::flushPendingKeystrokes()
    {
    #ifdef __APPLE__
    tcflush(STDIN_FILENO, TCIFLUSH);
    #endif
    }
void OutputScreens::clearScreen(){
	//for (int i = 0; i < 200; i++){
	//	cout << " " << "\n";
	//}
	
	// \033[ indicates this is a format sequence
	// 2J means clear visible screen, 3J clears everything from the scroll buffer, 999;1H moves cursor to bottom of screen 
    flushPendingKeystrokes(); 
    std::cout << "\033[2J\033[3J\033[999;1H" << std::flush;


}

void OutputScreens::printTextScreen(const vector<string>& lines) {
	int upperBlankLines = ( (23 - lines.size()) / 2 );
	int lowerBlankLines = (23 - lines.size() - upperBlankLines);

	cout << "--------------------------------------------------------------------------------" << "\n";
	//this_thread::sleep_for(0.1s);
	for (int i = 0; i < upperBlankLines; i++) {
		cout << "|                                                                              |" << "\n";
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
		cout << "|" << "\n";
	}

	for (int i = 0; i < lowerBlankLines; i++) {
		cout << "|                                                                              |" << "\n";
	}

	cout << "-------------------------------------------------------------------------------" << flush;

	cin.ignore();
	clearScreen();
}

void OutputScreens::printTextScreenNoInput(const vector<string>& lines){
	//clearScreen();
    int upperBlankLines = ( (23 - lines.size()) / 2 );
	int lowerBlankLines = (23 - lines.size() - upperBlankLines);

	cout << "--------------------------------------------------------------------------------" << "\n";
	//this_thread::sleep_for(0.1s);

	for (int i = 0; i < upperBlankLines; i++) {
		cout << "|                                                                              |" << "\n";
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
		cout << "|" << "\n";
	}

	for (int i = 0; i < lowerBlankLines; i++) {
		cout << "|                                                                              |" << "\n";
	}

	cout << "-------------------------------------------------------------------------------" << flush;
    #ifdef _WIN32
    // Move cursor to top left without wiping the screen
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = {0, 0};
    SetConsoleCursorPosition(hOut, topLeft);

    // Write to console buffer
    DWORD charsWritten = 0;
    WriteConsoleA(hOut, frame.c_str(), static_cast<DWORD>(frame.size()), &charsWritten, nullptr);
    #endif

}

string OutputScreens::printTextScreenWithInput(const vector<string>& lines) {
	int upperBlankLines = ( (23 - lines.size()) / 2 );
	int lowerBlankLines = (23 - lines.size() - upperBlankLines);

	cout << "--------------------------------------------------------------------------------" << "\n";
	//this_thread::sleep_for(0.1s);

	for (int i = 0; i < upperBlankLines; i++) {
		cout << "|                                                                              |" << "\n";
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
		cout << "|" << "\n";
	}

	for (int i = 0; i < (lowerBlankLines - 1); i++) {
		cout << "|                                                                              |" << "\n";
	}

	cout << "--------------------------------------------------------------------------------" << "\n" << flush;
    flushPendingKeystrokes();
	string answer = "";
   
	getline(cin, answer);

	clearScreen();

	return answer;
}

char OutputScreens::printTextScreenWithCharInput(const vector<string>& lines){
    int upperBlankLines = ( (23 - lines.size()) / 2 );
	int lowerBlankLines = (23 - lines.size() - upperBlankLines);

	cout << "--------------------------------------------------------------------------------" << "\n";
	//this_thread::sleep_for(0.1s);

	for (int i = 0; i < upperBlankLines; i++) {
		cout << "|                                                                              |" << "\n";
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
		cout << "|" << "\n";
	}

	for (int i = 0; i < (lowerBlankLines - 1); i++) {
		cout << "|                                                                              |" << "\n";
	}

	cout << "--------------------------------------------------------------------------------" << "\n";

	char answer;
	cin >> answer;

	clearScreen();

	return answer;
}


void OutputScreens::printCameraScreen(int page, int camerasAvailable, string bottomText){
    int c[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // camera numbers
    if (page < 1){ // adjust camera numbers based on page number
        for (int i : c){
            c[i] = (c[i] + ( 8 * (page - 1) ) );
        }
    }

    if (camerasAvailable >= c[7]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "]                    | |                        | | [" << c[4] << "]                    |" << "\n";
        cout << "|                        | |      [N]ext Page       | |                        |" << "\n";
        cout << "|                        | |    [P]revious Page     | |                        |" << "\n";
        cout << "|                        | |     [J]ump to Page     | |                        |" << "\n";
        cout << "|                        | |                        | |                        |" << "\n";
        cout << "|                        | |        Page " << page << "/4        | |                        |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "]                    | | [" << c[6] << "]                    | | [" << c[7] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[6]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "]                    | |                        | | [" << c[4] << "]                    |" << "\n";
        cout << "|                        | |      [N]ext Page       | |                        |" << "\n";
        cout << "|                        | |    [P]revious Page     | |                        |" << "\n";
        cout << "|                        | |     [J]ump to Page     | |                        |" << "\n";
        cout << "|                        | |                        | |                        |" << "\n";
        cout << "|                        | |        Page " << page << "/4        | |                        |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "]                    | | [" << c[6] << "]                    | | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|                        | |                        | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |                        | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |                        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[5]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "]                    | |                        | | [" << c[4] << "]                    |" << "\n";
        cout << "|                        | |      [N]ext Page       | |                        |" << "\n";
        cout << "|                        | |    [P]revious Page     | |                        |" << "\n";
        cout << "|                        | |     [J]ump to Page     | |                        |" << "\n";
        cout << "|                        | |                        | |                        |" << "\n";
        cout << "|                        | |        Page " << page << "/4        | |                        |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "]                    | | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|                        | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[4]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "]                    | |                        | | [" << c[4] << "]                    |" << "\n";
        cout << "|                        | |      [N]ext Page       | |                        |" << "\n";
        cout << "|                        | |    [P]revious Page     | |                        |" << "\n";
        cout << "|                        | |     [J]ump to Page     | |                        |" << "\n";
        cout << "|                        | |                        | |                        |" << "\n";
        cout << "|                        | |        Page " << page << "/4        | |                        |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "] / / / / / / / / / /| | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[3]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "]                    | |                        | | [" << c[4] << "] / / / / / / / / / /|" << "\n";
        cout << "|                        | |      [N]ext Page       | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | |    [P]revious Page     | | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |     [J]ump to Page     | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |        Page " << page << "/4        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "] / / / / / / / / / /| | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[2]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "]                    |" << "\n";
        for (int i = 0; i < 5; i++){
            cout << "|                        | |                        | |                        |" << "\n";
        }
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "] / / / / / / / / / /| |                        | | [" << c[4] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |      [N]ext Page       | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |    [P]revious Page     | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |     [J]ump to Page     | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |        Page " << page << "/4        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "] / / / / / / / / / /| | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[1]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "]                    | | [" << c[2] << "] / / / / / / / / / /|" << "\n";
        cout << "|                        | |                        | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |                        | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |                        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "] / / / / / / / / / /| |                        | | [" << c[4] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |      [N]ext Page       | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |    [P]revious Page     | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |     [J]ump to Page     | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |        Page " << page << "/4        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "] / / / / / / / / / /| | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else if (camerasAvailable == c[0]){
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "]                    | | [" << c[1] << "] / / / / / / / / / /| | [" << c[2] << "] / / / / / / / / / /|" << "\n";
        cout << "|                        | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "|                        | | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|                        | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "] / / / / / / / / / /| |                        | | [" << c[4] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |      [N]ext Page       | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |    [P]revious Page     | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |     [J]ump to Page     | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |        Page " << page << "/4        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "] / / / / / / / / / /| | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    else{
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[0] << "] / / / / / / / / / /| | [" << c[1] << "] / / / / / / / / / /| | [" << c[2] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[3] << "] / / / / / / / / / /| |                        | | [" << c[4] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |      [N]ext Page       | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |    [P]revious Page     | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |     [J]ump to Page     | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| |                        | | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |        Page " << page << "/4        | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";

        cout << "-------------------------- -------------------------- --------------------------" << "\n";
        cout << "| [" << c[5] << "] / / / / / / / / / /| | [" << c[6] << "] / / / / / / / / / /| | [" << c[7] << "] / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "| / / / / / / / / / / / /| | / / / / / / / / / / / /| | / / / / / / / / / / / /|" << "\n";
        cout << "|/ / / / / / / / / / / / | |/ / / / / / / / / / / / | |/ / / / / / / / / / / / |" << "\n";
        cout << "-------------------------- -------------------------- --------------------------" << "\n";
    }
    
    int leftBlankChars = ( (80 - bottomText.length()) / 2);
    int rightBlankChars = (80 - bottomText.length() - leftBlankChars - 12);
    for (int j = 0; j < leftBlankChars; j++) {
        cout << " ";
    }
    cout << bottomText;
    for (int j = 0; j < rightBlankChars; j++) {
        cout << " ";
    }
    cout << "[F]loorplan";
}
/*
void OutputScreens::printCameraScreen(int page, int camerasAvailable){
    printCameraScreen(page, camerasAvailable, "SELECT A CAMERA");
}
void OutputScreens::printCameraScreen(){
    printCameraScreen(1, 4, "SELECT A CAMERA");
}
void OutputScreens::printCameraList(){ // list of camera options at start of game
    // welcome animation
    for (int i=0; i<2; i++)
	{
        clearScreen();
        for (int j = 0; j < 11; j++){ cout << " \n"; }
		cout << "                           Welcome To The ___________" << "\n" << "                           Surveillance System!" << "\n";
		for (int j = 0; j < 11; j++){ cout << " \n"; }
        this_thread::sleep_for(0.8s);

        clearScreen();
		for (int j = 0; j < 11; j++){ cout << " \n"; }
		cout << "                           Welcome To The ___________" << "\n" << "                           Surveillance System! ." << "\n";
		for (int j = 0; j < 11; j++){ cout << " \n"; }
        this_thread::sleep_for(0.8s);

        clearScreen();
		for (int j = 0; j < 11; j++){ cout << " \n"; }
		cout << "                           Welcome To The ___________" << "\n" << "                           Surveillance System! . ." << "\n";
		for (int j = 0; j < 11; j++){ cout << " \n"; }
        this_thread::sleep_for(0.8s);
        
        clearScreen();
		for (int j = 0; j < 11; j++){ cout << " \n"; }
		cout << "                           Welcome To The ___________" << "\n" << "                           Surveillance System! . . ." << "\n";
		for (int j = 0; j < 11; j++){ cout << " \n"; }
        this_thread::sleep_for(0.8s);
	}

    // list animation
    clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n";
	for (int j = 0; j < 14; j++){ cout << " \n"; }
    this_thread::sleep_for(0.6s);

    clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1]| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
    this_thread::sleep_for(0.1s);

    clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] F| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
    this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Fl| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Fli| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flig| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Fligh| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight D| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Di| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Dic| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.7s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Di| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight D| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight De| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.3s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Dec| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck| " << "\n";
	for (int j = 0; j < 12; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2]|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] |" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] C|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Cr|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Cre|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

    clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew |" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);
    
	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Q|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Qu|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Qua|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quar|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quart|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarte|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarter|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters|" << "\n";
	for (int j = 0; j < 11; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3]|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] B|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Br|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Bri|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Brie|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Brief|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefi|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefin|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing |" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing R|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Ro|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Roo|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room|" << "\n";
	for (int j = 0; j < 10; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4]|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] |" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.3s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] A|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Ai|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Air|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Airl|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Airlo|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Airloc|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.2s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Airlock|" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.1s);

	clearScreen();
    for (int j = 0; j < 9; j++){ cout << " \n"; }
	cout << "                        Please select a camera to view:" << "\n\n" << "                                [1] Flight Deck" << "\n" << "                               [2] Crew Quarters" << "\n" << "                               [3] Briefing Room" << "\n" << "                                  [4] Airlock" << "\n";
	for (int j = 0; j < 9; j++){ cout << " \n"; }
	this_thread::sleep_for(0.3s);
}
    */