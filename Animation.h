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
    void setEcho(bool echoState);//setEcho(true) enables cursor and echo, (false) disables both
    void flushPendingKeystrokes();//remove user input from buffer
    void resizeConsole();
    char _getchAnimation();
    void typingSpeed();

    void centeredTyping(const vector<string>& lines);//Typewriter effect
    void centeredTyping(const vector<string>& lines, const vector<string>& initialLines);//Second arg- 
    //-lets you specify which lines from the first arg should be printed immediately without typewriter effect
    void centeredTyping(const vector<string>& lines, const vector<string>& initialLines, int lineNumber, int extraPadding);//lets you add-
    //-horizontal padding to specified line
    char centeredTypingGetChar(const vector<string>& lines);//returns char with _getchAnimation
    char centeredTypingGetChar(const vector<string>& lines, const vector<string>& initialLines);
    string centeredTypingGetString(const vector<string>& lines, const vector<string>& initialLines); //takes string input after animation
//centeredTyping functions for chaining consecutive calls (never end a chain with one of these)
    void centeredTypingNoWait(const vector<string>& lines);
    void centeredTypingNoWait(const vector<string>& lines, const vector<string>& initialLines);
    void centeredTypingNoWait(const vector<string>& lines, int size);//lets you enforce # of lines in last call in chain-
    //-so that vertical padding is calculated accurately
    void centeredTypingNoWait(const vector<string>& lines, const vector<string>& initialLines, int size);
//Output Screens
    void clearScreen();
    void printTextScreen(const vector<string>& lines);
    string printTextScreenWithInput(const vector<string>& lines);
    void printFullScreen(const string& screen);

};