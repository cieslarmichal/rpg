#include "Rect.h"



Rect::Rect(Player & p, int dx, int dy, sf::Vector2f pos) : obstacle(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	character = std::unique_ptr<Player>(new Player(p));
	rect.setSize(sf::Vector2f(dimX, dimY));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Skeleton & s, int dx, int dy, sf::Vector2f pos) :obstacle(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	character = std::unique_ptr<Enemy>(new Skeleton(s));
	rect.setSize(sf::Vector2f(dimX, dimY));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Obstacle & o, int dx, int dy, sf::Vector2f pos) : character(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	obstacle = std::unique_ptr<Obstacle>(new Obstacle(o));
	rect.setSize(sf::Vector2f(dimX, dimY));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Projectile & p, int dx, int dy, sf::Vector2f pos) : character(nullptr), obstacle(nullptr), dimX(dx), dimY(dy)
{
	projectile = std::unique_ptr<Projectile>(new Projectile(p));
	rect.setSize(sf::Vector2f(dimX, dimY));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Rect & r)
{
	leftEdge = r.leftEdge;
	rightEdge = r.rightEdge;
	topEdge = r.topEdge;
	bottomEdge = r.bottomEdge;
	dimX = r.dimX;
	dimY = r.dimY;
	rect = r.rect;
	character = std::move(r.character);
	projectile = std::move(r.projectile);
	obstacle = std::move(r.obstacle);
}

Rect & Rect::operator=(Rect & r)
{
	leftEdge = r.leftEdge;
	rightEdge = r.rightEdge;
	topEdge = r.topEdge;
	bottomEdge = r.bottomEdge;
	dimX = r.dimX;
	dimY = r.dimY;
	rect = r.rect;
	character = std::move(r.character);
	obstacle = std::move(r.obstacle);
	projectile = std::move(r.projectile);
	return *this;
}

//setters
void Rect::setLeftEdge(int inp)
{
	leftEdge = inp;
}

void Rect::setRightEdge(int inp)
{
	rightEdge = inp;
}

void Rect::setTopEdge(int inp)
{
	topEdge = inp;
}

void Rect::setBottomEdge(int inp)
{
	bottomEdge=inp;
}

//getters

int Rect::getLeftEdge() const
{
	return leftEdge;
}

int Rect::getRightEdge() const
{
	return rightEdge;
}

int Rect::getTopEdge() const
{
	return topEdge;
}

int Rect::getBottomEdge() const
{
	return bottomEdge;
}

sf::Vector2f Rect::getPosition() const
{
	return rect.getPosition();
}


int Rect::getDimX() const
{
	return dimX;
}

int Rect::getDimY() const
{
	return dimY;
}

void Rect::setEdges()
{
	leftEdge = rect.getPosition().x;
	rightEdge = rect.getPosition().x + dimX;
	bottomEdge = rect.getPosition().y + dimY;
	topEdge = rect.getPosition().y;
}


