#include "Score.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Settings.h"

Score::Score(b2World& world) {
    player1 = 0;
    player2 = 0;

    position = sf::Vector2f(600, 30);
    font.loadFromFile("fonts/arial.ttf");

    score1.setFont(font);
    score1.setCharacterSize(90);
    score1.setFillColor(sf::Color::White);
    score1.setPosition(sf::Vector2f(450, 60));

    score2.setFont(font);
    score2.setCharacterSize(90);
    score2.setFillColor(sf::Color::White);
    score2.setPosition(sf::Vector2f(740, 60));

    player1Label.setFont(font);
    player1Label.setCharacterSize(30);
    player1Label.setFillColor(sf::Color::White);
    player1Label.setString("Player1");
    player1Label.setPosition(sf::Vector2f(450, 0));

    player2Label.setFont(font);
    player2Label.setCharacterSize(30);
    player2Label.setFillColor(sf::Color::White);
    player2Label.setString("Player2");
    player2Label.setPosition(sf::Vector2f(690, 0));

    timerText.setFont(font);
    timerText.setCharacterSize(45);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(sf::Vector2f(562, 100));

    texture.loadFromFile("icons/scoreboard/board.png");
    boardShape.setSize(sf::Vector2f(459, 192));
    boardShape.setTexture(&texture);
    boardShape.setPosition(640 - 250, 0);

    timeRemaining = GAME_TIME;
}

void Score::updateScore(int playerNumber) {
    if (playerNumber == 1) {
        player1++;
    }
    else {
        player2++;
    }
}

void Score::updateText() {
    score1.setString(std::to_string(player1));
    score2.setString(std::to_string(player2));

    if (gameClock.getElapsedTime().asSeconds() >= 1.0f) {
        timeRemaining--;
        gameClock.restart();
    }
    if (timeRemaining < 0) {
        timeRemaining = 0;
    }

    int minutes = timeRemaining / 60;
    int seconds = timeRemaining % 60;
    timerText.setString((minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds));
}

void Score::draw(sf::RenderWindow& window) {
    window.draw(boardShape);
    window.draw(score1);
    window.draw(score2);
    window.draw(player1Label);
    window.draw(player2Label);
    window.draw(timerText);
}
