#pragma once

#include <string>
#include <vector>
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class Animation
{
public:
    bool echo_altered = false;
#ifdef __APPLE__
struct termios saved_tio;
#endif
    Animation();
    ~Animation();
    void setEcho(bool echoState);
    void flushPendingKeystrokes();
    void resizeConsole();
    void centeredTyping(const vector<string>& lines);

};