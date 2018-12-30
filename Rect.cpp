#include "Rect.h"



Rect::Rect(Player & p, int dx, int dy, sf::Vector2f pos) : obstacle(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	character = std::unique_ptr<Player>(new Player(p));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Skeleton & s, int dx, int dy, sf::Vector2f pos) :obstacle(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	character = std::unique_ptr<Enemy>(new Skeleton(s));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Dragon & d, int dx, int dy, sf::Vector2f pos) :obstacle(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	character = std::unique_ptr<Enemy>(new Dragon(d));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Obstacle & o, int dx, int dy, sf::Vector2f pos) : character(nullptr), projectile(nullptr), dimX(dx), dimY(dy)
{
	obstacle = std::unique_ptr<Obstacle>(new Obstacle(o));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	setEdges();
}

Rect::Rect(Projectile & p, int dx, int dy, sf::Vector2f pos) : character(nullptr), obstacle(nullptr), dimX(dx), dimY(dy)
{
	projectile = std::unique_ptr<Projectile>(new Projectile(p));
	rect.setSize(sf::Vector2f((float)dimX, (float)dimY));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	setEdges();
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
	//sf::Vector2i position;
	//int x = (int)rect.getPosition().x;
	//int amountOfTiles = x / 40;
	//if (x % 40 > 0)
	//{
	//	position.x = amountOfTiles * 40 + 40;
	//}
	//else
	//{
	//	position.x = amountOfTiles * 40;
	//}

	//int y = (int)rect.getPosition().y;
	//amountOfTiles = y / 40;
	//if (y % 40 > 0)
	//{
	//	position.y = amountOfTiles * 40 + 40;
	//}
	//else
	//{
	//	position.y = amountOfTiles * 40;
	//}

	//leftEdge = position.x;
	//rightEdge = position.x + dimX;
	//bottomEdge = position.y + dimY;
	//topEdge = position.y;

	//setPreviousEdges();
	leftEdge = (int)rect.getPosition().x;
	rightEdge = (int)rect.getPosition().x + dimX;
	bottomEdge = (int)rect.getPosition().y + dimY;
	topEdge = (int)rect.getPosition().y;
}

void Rect::setPreviousEdges()
{
	//previousBottomEdge = bottomEdge;
	//previousTopEdge = topEdge;
	//previousLeftEdge = leftEdge;
	//previousRightEdge = rightEdge;

	//if (character != nullptr)
	//{
	//	switch (character->getDirection())
	//	{
	//	case (int)Directions::UP:
	//		previousBottomEdge = bottomEdge + dimY;
	//		previousTopEdge = topEdge + dimY;
	//		break;
	//	case (int)Directions::DOWN:
	//		previousBottomEdge = bottomEdge - dimY;
	//		previousTopEdge = topEdge - dimY;
	//		break;
	//	case (int)Directions::LEFT:
	//		previousLeftEdge = leftEdge + dimX;
	//		previousRightEdge = rightEdge + dimX;
	//		break;
	//	case (int)Directions::RIGHT:
	//		previousLeftEdge = leftEdge - dimX;
	//		previousRightEdge = rightEdge - dimX;
	//		break;
	//	default:
	//		break;
	//	}
	//}
}

void Rect::setWanna(bool & w) // wish to turn somewhere
{
	wannaLeft = false;
	wannaRight = false;
	wannaUp = false;
	wannaDown = false;
	w = true;
}
