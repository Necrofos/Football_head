#pragma once
#include "SFML/Graphics.hpp"
#include <string>
class Score
{
public:
	Score();
	void updateText();
	void updateScore(int playerNumber);
	void draw(sf::RenderWindow& window);


	sf::Vector2f position;
	int player1;
	int player2;
	sf::Font font;

	sf::Text text;
	sf::Text score1;
	sf::Text score2;
	sf::Text timer;
	std::string fontPath;
	sf::Texture texture;
	sf::RectangleShape boardShape;


};

