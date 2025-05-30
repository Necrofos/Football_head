#include "Ball.h"

Ball::Ball(b2World& world) {
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(WINDOW_WIDTH / 2 / SCALE, (WINDOW_HEIGHT / 2 - 100) / SCALE);
    ballBodyDef.bullet = true;
    ballBody = world.CreateBody(&ballBodyDef);

    ballShape.m_radius = RADIUS / SCALE;
    ballStartPosition = b2Vec2(WINDOW_WIDTH / 2 / SCALE, (WINDOW_HEIGHT / 2 - 100) / SCALE);


    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 5.0f;
    ballFixtureDef.friction = 0.3f;
    ballFixtureDef.restitution = 0.6f;

    ballBody->CreateFixture(&ballFixtureDef);


    sfBall = sf::CircleShape(RADIUS);
    ballTexture.loadFromFile("icons/ball.png");
    sfBall.setTexture(&ballTexture);
    sfBall.setFillColor(sf::Color::White);
    sfBall.setOrigin(RADIUS, RADIUS);
    ballBody->SetUserData((void*)"Ball");
}


//���������� ������� ����
void Ball::update() {
    b2Vec2 BallPosition = this->ballBody->GetPosition();
    float BallAngle = this->ballBody->GetAngle();
    this->sfBall.setPosition(BallPosition.x * SCALE, BallPosition.y * SCALE);
    this->sfBall.setRotation(BallAngle * 180.0f / 3.14159f);
}


//��������� ������� ����
b2Vec2 Ball::getPosition() {
    return ballBody->GetPosition();
}

//������� ���� � ��������� ���������
void Ball::returnInInitialState() {
    ballBody->SetTransform(ballStartPosition, 0);
    ballBody->SetLinearVelocity(b2Vec2(0, 0));
    ballBody->SetAngularVelocity(0);
}

//��������� ����
void Ball::render(sf::RenderWindow& window) {
    window.draw(sfBall);
}