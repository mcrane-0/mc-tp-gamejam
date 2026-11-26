
#include <string>
#include <vector>
//#include "OutputScreens.h"
//#include "Animation.h"
#include "GameState.h"
#include "Rooms.h"
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

        //OutputScreens outscr;
       // Animation ani;       

    GameState::GameState()
    {
        unlockedRooms.reserve(50);
        unlockedRooms = {GameState::RoomName::CrewQuarters, GameState::RoomName::BriefingRoom, GameState::RoomName::Airlock};
    }
    GameState::RoomName GameState::getCurrentRoom() const{return GameState::currentRoom;}
    bool GameState::isRoomUnlocked(RoomName room) const
    {
        return find(unlockedRooms.begin(), unlockedRooms.end(), room) != unlockedRooms.end();
    }
    void GameState::unlockRoom(GameState::RoomName room)
    {
        if (!isRoomUnlocked(room))
        GameState::unlockedRooms.emplace_back(room);
    }
    void GameState::setCurrentRoom(const GameState::RoomName& newRoom){currentRoom = newRoom;}

    void GameState::exitRoom(const GameState::RoomName& room)
    {
        switch (room)
        {
        case GameState::RoomName::FlightDeck:
        case GameState::RoomName::CrewQuarters:
        case GameState::RoomName::BriefingRoom:
        case GameState::RoomName::Airlock:
        case GameState::RoomName::MessHall:
        {
            setCurrentRoom(GameState::RoomName::RoomList);
            break;
        }
        case GameState::RoomName::RoomList:
        {
            break;
        }
        }
    }
    void GameState::enterRoom(const GameState::RoomName& room)
    {
        switch (room)
        {
            case GameState::RoomName::RoomList:
            {

            }
            case GameState::RoomName::FlightDeck:
            {

            }
            case GameState::RoomName::CrewQuarters:
            {

            }
            case GameState::RoomName::BriefingRoom:
            {
                roomObj.briefingRoom();
            }
            case GameState::RoomName::Airlock:
            {

            }
            case GameState::RoomName::MessHall:
            {

            }
        }

    }
    //~();
    
