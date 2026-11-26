#pragma once

#include <string>
#include <vector>
#include "Animation.h"

#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class Rooms{
    private:
        Animation ani;
    public:
        Rooms();
        //~Rooms();
        void setEcho(bool echoState);//setEcho(true) enables cursor and echo, (false) disables both
        void flushPendingKeystrokes();//remove user input from buffer
        void resizeConsole();

        void briefingRoom();

        void cameraScreen(int page, int camerasAvailable, string bottomText);
        void cameraScreen(int page, int camerasAvailable);
        void cameraScreen();
        void breakerBox(bool switches[6], bool solved);
        
};