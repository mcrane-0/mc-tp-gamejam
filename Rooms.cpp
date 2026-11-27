#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Rooms.h"
#include "GameState.h"
#include "Animation.h"

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif
#ifdef __linux__
#include <cstring>
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;
using namespace std::chrono;


Animation ani;
//GameState state;
Rooms::Rooms()
{
    invertedAirlockCopy = R"(                                                      █                         
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

    crewQuartersArt = R"(  █      ░█        ██   ░ █      █                                            
  █ █ █░ ░░░░█    ░ ███  █  █░   █                                        ███ 
  ██   ░██░█░ ░ ░  █ █  █  █░   ██                                    ███     
   ██░ █   ███ ░ █░░ ██   ░██ ███                        ████████████         
      ████ ███ █ ████ ░ █ ████               ██                     █      ██ 
        ████████████████████                █ █                     █   ██    
                                     ███████  ██████████           ██████     
█████████████████████████████████████████████ █                               
                                            █ █                           ███ 
                                                   ███████████████  ██        
                                               █                     █        
                                             ██ █                     █  ██   
                                             █  █    █████████████████████████
                                            ██  █                             
                                              ██                              
                                               ███████████████████████████████
                                                                   ██████     
                                                 ██                    █      
                                                █ █                     █    █
                                               █  ████████████████████████████
                                               █  █                           
                                                █ █                           
                                                 █████████████████████████████)";

    crewQuarters1 = "  █      ░█        ██   ░ █      █                                            ";
    crewQuarters2 = "  █ █ █░ ░░░░█    ░ ███  █  █░   █                                        ███ ";
    crewQuarters3 = "  ██   ░██░█░ ░ ░  █ █  █  █░   ██                                    ███     ";
    crewQuarters4 = "   ██░ █   ███ ░ █░░ ██   ░██ ███                        ████████████         ";
    crewQuarters5 = "      ████ ███ █ ████ ░ █ ████               ██                     █      ██ ";
    crewQuarters6 = "        ████████████████████                █ █                     █   ██    ";
    crewQuarters7 = "                                     ███████  ██████████           ██████     ";
    crewQuarters8 = "█████████████████████████████████████████████ █                               ";
    crewQuarters9 = "                                            █ █                           ███ ";
    crewQuarters10 = "                                                   ███████████████  ██        ";
    crewQuarters11 = "                                               █                     █        ";
    crewQuarters12 = "                                             ██ █                     █  ██   ";
    crewQuarters13 = "                                             █  █    █████████████████████████";
    crewQuarters14 = "                                            ██  █                             ";
    crewQuarters15 = "                                              ██                              ";
    crewQuarters16 = "                                               ███████████████████████████████";
    crewQuarters17 = "                                                                   ██████     ";
    crewQuarters18 = "                                                 ██                    █      ";
    crewQuarters19 = "                                                █ █                     █    █";
    crewQuarters20 = "                                               █  ████████████████████████████";
    crewQuarters21 = "                                               █  █                           ";
    crewQuarters22 = "                                                █ █                           ";
    crewQuarters23 = "                                                 █████████████████████████████";
}

/* ASCII Colored Text
	RED = "\033[31m";
    GREEN = "\033[32m";
    CYAN = "\033[36m";
    RESET = "\033[0m";
*/
/*
void Rooms::setEcho(bool echoState) {
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
}*/
void Rooms::flushPendingKeystrokes()
{
    #if defined(__APPLE__) || defined(__linux__)
        tcflush(STDIN_FILENO, TCIFLUSH);
    #elif defined(_WIN32)
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        if (hStdin != INVALID_HANDLE_VALUE) {
            FlushConsoleInputBuffer(hStdin);
        }
    #endif
}
void Rooms::resizeConsole()
{
    #if defined(__APPLE__) || defined(__linux__)
        cout << "\033[8;25;80t" << flush;
    #elif defined(_WIN32)
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SMALL_RECT tiny = {0, 0, 1, 1};
        SetConsoleWindowInfo(hOut, TRUE, &tiny);
        COORD buffer = {80, 25};
        SetConsoleScreenBufferSize(hOut, buffer);
        SMALL_RECT window = {0, 0, 79, 24};
        SetConsoleWindowInfo(hOut, TRUE, &window);
    #endif
}


