#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include "windows.h"

class Timer
{
public:
    struct Time_data
	{
		unsigned int min;
		unsigned int sec;
	};

	Timer();
	~Timer();
	void showTime();
	Time_data tData;
	std::string clk;
	void waitForNextSec();
	void start();
	void stop();
	bool stopSignal;
	void getMin();
	void getSec();


};

#endif // TIMER_H
