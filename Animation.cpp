#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Animation.h"

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <termios.h>
#include <unistd.h>
#endif
#ifdef __linux__
#include <cstring>
#include <termios.h>
#include <unistd.h>
#endif


using namespace std;
using namespace std::chrono;

//bool echo_altered = false;//safety flag prevents overwriting

Animation::Animation(){};
Animation::~Animation(){ if (echo_altered) {
            setEcho(true);
        }};
 void Animation::setEcho(bool echoState) {
    #ifdef __APPLE__
        if (!echoState) {
            if (!echo_altered) {
                tcgetattr(STDIN_FILENO, &saved_tio);//backup terminal settings
                echo_altered = true;
            }
            termios new_tio = saved_tio;
            cout << "\033[?25l" << flush;
            new_tio.c_lflag &= ~ECHO;//disable echo
            tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
        } else if (echo_altered) {
            // Restore terminal settings
            cout << "\033[?25h" << flush;
            tcsetattr(STDIN_FILENO, TCSANOW, &saved_tio);
            echo_altered = false;
        }
        #endif
    }
#if defined(__APPLE__) || defined(__linux__)
char Animation::_getchAnimation() 
{
    struct termios savedTerm, tempTerm;
    char ch;

    tcgetattr(STDIN_FILENO, &savedTerm);
    tempTerm = savedTerm;//copy settings into temp settings
    tempTerm.c_lflag &= ~(ICANON | ECHO); //turn off line buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &tempTerm);//apply temp settings
    ch = getchar();//get char
    tcsetattr(STDIN_FILENO, TCSANOW, &savedTerm);//restore original settings
    return ch;
}
#elif defined(_WIN32)
char _getchAnimation()
{
    _getch();
}
#endif

    void Animation::flushPendingKeystrokes()
    {
    #if defined(__APPLE__) || defined(__linux__)
    tcflush(STDIN_FILENO, TCIFLUSH);

  /*  #elif defined(__linux__)
    unsigned long* tmpstdin = (unsigned long*)stdin;
    unsigned long* oldbuf = (unsigned long*)*(tmpstdin+4);
    free((void*)oldbuf);
    *tmpstdin=(unsigned long)0xfbad2088;
    tmpstdin+=1;
    memset(tmpstdin,'\x00',64);
    */
    #elif defined(_WIN32)
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin != INVALID_HANDLE_VALUE) {
        FlushConsoleInputBuffer(hStdin);
    }
    #endif
    }
    void Animation::resizeConsole()
    {
        #if defined(__APPLE__) || defined(__linux__)
            cout << "\033[8;25;80t" << flush;
        #elif defined(_WIN32)
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            SMALL_RECT tiny = {0, 0, 1, 1};
            SetConsoleWindowInfo(hOut, TRUE, &tiny);
            COORD buffer = {80, 25};
            SetConsoleScreenBufferSize(hOut, buffer);
            SMALL_RECT window = {0, 0, 79, 24};
            SetConsoleWindowInfo(hOut, TRUE, &window);
        #endif
    }
    void Animation::centeredTyping(const vector<string>& lines)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
        int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);
        int totalChars = 0;

        for (const string& line : lines)
        {
            totalChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = 0; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < lowerBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        setEcho(true);
        this_thread::sleep_for(1s);
        cout << "\033[H" << "\n| " << "(PRESS ENTER TO CONTINUE)";
        cin.ignore();
        cout << "\033[?1049l" << flush;
        
    
    
    }
        // centeredTyping() with initial state
        void Animation::centeredTyping(const vector<string>& lines, const vector<string>& initialLines)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
        int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);
        int totalChars = 0;
        int initialChars = 0;
        for (const string& line : lines)
        {
            totalChars += line.length();
        }
        for (const string& line : initialLines)
        {
            initialChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = initialChars; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < lowerBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        setEcho(true);
        this_thread::sleep_for(1s);
        cout << "\033[H" << "\n| " << "(PRESS ENTER TO CONTINUE)";
        cin.ignore();
        cout << "\033[?1049l" << flush;
    }

            void Animation::centeredTyping(const vector<string>& lines, const vector<string>& initialLines, int lineNumber, int extraPadding)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
        int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);
        int totalChars = 0;
        int initialChars = 0;
        for (const string& line : lines)
        {
            totalChars += line.length();
        }
        for (const string& line : initialLines)
        {
            initialChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = initialChars; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            int linecount = 0;
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars;
                int rightBlankChars;
                ++linecount;
                if (linecount == lineNumber)
                {
                    leftBlankChars = ((extraPadding + terminalWidth - static_cast<int>(line.length())) / 2);
                    rightBlankChars = (extraPadding + terminalWidth - static_cast<int>(line.length()) - leftBlankChars);

                }
                else
                {
                    leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                    rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                }
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < lowerBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        setEcho(true);
        this_thread::sleep_for(1s);
        cout << "\033[H" << "\n| " << "(PRESS ENTER TO CONTINUE)";
        cin.ignore();
        cout << "\033[?1049l" << flush;
    }


        void Animation::centeredTypingNoWait(const vector<string>& lines, int size)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - size) / 2 );
        int lowerBlankLines = (terminalHeight - size - upperBlankLines);
                //int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
                //int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);

        int totalChars = 0;

        for (const string& line : lines)
        {
            totalChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = 0; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }       

            // bottom blank spaces print
            
            for (int i = 0; i < (lowerBlankLines + (size - static_cast<int>(lines.size()))); i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        //setEcho(true);        
    }

    //no wait after centeredTyping animation
        void Animation::centeredTypingNoWait(const vector<string>& lines)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
        int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);
        int totalChars = 0;

        for (const string& line : lines)
        {
            totalChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = 0; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < lowerBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        //setEcho(true);
        //cout << "\033[?1049l" << flush;
    }
        void Animation::centeredTypingNoWait(const vector<string>& lines, const vector<string>& initialLines)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
        int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);
        int totalChars = 0;
        int initialChars = 0;
        for (const string& line : lines)
        {
            totalChars += line.length();
        }
        for (const string& line : initialLines)
        {
            initialChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = initialChars; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < lowerBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        //setEcho(true);
        //cout << "\033[?1049l" << flush;
    }
    void Animation::centeredTypingNoWait(const vector<string>& lines, const vector<string>& initialLines, int size)
    {
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - size) / 2 );
        int lowerBlankLines = (terminalHeight - size - upperBlankLines);
        int totalChars = 0;
        int initialChars = 0;
        for (const string& line : lines)
        {
            totalChars += line.length();
        }
        for (const string& line : initialLines)
        {
            initialChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = initialChars; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < (lowerBlankLines + (size - static_cast<int>(lines.size()))); i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        //setEcho(true);
        //cout << "\033[?1049l" << flush;
    }
        // centeredTyping() with initial state that gets char
        char Animation::centeredTypingGetChar(const vector<string>& lines, const vector<string>& initialLines)
    {
        char input;
        int terminalWidth = 78;
        int terminalHeight = 23;
        int upperBlankLines = ( (terminalHeight - lines.size()) / 2 );
        int lowerBlankLines = (terminalHeight - lines.size() - upperBlankLines);
        int totalChars = 0;
        int initialChars = 0;
        for (const string& line : lines)
        {
            totalChars += line.length();
        }
        for (const string& line : initialLines)
        {
            initialChars += line.length();
        }

        cout << "\033[3J" << "\033[?1049h" << flush;
        setEcho(false);
        resizeConsole();
        for (int frameCount = initialChars; frameCount <= totalChars; ++frameCount)//1 character printed per frame
        {
            string frame;
            frame.reserve(2100);//pre-allocate all the available characters on screen
            int charsAvailable = frameCount;//in frame 1, 1 char slot is available, in frame 30 30 char slots are available
            int charsPrinted;//valid maximum chars we can print on a line, also considering charsAvailable


            frame += "\033[H";//move cursor to top left
            frame += string(80, '-') + "\n";//render top line
            // top blank spaces print
            for (int i = 0; i < upperBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";//render into string instead of using cout
                //cout << "|                                                                              |" << "\n";
            }
            
            // left-to-right centering
            for (const string& line : lines)
            {
                int leftBlankChars = ((terminalWidth - static_cast<int>(line.length())) / 2);
                int rightBlankChars = (terminalWidth - static_cast<int>(line.length()) - leftBlankChars);
                if (line.length() < charsAvailable)
                {
                    charsPrinted = line.length();
                }
                else
                {
                    charsPrinted = charsAvailable;
                }
                charsAvailable -= charsPrinted;
                string printed = line.substr(0, charsPrinted);
                string unprinted = string(line.length() - charsPrinted, ' ');
                //frame containing text is rendered
                frame += "|" + string(leftBlankChars, ' ') + printed + unprinted
                + string(rightBlankChars, ' ') + "|\n";
            }            
            // bottom blank spaces print
            for (int i = 0; i < lowerBlankLines; i++)
            {
                frame += "|" + string(terminalWidth, ' ') + "|\n";
            }
            frame += string(79, '-');
            cout << frame << flush;
            this_thread::sleep_for(0.05s);
        }
        flushPendingKeystrokes();
        this_thread::sleep_for(1s);
        input = _getchAnimation();
        setEcho(true);
        cout << "\033[H" << "\n| ";
        cout << "\033[?1049l" << flush;
        return input;
    }




    //void Animation::centeredTyping(const vector<string>& lines)
    //{
    //    Animation::centeredTyping(lines);
    //}