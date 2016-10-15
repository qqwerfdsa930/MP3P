#ifndef MP3PLAYER_H
#define MP3PLAYER_H
#include <string>
#include "windows.h"
#include <iostream>
#include <fstream>
#include <thread>
#include "bass.h"



class MP3Player
{
    public:
        MP3Player();
        ~MP3Player();
        void open();
        void play();
        void close();
        bool ifStop();
        bool stopSignal;

    private:
        HSTREAM hStream;
        std::string fileName;

};

#endif // MP3PLAYER_H
