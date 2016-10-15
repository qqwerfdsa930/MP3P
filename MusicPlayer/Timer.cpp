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
    while (!stopSignal)
    {


        tData.sec++;

        if (tData.sec == 60)
        {
            tData.min++;
            tData.sec = 0;
        }
        clk = std::to_string(tData.min) + " : " + std::to_string(tData.sec);
        waitForNextSec();
        std::cout << clk << std::endl;
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
