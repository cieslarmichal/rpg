#include "TimeHandler.h"



TimeHandler::TimeHandler()
{
	elapsed = clock.getElapsedTime();
}

void TimeHandler::reset()
{
	clock.restart();
}

int TimeHandler::getElapsedSeconds()
{
	elapsed = clock.getElapsedTime();
	return (int)elapsed.asSeconds();
}
