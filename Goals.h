#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Settings.h"

class Goal {
public:
    Goal(b2World& world, bool isLeft);

    float goalWidth;
    float goalHeight;
    float roofHeight;
    float roofWidth;
    float xPosition;
    float xRoof;
    void draw(sf::RenderWindow& window);
    b2BodyDef verticalBodyDef;
    b2BodyDef horizontalBodyDef;
    b2Body* verticalBody;
    b2Body* horizontalBody;

    b2PolygonShape verticalPolygon;
    b2PolygonShape horizontalPolygon;

    sf::RectangleShape SFverticalShape;
    sf::RectangleShape SFhorizontalShape;

};