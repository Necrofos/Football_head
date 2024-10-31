#pragma once
#include "SFML/Graphics.hpp"
class MainMenu
{
public:
	MainMenu(float height, float width);

	void moveDown();
	void moveUp();
	void update();
	void draw(sf::RenderWindow& window);
	int GetPressedItem();
	float width;
	float height;


	sf::Font font;
	sf::Text menu[2];
	static const int MAX_NUMBER_OF_ITEMS = 2;
	int selectedItemIndex;
};

