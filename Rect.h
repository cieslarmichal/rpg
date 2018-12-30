#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Skeleton.h"
#include "Dragon.h"
#include "Obstacle.h"
#include "Projectile.h"
#include <memory>

class Rect
{
public:
	Rect(Player &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
	Rect(Skeleton &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
	Rect(Dragon &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
	Rect(Obstacle &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
	Rect(Projectile &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
	std::unique_ptr<Character> character;
	std::unique_ptr<Obstacle> obstacle;
	std::unique_ptr<Projectile> projectile;
	sf::RectangleShape rect;
	//setters
	void setEdges();
	void setLeftEdge(int);
	void setRightEdge(int);
	void setTopEdge(int);
	void setBottomEdge(int);
	//getters
	int getLeftEdge();
	int getRightEdge();
	int getTopEdge();
	int getBottomEdge();
	int getDimX() const;
	int getDimY() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f velocity{ 0,0 };
	//sf::Vector2i getTilePosition() const;

	void setPreviousEdges();
	void setWanna(bool & w);
	bool wannaUp{ false }, wannaDown{ false }, wannaRight{ false }, wannaLeft{ false };
	int previousLeftEdge, previousRightEdge, previousTopEdge, previousBottomEdge;
private:
	int leftEdge, rightEdge, topEdge, bottomEdge;
	int dimX, dimY;
};
