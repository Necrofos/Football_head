#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
class MainMenu
{
public:
	MainMenu(float height, float width);

	void moveDown();
	void moveUp();
	void draw(sf::RenderWindow& window);
	void playMusic();
	void stopMusic();
	void playClick();
	bool isPlaySelected();
private:
	float width;
	float height;
	sf::Font font;
	sf::Text menu[2];
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Music music;
	sf::Music click;
	
	int selectedItemIndex;
};

