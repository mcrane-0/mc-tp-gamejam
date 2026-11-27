#pragma once

#include <string>
#include <vector>
//#include "OutputScreens.h"
//#include "Animation.h"
#include "Rooms.h"
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class GameState
{
    public:
     enum class RoomName
 {
        FlightDeck,
        FlightDeckIntro,
        CrewQuarters,
        BriefingRoom,
        BriefingRoomIntro,
        Airlock,
        MessHall,
        RoomList,
 };
        GameState();
        bool powerRestored;
        vector<RoomName> unlockedRooms;//do .reserve(50) for 50 rooms i think
        void unlockRoom(RoomName room);
        RoomName getCurrentRoom() const;
        bool isRoomUnlocked(RoomName room) const;
        void setCurrentRoom(const RoomName& newRoom);
        void exitRoom();
        void enterRoom(const RoomName& room);


        //~();

    private:
        //OutputScreens outscr;
       // Animation ani;
       Rooms roomObj;
       RoomName currentRoom;
       


};
