#pragma once
#include<string>

//using namespace std;
using std::string;

class Player
{
public:
Player();
string getUserName();
void setUserName(string name);

private:
string userName;
};