#pragma once

#include <string>
#include <vector>
//#include "OutputScreens.h"
//#include "Animation.h"
#include "GameState.h"
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

        //OutputScreens outscr;
       // Animation ani;       

    GameState::GameState(){}
    GameState::RoomName GameState::getCurrentRoom() const{return GameState::currentRoom;}
    void GameState::setCurrentRoom(const GameState::RoomName& newRoom){currentRoom = newRoom;}
    //~();
    
