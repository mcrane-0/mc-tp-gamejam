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
        CrewQuarters,
        BriefingRoom,
        Airlock,
        MessHall,
 };
        GameState();
        vector<RoomName> unlockedRooms;//do .reserve(50) for 50 rooms i think
        void unlockRoom(RoomName room);
        RoomName getCurrentRoom() const;
        bool isRoomUnlocked(RoomName room) const;
        void setCurrentRoom(const RoomName& newRoom);
        //~();

    private:
        //OutputScreens outscr;
       // Animation ani;
       Rooms room;
       RoomName currentRoom;
       


};
