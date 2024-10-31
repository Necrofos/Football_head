#include "goals.h"

Goal::Goal(b2World& world, bool isLeft) {
	goalWidth = 10.0f;
	goalHeight = 200.0f;
	roofHeight = 10.0f;
	roofWidth = 50.0f;
	if (isLeft) {
		xPosition = goalWidth / 2;
		xRoof = roofWidth / 2;
	}
	else {
		xPosition = WINDOW_WIDTH - (goalWidth / 2);
		xRoof = WINDOW_WIDTH - (roofWidth / 2);
	}
	float yPosition = WINDOW_HEIGHT - 20 - (goalHeight / 2);
	float yRoof = yPosition - (goalHeight / 2 + roofHeight / 2);
	verticalBodyDef.position.Set(xPosition / SCALE, yPosition / SCALE);
	verticalBodyDef.type = b2_staticBody;
	verticalBody = world.CreateBody(&verticalBodyDef);

	verticalPolygon.SetAsBox((goalWidth / 2) / SCALE, (goalHeight / 2) / SCALE);
	verticalBody->CreateFixture(&verticalPolygon, 0.0f);


	horizontalBodyDef.position.Set(xRoof / SCALE, yRoof / SCALE);
	horizontalBodyDef.type = b2_staticBody;
	horizontalBody = world.CreateBody(&horizontalBodyDef);

	horizontalPolygon.SetAsBox((roofWidth / 2) / SCALE, (roofHeight / 2) / SCALE);
	horizontalBody->CreateFixture(&horizontalPolygon, 0.0f);

	SFverticalShape.setSize(sf::Vector2f(goalWidth, goalHeight));
	SFverticalShape.setFillColor(sf::Color::White);
	SFverticalShape.setOrigin(goalWidth / 2, goalHeight / 2);
	SFverticalShape.setPosition(xPosition, yPosition);


	SFhorizontalShape.setSize(sf::Vector2f(roofWidth, roofHeight));
	SFhorizontalShape.setFillColor(sf::Color::White);
	SFhorizontalShape.setOrigin(roofWidth / 2, roofHeight / 2);
	SFhorizontalShape.setPosition(xRoof, yRoof);
}

void Goal::draw(sf::RenderWindow& window) {
	window.draw(SFverticalShape);
	window.draw(SFhorizontalShape);
}