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
#include "SFML/Audio.hpp"
#include "MyContactListener.h"

class Game {
public:
    Game();
    void run();
private:
    void processingEventsInGame();
    void processingEventsInMenu();
    void update();
    void render();
    void check_goal();
    void checkWin();
    void drawGoalText();
    void start();

    sf::RenderWindow window;
    b2World world;
    Player1 player1;
    Player2 player2;
    Ball ball;
    Box box;
    LeftGoal leftGoal;
    RightGoal rightGoal;
    Score score;
    MainMenu menu;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool inGame;
    bool gameStart;
    b2Vec2 ballStartPosition;
    sf::Music whistle;
    sf::Music goalScore;
    sf::Music ballSound;
    sf::Music backgroundMusic;
    GameContactListener* contactListener;
};

