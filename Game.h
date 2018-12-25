#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Character.h"
#include "Draw.h"
#include "Rect.h"
#include "Sprite.h"
#include "Player.h"
#include "Input.h"
#include "Movement.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Obstacle.h"
#include "Wrapper.h"
#include "Update.h"
#include "CollisionHandler.h"
#include "Delete.h"
#include "Create.h"
#include "Mark.h"
#include "Shoot.h"
#include "Notifications.h"

class Game
{
public:
	Game();
	~Game();
	bool play();
private:
	void clearWindow(sf::RenderWindow & window);
};
