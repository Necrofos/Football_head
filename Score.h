#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "box2d/box2d.h"
class Score
{
public:
	Score(b2World& world);
	void updateText();
	void updateScore(int playerNumber);
	void render(sf::RenderWindow& window);
	void returnInInitialState();
	int getScorePlayer1();
	int getScorePlayer2();
	int getTimeRemaining();

private:
	sf::Vector2f position;

	int timeRemaining;
	sf::Font font;
	int player1;
	int player2;

	sf::Text text;
	sf::Text score1;
	sf::Text score2;
	std::string fontPath;
	sf::Texture texture;
	sf::RectangleShape boardShape;

	sf::Text player1Label;
	sf::Text player2Label;
	sf::Text timerText;
	sf::Clock gameClock;
};