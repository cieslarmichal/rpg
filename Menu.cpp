#include "Menu.h"



Menu::Menu(sf::RenderWindow & win)
{
	window = &win;

	initialize();
}


Menu::~Menu()
{
	window = nullptr;
}


int Menu::chooseMode()
{
	while (window->isOpen())
	{
		clear();

		switch (events())
		{
		case (int)Action::CONFIRM:
			if (currentItemIndex == (int)Item::PLAY)
			{
				return (int)Mode::GAME;
			}
			else if (currentItemIndex == (int)Item::EXIT)
			{
				return (int)Mode::EXIT;
			}
			break;
		case (int)Action::CANCEL:
			return (int)Mode::EXIT;
			break;
		}

		update();
		draw();
	}

	return 0;
}

void Menu::initialize()
{
	font.loadFromFile("stuff/arial.ttf");

	menu[(int)Item::PLAY].setFont(font);
	menu[(int)Item::PLAY].setFillColor(sf::Color::Red);
	menu[(int)Item::PLAY].setString("Play");
	menu[(int)Item::PLAY].setPosition(sf::Vector2f(((float)window->getSize().x / 2), (float)window->getSize().y / (itemAmount + 1) * 1));

	menu[(int)Item::OPTIONS].setFont(font);
	menu[(int)Item::OPTIONS].setFillColor(sf::Color::White);
	menu[(int)Item::OPTIONS].setString("Options");
	menu[(int)Item::OPTIONS].setPosition(sf::Vector2f(((float)window->getSize().x / 2), (float)window->getSize().y / (itemAmount + 1) * 2));

	menu[(int)Item::EXIT].setFont(font);
	menu[(int)Item::EXIT].setFillColor(sf::Color::White);
	menu[(int)Item::EXIT].setString("Exit");
	menu[(int)Item::EXIT].setPosition(sf::Vector2f((float)(window->getSize().x / 2), (float)window->getSize().y / (itemAmount + 1) * 3));

	currentItemIndex = 0;
}

void Menu::currentItemUp()
{
	if (currentItemIndex > 0)
	{
		currentItemIndex--;
	}
	else
	{
		currentItemIndex = itemAmount - 1;
	}
}

void Menu::currentItemDown()
{
	if (currentItemIndex < itemAmount - 1)
	{
		currentItemIndex++;
	}
	else
	{
		currentItemIndex = 0;
	}
}

void Menu::update()
{
	for (int itemIndex = 0; itemIndex < itemAmount; itemIndex++)
	{
		menu[itemIndex].setFillColor(sf::Color::White);
	}

	menu[currentItemIndex].setFillColor(sf::Color::Red);
}

void Menu::draw()
{
	for (auto item : menu)
	{
		window->draw(item);
	}

	window->display();
}

void Menu::clear()
{
	window->clear();
}

int Menu::events()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				currentItemUp();
				break;
			case sf::Keyboard::Down:
				currentItemDown();
				break;
			case sf::Keyboard::Escape:
				window->close();
				return (int)Action::CANCEL;
				break;
			case sf::Keyboard::Enter:
				return (int)Action::CONFIRM;
			}
			break;

		case sf::Event::Closed:
			window->close();
			return (int)Action::CANCEL;
		}
	}
	return (int)Action::NO_ACTION;
}

