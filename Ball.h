#pragma once
#include "box2d/box2d.h"
#include "Settings.h"
#include "SFML/Graphics.hpp"


class Ball
{
public:
	Ball(b2World& world);
	b2Body* ballBody;
	b2BodyDef ballBodyDef;
	b2CircleShape ballShape;
	b2FixtureDef ballFixtureDef;

	sf::CircleShape sfBall;
	void update();
};

