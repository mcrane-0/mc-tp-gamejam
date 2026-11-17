#pragma once

#include <string>
#include <vector>
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

class OutputScreens{
    public:
        OutputScreens();
        ~OutputScreens();
        void setEcho(bool enableEcho);

        void clearScreen();
        void flushPendingKeystrokes();
        // printTextScreen
        void printTextScreen(const vector<string>& lines);
        void printTextScreenNoInput(const vector<string>& lines);
        string printTextScreenWithInput(const vector<string>& lines);
        char printTextScreenWithCharInput(const vector<string>& lines);

        // printCameraScreen
        void printCameraScreen(int page, int camerasAvailable, string bottomText);
        void printCameraScreen(int page, int camerasAvailable);
        void printCameraScreen();
        void printCameraList();
        
};