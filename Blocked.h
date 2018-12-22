#pragma once

class Blocked {
public:
	friend class CollisionHandler;
	bool isDestroyed() const;
	void setDestroyed(bool);
private:
	Blocked(int ind, int dirc);
	enum { PLAYERINDEX = -1 };
	int characterIndex;
	int blockedDirection;
	bool destroyed;
};
