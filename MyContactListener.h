#pragma once
#include "box2d/box2d.h"
#include "SFML/Audio.hpp"

class GameContactListener : public b2ContactListener {
public:
    GameContactListener(sf::Music& ballSound) : ballContactSound(ballSound) {}

    void BeginContact(b2Contact* contact) override {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        if (isBallContact(fixtureA, fixtureB)) {
            ballContactSound.play();
        }
    }

private:
    sf::Music& ballContactSound;

    bool isBallContact(b2Fixture* fixtureA, b2Fixture* fixtureB) {

        return (fixtureA->GetBody()->GetUserData() == "Ball" ||
            fixtureB->GetBody()->GetUserData() == "Ball");
    }
};
