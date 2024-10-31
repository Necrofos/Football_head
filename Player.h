#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Settings.h"
#include "Ball.h"



class Player
{
public:
	Player(b2World& world, sf::Color color, b2Vec2 position);
	b2Body* playerBody;
	b2BodyDef playerBodyDef;
	b2CircleShape playerShape;
	b2FixtureDef playerFixtureDef;
	sf::CircleShape sfPlayer;
	int score;
	bool wasJumping;


	void move(int direction);

	void update();

	void jump();

	virtual void kick(Ball& ball) = 0;
};

class Player1 : public Player {
public:
	Player1(b2World& world, sf::Color color, b2Vec2 position) : Player(world, color, position) {};
	void kick(Ball& ball) override;
};

class Player2 : public Player {
public:
	Player2(b2World& world, sf::Color color, b2Vec2 position) : Player(world, color, position) {};
	void kick(Ball& ball) override;
};