void Rooms::briefingRoomIntro(GameState& state){
    ani.centeredTypingNoWait({"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper."});
    char ch = '0';
    while (ch != 'i' && ch != 'x')
    {
        ch = ani.centeredTypingGetChar({"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper.", "", "E(x)it     Zoom (I)n"}, {"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper.", "", "E(x)it     Zoom (I)n"});   
    }
    if (ch == 'i')
    {
        const vector<string> menu = {"Today's Menu:", "Breakfast: coffee/green tea, sausage, pancakes and maple syrup", "Lunch: vegetable quiche with wheat flatbread", "Dinner: barbequed beef brisket.", "", "\033[31m MESS HALL\033[0m Hours of Operation:", "Breakfast: 06:00", "Lunch: 12:00", "Dinner: 17:00"};
        ani.centeredTyping(menu, menu, 6, 9);
       // outscr.printTextScreen({"Today's Menu:", "Breakfast: coffee/green tea, sausage, pancakes and maple syrup", "Lunch: vegetable quiche with wheat flatbread", "Dinner: barbequed beef brisket.", "", "\033[31m MESS HALL\033[0m Hours of Operation:", "Breakfast: 06:00", "Lunch: 12:00", "Dinner: 17:00"});
    }
    else if (ch == 'x')
    {
        state.exitRoom();
    }
    state.exitRoom();
}



