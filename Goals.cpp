#include "goals.h"

Goal::Goal(b2World& world, bool isLeft) {
	goalWidth = 10.0f;
	goalHeight = 200.0f;
	roofHeight = 10.0f;
	roofWidth = 110.0f;
	int xGoal; 
	int yGoal = WINDOW_HEIGHT - goalHeight - roofHeight - 20;
	if (isLeft) {
		xPosition = goalWidth / 2;
		xRoof = roofWidth / 2;
		xGoal = 0;
		goalTexture.loadFromFile("icons/goals/l.png");
	}
	else {
		xPosition = WINDOW_WIDTH - (goalWidth / 2);
		xRoof = WINDOW_WIDTH - (roofWidth / 2);
		xGoal = WINDOW_WIDTH - roofWidth;
		goalTexture.loadFromFile("icons/goals/r.png");
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


	sfGoalShape.setSize(sf::Vector2f(roofWidth, goalHeight + roofHeight));
	sfGoalShape.setPosition(xGoal, yGoal);
	sfGoalShape.setTexture(&goalTexture);
}

void Goal::draw(sf::RenderWindow& window) {
	window.draw(SFverticalShape);
	window.draw(SFhorizontalShape);
	window.draw(sfGoalShape);
}

b2Vec2 Goal::getRoofPosition() {
	return b2Vec2(horizontalBody->GetPosition().x - (roofWidth / 2 / SCALE), horizontalBody->GetPosition().y - (roofHeight / 2 / SCALE));
}