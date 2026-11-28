#pragma once

#include <string>
#include <vector>
#include "Animation.h"

#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;
class GameState;
/*
There is currently a bug, where sometimes, after reading the menu in briefing room
the player is prompted to enter the passphrase in flight deck
*/
class Rooms{
    private:
        Animation ani;
    public:
        Rooms();
        string invertedAirlockCopy;
        string crewQuartersArt;
        string crewQuarters1;
        string crewQuarters2;
        string crewQuarters3;
        string crewQuarters4;
        string crewQuarters5;
        string crewQuarters6;
        string crewQuarters7;
        string crewQuarters8;
        string crewQuarters9;
        string crewQuarters10;
        string crewQuarters11;
        string crewQuarters12;
        string crewQuarters13;
        string crewQuarters14;
        string crewQuarters15;
        string crewQuarters16;
        string crewQuarters17;
        string crewQuarters18;
        string crewQuarters19;
        string crewQuarters20;
        string crewQuarters21;
        string crewQuarters22;
        string crewQuarters23;
        //~Rooms();
        void setEcho(bool echoState);//setEcho(true) enables cursor and echo, (false) disables both
        void flushPendingKeystrokes();//remove user input from buffer
        void resizeConsole();

        void intro();
        void flightDeckIntro(GameState& state);
        void crewQuarters(GameState& state);
        void briefingRoomIntro(GameState& state);
        void airlock(GameState& state);
        void messHall(GameState& state);
        void messHallBreakerBox(GameState& state);

        void cameraScreen(int page, int camerasAvailable, string bottomText);
        void cameraScreen(int page, int camerasAvailable);
        void cameraScreen();
        void breakerBox(bool switches[6], bool solved);
        
        void roomList(GameState& state);
        
};