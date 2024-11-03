#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
class MainMenu
{
public:
	MainMenu(float height, float width);

	void moveDown();
	void moveUp();
	void draw(sf::RenderWindow& window);
	float width;
	float height;


	sf::Font font;
	sf::Text menu[2];
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	
	int selectedItemIndex;
};

