#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Skeleton.h"
#include "Dragon.h"
#include "Obstacle.h"
#include "Projectile.h"
#include "Item.h"
#include <memory>

class Rect
{
public:
	Rect(Player &, int dimX, int dimY, sf::Vector2f position);
	Rect(Skeleton &, int dimX, int dimY, sf::Vector2f position);
	Rect(Dragon &, int dimX, int dimY, sf::Vector2f position);
	Rect(Obstacle &, int dimX, int dimY, sf::Vector2f position);
	Rect(Projectile &, int dimX, int dimY, sf::Vector2f position);
	Rect(Item &, int dimX, int dimY, sf::Vector2f position);
	Character * character;
	std::unique_ptr<Player> player = nullptr;
	std::unique_ptr<Enemy> enemy = nullptr;
	std::unique_ptr<Obstacle> obstacle = nullptr;
	std::unique_ptr<Projectile> projectile = nullptr;
	std::unique_ptr<Item> item = nullptr;
	void setEdges();
	void setLeftEdge(int);
	void setRightEdge(int);
	void setTopEdge(int);
	void setBottomEdge(int);
	int getLeftEdge();
	int getRightEdge();
	int getTopEdge();
	int getBottomEdge();
	int getDimX() const;
	int getDimY() const;
	const sf::RectangleShape & getRect() const;
	sf::RectangleShape & getRect();
	sf::Vector2f getPosition() const;
	sf::Vector2f velocity{ 0,0 };
private:
	sf::RectangleShape rect;
	int leftEdge, rightEdge, topEdge, bottomEdge;
	int dimX, dimY;
};
