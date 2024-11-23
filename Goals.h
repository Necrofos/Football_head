#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Settings.h"

class Goal {
public:
    Goal(b2World& world, bool isLeft);
    void draw(sf::RenderWindow& window);

    //возвращает координату центра прямоугольника верхней крыши ворот в системе координат Box2D
    b2Vec2 getRoofPosition();
    float goalWidth;
    float goalHeight;
    float roofHeight;
    float roofWidth;
    float xPosition;
    float xRoof;
    b2BodyDef verticalBodyDef;
    b2BodyDef horizontalBodyDef;
    b2Body* verticalBody;
    b2Body* horizontalBody;

    b2PolygonShape verticalPolygon;
    b2PolygonShape horizontalPolygon;

    sf::RectangleShape SFverticalShape;
    sf::RectangleShape SFhorizontalShape;

    sf::RectangleShape sfGoalShape;
    sf::Texture goalTexture;
};