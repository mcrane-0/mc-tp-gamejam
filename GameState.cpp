
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
//using namespace std::ranges;

        //OutputScreens outscr;
        Animation aniObj;       

    GameState::GameState()
    {
        powerRestored = false;
        unlockedRooms.reserve(50);
        unlockedRooms = {GameState::RoomName::CrewQuarters, GameState::RoomName::BriefingRoom, GameState::RoomName::BriefingRoomIntro, GameState::RoomName::Airlock};
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

    void GameState::exitRoom()
    {
        aniObj.flushPendingKeystrokes();
        switch (currentRoom)
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
        case GameState::RoomName::FlightDeckIntro:
        case GameState::RoomName::BriefingRoomIntro:
        {
            enterRoom(GameState::RoomName::RoomList);
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
                setCurrentRoom(GameState::RoomName::RoomList);
                roomObj.roomList(*this);
                break;
            }
            case GameState::RoomName::FlightDeck:
            {

                break;
            }
            case GameState::RoomName::FlightDeckIntro:
            {
                setCurrentRoom(GameState::RoomName::FlightDeckIntro);
                roomObj.flightDeckIntro(*this);
                break;
            }
            case GameState::RoomName::CrewQuarters:
            {
                setCurrentRoom(GameState::RoomName::CrewQuarters);
                roomObj.crewQuarters(*this);
                break;
            }
            case GameState::RoomName::BriefingRoom:
            {
                break;
            }
            case GameState::RoomName::BriefingRoomIntro:
            {
                setCurrentRoom(GameState::RoomName::BriefingRoomIntro);
                roomObj.briefingRoomIntro(*this);
                break;
            }
            case GameState::RoomName::Airlock:
            {
                setCurrentRoom(GameState::RoomName::Airlock);
                roomObj.airlock(*this);
                break;
            }
            case GameState::RoomName::MessHall:
            {
                break;
            }
        }

    }
    //~();
    
