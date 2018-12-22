#pragma once

class Blocked {
	friend class CollisionHandler;
private:
	Blocked(int ind, int dirc);
	bool isDestroyed() const;
private:
	enum { PLAYERINDEX = -1 };
	int characterIndex;
	int blockedDirection;
	bool destroyed;
};