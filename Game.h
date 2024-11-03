#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "Ball.h"
#include "Player.h"
#include "Box.h"
#include "goals.h"
#include "Score.h"
#include <iostream>
#include "MainMenu.h"

class Game {
public:
    Game();
    void run();
private:
    void processingEventsInGame();
    void processingEventsInMenu();
    void update();
    void draw();
    void check_goal();
    void checkWin();
    void drawGoalText();

    sf::RenderWindow window;
    b2World world;
    Player1 player1;
    Player2 player2;
    Ball ball;
    Box box;
    Goal leftGoal;
    Goal rightGoal;
    Score score;
    MainMenu menu;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool inGame;

};

