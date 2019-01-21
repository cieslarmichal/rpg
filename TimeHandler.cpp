#include "TimeHandler.h"

TimeHandler::TimeHandler()
{
	elapsed = clock.getElapsedTime();
}

void TimeHandler::reset()
{
	clock.restart();
}

float TimeHandler::getElapsedSeconds()
{
	elapsed = clock.getElapsedTime();
	return elapsed.asSeconds();
}

float TimeHandler::getElapsedAndReset()
{
	return clock.restart().asSeconds();
}


