#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Rooms.h"

#include "OutputScreens.h"
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


OutputScreens outscr;
Animation ani;

Rooms::Rooms(){ };

/* ASCII Colored Text
	RED = "\033[31m";
    GREEN = "\033[32m";
    CYAN = "\033[36m";
    RESET = "\033[0m";
*/


void Rooms::briefingRoom(){
    ani.centeredTypingNoWait({"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper."});
    char ch;
    while (ch != 'i' && ch != 'x')
    {
        ch = ani.centeredTypingGetChar({"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper.", "", "E(x)it     Zoom (I)n"}, {"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper.", "", "E(x)it     Zoom (I)n"});   
    }
    if (ch == 'i')
    {
        const vector<string> menu = {"Today's Menu:", "Breakfast: coffee/green tea, sausage, pancakes and maple syrup", "Lunch: vegetable quiche with wheat flatbread", "Dinner: barbequed beef brisket.", "", "\033[31m MESS HALL\033[0m Hours of Operation:", "Breakfast: 06:00", "Lunch: 12:00", "Dinner: 17:00"};
        ani.centeredTyping(menu, menu);
       // outscr.printTextScreen({"Today's Menu:", "Breakfast: coffee/green tea, sausage, pancakes and maple syrup", "Lunch: vegetable quiche with wheat flatbread", "Dinner: barbequed beef brisket.", "", "\033[31m MESS HALL\033[0m Hours of Operation:", "Breakfast: 06:00", "Lunch: 12:00", "Dinner: 17:00"});
    }
    else if (ch == 'x')
    {
        cout << "poop";
    }
}

