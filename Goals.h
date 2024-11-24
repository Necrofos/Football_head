#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Settings.h"
#include <iostream>

class Goal {
public:
    Goal(b2World& world);
    void render(sf::RenderWindow& window);

    //возвращает координату центра прямоугольника верхней крыши ворот в системе координат Box2D
    b2Vec2 getRoofPosition();
protected:
    float goalWidth;
    float goalHeight;
    float roofHeight;
    float roofWidth;
    float xPosition;
    float xRoof;
    float yGoal;
    int xGoal;
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

class LeftGoal : public Goal {
public:
    LeftGoal(b2World& world); 
    //Возвращает координату правого нижнего угла крыши ворот в системе Box2D
    b2Vec2 getRoofPosition();
};

class RightGoal : public Goal {
public:
    RightGoal(b2World& world);
    //Возвращает координату левого нижнего угла крыши ворот в системе Box2D
    b2Vec2 getRoofPosition();
};