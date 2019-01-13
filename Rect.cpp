#include "Rect.h"


Rect::Rect(Player & p, int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	player = std::unique_ptr<Player>(new Player(p));
	character = &(*player);
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Npc & n, int dx, int dy, sf::Vector2f pos) :dimX(dx), dimY(dy)
{
	npc = std::unique_ptr<Npc>(new Npc(n));
	character = &(*npc);
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Black);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Skeleton & s, int dx, int dy, sf::Vector2f pos) :dimX(dx), dimY(dy)
{
	enemy = std::unique_ptr<Enemy>(new Skeleton(s));
	character = &(*enemy);
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(SkeletonBerserker & sb, int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	enemy = std::unique_ptr<Enemy>(new SkeletonBerserker(sb));
	character = &(*enemy);
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Dragon & d, int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	enemy = std::unique_ptr<Enemy>(new Dragon(d));
	character = &(*enemy);
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Obstacle & o, int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	obstacle = std::unique_ptr<Obstacle>(new Obstacle(o));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Projectile & p, int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	projectile = std::unique_ptr<Projectile>(new Projectile(p));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Item & it, int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	item = std::unique_ptr<Item>(new Item(it));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color(181, 155, 124, 255));
	rect.setPosition(pos);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	setEdges();
}

Rect::Rect(int dx, int dy, sf::Vector2f pos) : dimX(dx), dimY(dy)
{
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color(181, 155, 124, 255));
	rect.setPosition(pos);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
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
	bottomEdge = inp;
}

//getters

int Rect::getLeftEdge()
{
	setEdges();

	return leftEdge;
}

int Rect::getRightEdge()
{
	setEdges();

	return rightEdge;
}

int Rect::getTopEdge()
{
	setEdges();
	return topEdge;
}

int Rect::getBottomEdge()
{
	setEdges();

	return bottomEdge;
}

sf::Vector2f Rect::getPosition() const
{
	return rect.getPosition();
}

const sf::RectangleShape & Rect::getRect() const
{
	return rect;
}

sf::RectangleShape & Rect::getRect()
{
	return rect;
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
	leftEdge = (int)rect.getPosition().x;
	rightEdge = (int)rect.getPosition().x + dimX;
	bottomEdge = (int)rect.getPosition().y + dimY;
	topEdge = (int)rect.getPosition().y;
}
