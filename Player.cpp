#include "Player.h"

Player::Player() : userName(""){};

string Player::getUserName()
{
return userName;
};
void Player::setUserName(string name)
{
    userName = name;
};