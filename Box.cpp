#include "Box.h"
#include "Settings.h"

Box::Box(b2World& world) {
    //Земля
    groundBodyDef.position.Set(WINDOW_WIDTH / 2.0f / SCALE, (WINDOW_HEIGHT - 10.0f) / SCALE);
    groundBody = world.CreateBody(&groundBodyDef);
    groundBox.SetAsBox(WINDOW_WIDTH / 2.0f / SCALE, 10.0f / SCALE);
    groundBody->CreateFixture(&groundBox, 0.0f);

    //Потолок
    ceilingBodyDef.position.Set(WINDOW_WIDTH / 2.0f / SCALE, 0.0f / SCALE);
    b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
    ceilingBox.SetAsBox(WINDOW_WIDTH / 2.0f / SCALE, 10.0f / SCALE);
    ceilingBody->CreateFixture(&ceilingBox, 0.0f);

    //Левая стена
    leftwallBodyDef.position.Set(0.0f / SCALE, WINDOW_HEIGHT / 2.0f / SCALE);
    leftwallBody = world.CreateBody(&leftwallBodyDef);
    leftwallBox.SetAsBox(1.0f / SCALE, WINDOW_HEIGHT / 2.0f / SCALE);
    leftwallFixtureDef.shape = &leftwallBox;
    leftwallFixtureDef.friction = 0.0f;
    leftwallBody->CreateFixture(&leftwallFixtureDef);

    //Правая стена
    rightwallBodyDef.position.Set(WINDOW_WIDTH / SCALE, WINDOW_HEIGHT / 2.0f / SCALE);
    rightwallBody = world.CreateBody(&rightwallBodyDef);
    rightwallBox.SetAsBox(1.0f / SCALE, WINDOW_HEIGHT / 2.0f / SCALE);
    rightwallFixtureDef.shape = &rightwallBox;
    rightwallFixtureDef.friction = 0.0f;
    rightwallBody->CreateFixture(&rightwallFixtureDef);
}