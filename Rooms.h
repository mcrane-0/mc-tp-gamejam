#pragma once

#include <string>
#include <vector>
#include "OutputScreens.h"
#include "Animation.h"

#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class Rooms{
    private:
        OutputScreens outscr;
        Animation ani;
    public:
        Rooms();
        //~Rooms();

        void briefingRoom();
        
};