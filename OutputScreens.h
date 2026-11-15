#pragma once

#include <string>
#include <vector>

using namespace std;

class OutputScreens{
    public:
        OutputScreens();

        void clearScreen();

        void printTextScreen(const vector<string>& lines);
        void printTextScreenNoInput(const vector<string>& lines);
        string printTextWithInputScreen(const vector<string>& lines);
        char printTextWithCharInputScreen(const vector<string>& lines);

        void printCameraScreen(int page, int camerasAvailable, string bottomText);
        void printCameraScreen(int page, int camerasAvailable);
        void printCameraScreen();
        
};