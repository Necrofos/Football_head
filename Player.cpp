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
	sfPlayer.setFillColor(color);
	sfPlayer.setOrigin(PLAYER_RADIUS, PLAYER_RADIUS);
	score = 0;
}


void Player::move(int direction) {
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
	}
}

void Player1::kick(Ball& ball) {
	float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
	float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
	double dS = sqrt(dx * dx + dy * dy);
	if (dS < 100) {
		ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(90, -50), true);
	}
}

void Player2::kick(Ball& ball) {
	float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
	float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
	double dS = sqrt(dx * dx + dy * dy);
	if (dS < 100) {
		ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(-90, -50), true);
	}
}