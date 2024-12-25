#include "Player.h"
#include "Settings.h"
#include <iostream>

Player::Player(b2World& world, sf::Color color, b2Vec2 position) {
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(position.x, position.y);
    playerBody = world.CreateBody(&playerBodyDef);
    playerBody->SetFixedRotation(true);

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
    kickSound.openFromFile("sounds/Hob.wav");
    kickSound.setVolume(20);
    earlyTime = std::chrono::system_clock::now();
}
//Движение игрока
void Player::move() {
    float desiredVelocity = PLAYER_SPEED * direction;
    b2Vec2 currentVelocity = playerBody->GetLinearVelocity();
    float velocityChange = desiredVelocity - currentVelocity.x;
    float impulse = playerBody->GetMass() * velocityChange;
    playerBody->ApplyLinearImpulse(b2Vec2(impulse, 0.0f), playerBody->GetWorldCenter(), true);
}
//Обновление состояния игрока
void Player::update() {
    b2Vec2 PlayerPosition = this->playerBody->GetPosition();
    float PlayerAngle = this->playerBody->GetAngle();
    this->sfPlayer.setPosition(PlayerPosition.x * SCALE, PlayerPosition.y * SCALE);
    this->sfPlayer.setRotation(PlayerAngle * 180.0f / 3.14159f);

    if(this->number == 1){
        bootSprite.setPosition(sfPlayer.getPosition().x - 20, sfPlayer.getPosition().y + 45);
    }
    else if (this->number == 2) {
        bootSprite.setPosition(sfPlayer.getPosition().x + 20, sfPlayer.getPosition().y + 45);
    }

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
//Прыжок
void Player::jump() {
    if (this->sfPlayer.getPosition().y >= 649) {
        b2Vec2 jumpImpulse(0.0f, -3000.0f);
        playerBody->ApplyLinearImpulseToCenter(jumpImpulse, true);
    }
}

//Отрисовывает анимацию удара левого игрока
void Player1::animateKick() {
    float rotationOffset = -45.0f * sin(kickTimer * 3.14159f);
    bootSprite.setRotation(sfPlayer.getRotation() + rotationOffset);
}
//Отрисовывет анимацию удара правого игрока
void Player2::animateKick() {
    float rotationOffset = 45.0f * sin(kickTimer * 3.14159f);
    bootSprite.setRotation(sfPlayer.getRotation() + rotationOffset);
}
//Удар левого игрока
void Player1::kick(Ball& ball) {
    kickSound.play();
    float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
    float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
    double dS = sqrt(dx * dx + dy * dy);
    animateKick();
    isKicking = true;
    if (dS < 100) {
        ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(180, -100), true);
    }
}
//Удар правого ирока
void Player2::kick(Ball& ball) {
    kickSound.play();
    float dx = ball.sfBall.getPosition().x - this->sfPlayer.getPosition().x;
    float dy = ball.sfBall.getPosition().y - this->sfPlayer.getPosition().y;
    double dS = sqrt(dx * dx + dy * dy);
    animateKick();
    isKicking = true;
    if (dS < 100) {
        ball.ballBody->ApplyLinearImpulseToCenter(b2Vec2(-180, -100), true);
    }
}

sf::CircleShape Player::getSFShape() {
    return sfPlayer;
}

void Player::setMoveDirection(int direction) {
    this->direction = direction;

}

sf::Sprite Player::getBootSprite() {
    return bootSprite;
}
//Отрисовка игрока
void Player::render(sf::RenderWindow& window) {
    window.draw(sfPlayer);
    window.draw(bootSprite);
}
//Возвращает правого игрока в начальное положение
void Player2::returnInStartPosition() {
    playerBody->SetTransform(b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE), 0);
}

//Возвращает левого игрока в начальное положение
void Player1::returnInStartPosition() {
    playerBody->SetTransform(b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE), 0);
}