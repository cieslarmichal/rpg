#include "Blocked.h"

Blocked::Blocked(int ind, int dirc) :characterIndex(ind), blockedDirection(dirc), destroyed(false) {}

bool Blocked::isDestroyed() const
{
	return destroyed;
}

void Blocked::setDestroyed(bool inp)
{
	destroyed = inp;
}
