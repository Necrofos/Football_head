#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "Settings.h"
#include "Ball.h"
#include "SFML/Audio.hpp"
#include <chrono>

class Player
{
public:
    Player(b2World& world, sf::Color color, b2Vec2 position);
    void move();
    void update();
    void jump();
    virtual void kick(Ball& ball) = 0;
    virtual void animateKick() = 0;
    void setMoveDirection(int direction);
    bool wasJumping;
    bool isKicking;
    sf::Sprite getBootSprite();
    sf::CircleShape getSFShape();

    void render(sf::RenderWindow& window);
    virtual void returnInStartPosition() = 0;
protected:
    b2Body* playerBody;
    b2BodyDef playerBodyDef;
    b2CircleShape playerShape;
    b2FixtureDef playerFixtureDef;
    sf::CircleShape sfPlayer;
    sf::Music kickSound;
    b2Body* bootBody;
    b2BodyDef bootBodyDef;
    b2FixtureDef bootFixtureDef;

    sf::Texture playerTexture;
    sf::Sprite bootSprite;
    sf::Texture bootTexture;
    std::chrono::system_clock::time_point earlyTime;



    

    float kickTimer = 0.0f;
    int score;

    int direction;
    float currentRotation;
    int number;


};

class Player1 : public Player {
public:
    Player1(b2World& world, sf::Color color, b2Vec2 position) : Player(world, color, position) {
        bootTexture.loadFromFile("icons/boots/shoeL.png");
        bootSprite.setTexture(bootTexture);
        playerTexture.loadFromFile("icons/heads/P1.png");
        sfPlayer.setTexture(&playerTexture);
        sf::Vector2u size = bootTexture.getSize();
        bootSprite.setOrigin(0, size.y);
        number = 1;
    }
    void kick(Ball& ball) override;
    void animateKick() override; 
    void returnInStartPosition() override;
};

class Player2 : public Player {
public:
    Player2(b2World& world, sf::Color color, b2Vec2 position) : Player(world, color, position) {
        bootTexture.loadFromFile("icons/boots/shoeR.png");
        bootSprite.setTexture(bootTexture);
        playerTexture.loadFromFile("icons/heads/P2.png");
        sfPlayer.setTexture(&playerTexture);
        sf::Vector2u size = bootTexture.getSize();
        bootSprite.setOrigin(size.x, size.y);
        number = 2;
    }
    void kick(Ball& ball) override;
    void animateKick() override; 
    void returnInStartPosition() override;
};
