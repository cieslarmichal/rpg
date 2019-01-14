#include "TimeHandler.h"



TimeHandler::TimeHandler()
{
	elapsed = clock.getElapsedTime();
	elapsed2 = clock2.getElapsedTime();
}

void TimeHandler::reset()
{
	clock.restart();
}

void TimeHandler::reset2()
{
	clock2.restart();
}

float TimeHandler::getElapsedSeconds()
{
	elapsed = clock.getElapsedTime();
	return elapsed.asSeconds();
}

float TimeHandler::getElapsedSeconds2()
{
	elapsed2 = clock2.getElapsedTime();
	return elapsed2.asSeconds();
}
