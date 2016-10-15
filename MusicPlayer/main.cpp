#include <iostream>
#include "windows.h"
#include <string>
#include "MP3Player.h"
#include "Timer.h"
#include <thread>

int main()
{
    MP3Player MP;
    Timer Counter;
    MP.open();
    std::thread mpThread(&MP3Player::play, &MP);
    Counter.stopSignal = MP.stopSignal;
    std::thread clkThread(&Timer::showTime, &Counter);
    mpThread.join();
    clkThread.join();

    exit(EXIT_SUCCESS);
}
