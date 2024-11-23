#pragma once
#include "box2d/box2d.h"
#include "Settings.h"
#include "SFML/Graphics.hpp"


class Ball
{
public:
	Ball(b2World& world);
	void update();

	//���������� 
	b2Body* getBallBody();

	//���������� sf::CircleShape
	sf::CircleShape getSFBall();

	//���������� ���������� ������ ���� � ������� Box2D
	b2Vec2 getPosition();

	void returnInInitialState();
private:
	b2Body* ballBody;
	b2BodyDef ballBodyDef;
	b2CircleShape ballShape;
	b2FixtureDef ballFixtureDef;

	b2Vec2 ballStartPosition;

	sf::CircleShape sfBall;
	sf::Texture ballTexture;

};

