#include "Player.h"
#include "Settings.h"
#include <iostream>

Player::Player(b2World& world, sf::Color color, b2Vec2 position) {
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(position.x, position.y);
	playerBody = world.CreateBody(&playerBodyDef);

	playerShape.m_radius = PLAYER_RADIUS / SCALE;

	playerFixtureDef.shape = &playerShape;

	playerFixtureDef.density = 20.0f;
	playerFixtureDef.friction = 0.3f;
	playerFixtureDef.restitution = 0.0f;

	playerBody->CreateFixture(&playerFixtureDef);

	sfPlayer = sf::CircleShape(PLAYER_RADIUS);
	sfPlayer.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
	score = 0;
	bootSprite.setScale(sf::Vector2f(0.2f, 0.2f));
	
}


void Player::move() {
	float desiredVelocity = PLAYER_SPEED * direction;
	b2Vec2 currentVelocity = playerBody->GetLinearVelocity();

	float velocityChange = desiredVelocity - currentVelocity.x;
	float impulse = playerBody->GetMass() * velocityChange;

	playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0.0f), playerBody->GetWorldCenter(), true);
}





void Player::update() {
    b2Vec2 PlayerPosition = this->playerBody->GetPosition();
    float PlayerAngle = this->playerBody->GetAngle();
    this->sfPlayer.setPosition(PlayerPosition.x * SCALE, PlayerPosition.y * SCALE);
    this->sfPlayer.setRotation(PlayerAngle * 180.0f / 3.14159f);

    bootSprite.setPosition(sfPlayer.getPosition().x - 15, sfPlayer.getPosition().y + 20);
    bootSprite.setRotation(sfPlayer.getRotation());

    if (isKicking) {
        kickTimer += 0.05f;
        if (kickTimer < 0.5f) {
            animateKick(); 
        }
        else if (kickTimer < 1.0f) {
            bootSprite.setRotation(sfPlayer.getRotation()); 
        }
        else {
            isKicking = false;
            kickTimer = 0.0f; 
        }
    }
}

void Player::jump() {
    if (this->sfPlayer.getPosition().y >= 649) {
        b2Vec2 jumpImpulse(0.0f, -3000.0f);
        playerBody->ApplyLinearImpulseToCenter(jumpImpulse, true);
    }
}

void Player::kick(Ball& ball) {
    float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
    float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
    double dS = sqrt(dx * dx + dy * dy);
    if (dS < 100) {
        ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(90, -50), true);

        isKicking = true;
        animateKick();
    }
}

void Player::animateKick() {
    bootSprite.setRotation(sfPlayer.getRotation() - 45.0f);
}

void Player1::kick(Ball& ball) {
    float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
    float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
    double dS = sqrt(dx * dx + dy * dy);
    animateKick();
    isKicking = true;
    if (dS < 100) {
        ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(90, -50), true);
    }
}

void Player2::kick(Ball& ball) {
    float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
    float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
    double dS = sqrt(dx * dx + dy * dy);
    animateKick();
    isKicking = true;
    if (dS < 100) {
        ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(-90, -50), true);;
    }
}