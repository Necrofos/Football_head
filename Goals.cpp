#include "goals.h"

Goal::Goal(b2World& world) {
	goalWidth = 10.0f;
	goalHeight = 200.0f;
	roofHeight = 10.0f;
	roofWidth = 110.0f;
	yGoal = WINDOW_HEIGHT - goalHeight - roofHeight - 20;
}
//Отрисовка ворот
void Goal::render(sf::RenderWindow& window) {
	window.draw(SFverticalShape);
	window.draw(SFhorizontalShape);
	window.draw(sfGoalShape);
}
//Возвращает
b2Vec2 Goal::getRoofPosition() {
	return b2Vec2(horizontalBody->GetPosition().x + (roofWidth / 2 / SCALE), horizontalBody->GetPosition().y - (roofHeight / 2 / SCALE));
}

b2Vec2 LeftGoal::getRoofPosition() {
	return b2Vec2(horizontalBody->GetPosition().x + (roofWidth / 2 / SCALE), horizontalBody->GetPosition().y - (roofHeight / 2 / SCALE));
}

b2Vec2 RightGoal::getRoofPosition() {
	return b2Vec2(horizontalBody->GetPosition().x - (roofWidth / 2 / SCALE), horizontalBody->GetPosition().y - (roofHeight / 2 / SCALE));
}

RightGoal::RightGoal(b2World& world) :Goal(world){
    yGoal = WINDOW_HEIGHT - goalHeight - roofHeight - 20;
    xPosition = WINDOW_WIDTH - (goalWidth / 2);
    xRoof = WINDOW_WIDTH - (roofWidth / 2);
    xGoal = WINDOW_WIDTH - roofWidth;
    goalTexture.loadFromFile("icons/goals/r.png");
    sfGoalShape.setPosition(xGoal, WINDOW_HEIGHT - goalHeight - roofHeight - 20);
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

LeftGoal::LeftGoal(b2World& world) : Goal(world) {
    yGoal = WINDOW_HEIGHT - goalHeight - roofHeight - 20;
    xPosition = goalWidth / 2;
    xRoof = roofWidth / 2;
    xGoal = 0;
    goalTexture.loadFromFile("icons/goals/l.png");
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