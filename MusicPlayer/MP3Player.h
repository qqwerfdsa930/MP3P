#ifndef MP3PLAYER_H
#define MP3PLAYER_H
#include <string>
#include <vector>
#include "windows.h"
#include <iostream>
#include <fstream>
#include <thread>
#include "bass.h"
#include "UI.h"
#include "Timer.h"



class MP3Player
{
    public:
        MP3Player();
        ~MP3Player();
        void showUI();
        void open();
        void play();
        void close();
        void stop();

    private:
        UI ui;
        HSTREAM hStream;
        void updateStat();
        void updateMenu();
        std::string fileName;
        std::ifstream musicFile;
        std::vector<std::string> menuList;
        int selectedMenuItem;
        Timer counter;
};

#endif // MP3PLAYER_H
