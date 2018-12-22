#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Skeleton.h"
#include "Obstacle.h"
#include "Projectile.h"
#include <memory>

class Rect
{
public:
	Rect(Player &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
	Rect(Skeleton &, int dimX, int dimY, sf::Vector2f pos = { 0,0 });
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
	int getLeftEdge() const;
	int getRightEdge() const;
	int getTopEdge() const;
	int getBottomEdge() const;
	int getDimX() const;
	int getDimY() const;
	sf::Vector2f getPosition() const;
private:
	int leftEdge, rightEdge, topEdge, bottomEdge;
	int dimX, dimY;
};

