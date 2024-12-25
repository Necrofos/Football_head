#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
class Box {
public:
	//�����
	Box(b2World& world);

private:
	b2BodyDef groundBodyDef;
	b2Body* groundBody;
	b2PolygonShape groundBox;

	//����� �����
	b2BodyDef leftwallBodyDef;
	b2Body* leftwallBody;
	b2PolygonShape leftwallBox;
	b2FixtureDef leftwallFixtureDef;

	//������ �����
	b2BodyDef rightwallBodyDef;
	b2Body* rightwallBody;
	b2PolygonShape rightwallBox;
	b2FixtureDef rightwallFixtureDef;

	//�������
	b2BodyDef ceilingBodyDef;
	b2Body* ceilingBody;
	b2PolygonShape ceilingBox;

};