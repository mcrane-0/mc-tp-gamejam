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

void Rooms::briefingRoom(){
    ani.centeredTyping({"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper."});
    outscr.printTextScreen({"Papers are strewn across a large metal table.", "On the nearest edge, you spot a small blue sheet of paper.", "", "E(x)it     Zoom (I)n"});
    
    outscr.printTextScreen({"Today's Menu:", "Breakfast: coffee/green tea, sausage, pancakes and maple syrup", "Lunch: vegetable quiche with wheat flatbread", "Dinner: barbequed beef brisket.", "", "MESS HALL Hours of Operation:", "Breakfast: 06:00", "Lunch: 12:00", "Dinner: 17:00"});

}