void Rooms::cameraScreen(int page, int camerasAvailable, string bottomText){
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
void Rooms::cameraScreen(int page, int camerasAvailable){
    cameraScreen(page, camerasAvailable, "SELECT A CAMERA");
}
void Rooms::cameraScreen(){
    cameraScreen(1, 4, "SELECT A CAMERA");
}

void Rooms::breakerBox(bool switches[6], bool solved){
    cout << "\033[3J" << "\033[?1049h" << flush;
    ani.setEcho(false);
    resizeConsole();

    string frame;
    frame.reserve(2100);//pre-allocate all the available characters on screen


    frame += "\033[H";//move cursor to top left
    frame += string(80, '-') + "\n";//render top line
    frame += "|" + string(78, ' ') + "|\n"; // blank space
    if (solved){
        frame += "|" + string(31, ' ') + "\033[32mPOWER RESTORED!\033[0m" + string(32, ' ') + "|\n";
    }
    else {
        frame += "|" + string(15, ' ') + "You notice a small breaker panel on the wall..." + string(16, ' ') + "|\n";
    }
    for (int i = 0; i < 5; i++){ frame += "|" + string(78, ' ') + "|\n"; } // 5 blank spaces

    // left-to-right centering
    for (int i = 0; i < 3; i++)
    {
        int leftSwitch = i;
        int rightSwitch = (i+3);
        char leftSwitchChar = leftSwitch + 65;
        char rightSwitchChar = rightSwitch + 65; 

        frame += "|" + string(27, ' ') + "----------    ----------" + string(27, ' ') + "|\n";

        if (switches[leftSwitch] == true) { // left switch is on
            if (switches[rightSwitch] == true) { // and right switch is on
                frame += "|" + string(27, ' ') + "| (" + leftSwitchChar + ") --]|    |[-- (" + rightSwitchChar + ") |" + string(27, ' ') + "|\n";
            }
            else { // and right switch is off
                frame += "|" + string(27, ' ') + "| (" + leftSwitchChar + ") --]|    | --](" + rightSwitchChar + ") |" + string(27, ' ') + "|\n";
            }
        }
        else { // left switch is off
            if (switches[rightSwitch] == true) { // and right switch is on
                frame += "|" + string(27, ' ') + "| (" + leftSwitchChar + ")[-- |    |[-- (" + rightSwitchChar + ") |" + string(27, ' ') + "|\n";
            }
            else { // and right switch is off
                frame += "|" + string(27, ' ') + "| (" + leftSwitchChar + ")[-- |    | --](" + rightSwitchChar + ") |" + string(27, ' ') + "|\n";
            }
        }

        frame += "|" + string(27, ' ') + "----------    ----------" + string(27, ' ') + "|\n";
        frame += "|" + string(78, ' ') + "|\n";
    }

    for (int i = 0; i < 3; i++) { frame += "|" + string(78, ' ') + "|\n"; } // 3 blank spaces
    if (solved){
        frame += "|" + string(78, ' ') + "|\n";
    }
    else {
        frame += "| E(x)it" + string(71, ' ') + "|\n";
    }
    frame += string(79, '-'); // bottom line

    cout << frame << flush;
    ani.setEcho(true);
}

//Trevor additions
void Rooms::intro()
{
    ani.printTextScreen( {"PLEASE ADJUST TERMINAL SIZE TO 80 x 25 CHARACTERS", "", "PRESS ENTER TO CONTINUE"});
    ani.printTextScreen({"INSERT TITLE HERE", "By Miles Crane and Trevor Past", "For the Fall 2026 MSU Game Jam", "", "PRESS ENTER TO CONTINUE"});
    ani.printTextScreen({"HOW TO INTERACT WITH GAME:", "", "Options for input will be shown on screen in between [square brackets].", "If you are given an \"[O]ption\", type \"O\" and press Enter to choose it.", "", "When there are no options shown on screen, press Enter to continue."});
}
void Rooms::flightDeckIntro(GameState& state)
{
	const string PASSPHRASEFLIGHTDECK = "What if the truth that I find is just a prettier lie?";
    const string PASSPHRASEFLIGHTDECK2 = "what if the truth that i find is just a prettier lie?";
    const string PASSPHRASEFLIGHTDECK3 = "what if the truth that I find is just a prettier lie?";

    string passphrase = "";
	char ch = '0';
	bool flag = true;
    while (flag == true)
    {
        ani.flushPendingKeystrokes();
        passphrase = ani.printTextScreenWithInput({"This is a secure area. Authorization required.", "", "", "", "",
        "Enter Passphrase:"});
        if (passphrase == PASSPHRASEFLIGHTDECK || passphrase == PASSPHRASEFLIGHTDECK2 || passphrase == PASSPHRASEFLIGHTDECK3)
        {
            flag = false;
            state.unlockedRooms.emplace_back(GameState::RoomName::FlightDeck);
            //state.enterRoom(GameState::RoomName::FlightDeck);
        }
        else
        {
            ani.flushPendingKeystrokes();
            ch = ani.centeredTypingGetChar({"Try Again? (Y/n)"}, {""});
			if (ch == 'n')
			{
                ani.flushPendingKeystrokes();
				state.enterRoom(GameState::RoomName::RoomList);
			}
            ani.flushPendingKeystrokes();
        }
    }
}
    void Rooms::airlock(GameState& state)
    {
        ani.flushPendingKeystrokes();
        ani.setEcho(false);
        cout << invertedAirlockCopy;
        cin.ignore();
        ani.setEcho(true);
        if (!state.powerRestored)
        {
            ani.flushPendingKeystrokes();
            state.enterRoom(GameState::RoomName::RoomList);
        }
        //else enter camera

    }

    void Rooms::crewQuarters(GameState& state)
    {
        ani.flushPendingKeystrokes();
        ani.printTextScreen(
            {crewQuarters1, crewQuarters2, crewQuarters3, crewQuarters4, crewQuarters5,
             crewQuarters6, crewQuarters7, crewQuarters8, crewQuarters9, crewQuarters10,
             crewQuarters11, crewQuarters12, crewQuarters13, crewQuarters14, crewQuarters15,
             crewQuarters16, crewQuarters17, crewQuarters18, crewQuarters19, "  There's nobody here...                        ████████████████████████████. |",
             crewQuarters21, crewQuarters22, crewQuarters23}
            );
            state.enterRoom(GameState::RoomName::RoomList);
    }

    void Rooms::roomList(GameState& state)
    {
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
        if (state.isRoomUnlocked(GameState::RoomName::FlightDeck))
        {
            //state.enterRoom(GameState::RoomName::FlightDeck);
            //a way back home... a brief scene plays and the game ends, 
            //returning the player to the reality they had temporarily abandoned
        }
        else
        {
		    state.enterRoom(GameState::RoomName::FlightDeckIntro);
        }
		break;
	case '2':
		state.enterRoom(GameState::RoomName::CrewQuarters);
		break;
	case '3':
		state.enterRoom(GameState::RoomName::BriefingRoomIntro);
		break;
	case '4':
		state.enterRoom(GameState::RoomName::Airlock);
		break;

	default:
		break;
	}
    }
