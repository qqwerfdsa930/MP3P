#include "Timer.h"

Timer::Timer()
{
	tData.min = 0;
	tData.sec = 0;
}

Timer::~Timer()
{

}


void Timer::showTime()
{
    while(!ifStop)
    {
        std::string minOut, secOut;
        tData.sec++;
        if (tData.sec == 60)
        {
            tData.min++;
            tData.sec = 0;
        }
        minOut = std::to_string(tData.min);
        if(tData.min < 10)
            minOut.insert(0, 1, '0');
        ui.write(minOut, {10, 5});
        ui.write(" : ", {13, 5});
        secOut = std::to_string(tData.sec);
        if(tData.sec < 10)
            secOut.insert(0, 1, '0');
        ui.write(secOut, {17, 5});

        waitForNextSec();
    }
    if(ifStop)
    {
        tData.min = 0;
        tData.sec = 0;
    }
}

void Timer::waitForNextSec()
{
	Sleep(1000);
}

void Timer::start()
{

}

void Timer::stop()
{

}

void Timer::getMin()
{

}

void Timer::getSec()
{

}
