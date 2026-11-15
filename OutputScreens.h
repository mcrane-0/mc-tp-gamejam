#pragma once

#include <string>
#include <vector>

using namespace std;

class OutputScreens{
    public:
        OutputScreens();

        void clearScreen();

        void printTextScreen(vector<string> lines);
        void printTextScreenNoInput(vector<string> lines);
        string printTextWithInputScreen(vector<string> lines);
        char printTextWithCharInputScreen(vector<string> lines);

        void printCameraScreen(int page, int camerasAvailable, string bottomText);
        void printCameraScreen(int page, int camerasAvailable);
        void printCameraScreen();
        
};