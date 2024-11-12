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

	b2Body* bootBody;
	b2BodyDef bootBodyDef;
	b2FixtureDef bootFixtureDef;

	sf::Texture playerTexture;

	sf::Sprite bootSprite;
	sf::Texture bootTexture;

	bool isKicking;
	float kickTimer = 0.0f;
	int score;
	bool wasJumping;
	int direction;
	float currentRotation;


	void move();

	void update();

	void jump();

	virtual void kick(Ball& ball) = 0;
	void animateKick();
	
};

class Player1 : public Player {
public:
	Player1(b2World& world, sf::Color color, b2Vec2 position) : Player(world, color, position) {
		bootTexture.loadFromFile("icons/boots/shoeL.png");
		bootSprite.setTexture(bootTexture);
		playerTexture.loadFromFile("icons/heads/P1.png");
		sfPlayer.setTexture(&playerTexture);
	}
	void kick(Ball& ball) override;
};

class Player2 : public Player {
public:
	Player2(b2World& world, sf::Color color, b2Vec2 position) : Player(world, color, position) {

		bootTexture.loadFromFile("icons/boots/shoeR.png");
		bootSprite.setTexture(bootTexture);
		playerTexture.loadFromFile("icons/heads/P2.png");
		sfPlayer.setTexture(&playerTexture);
	}
	void kick(Ball& ball) override;
};

