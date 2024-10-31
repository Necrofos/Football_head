#include "Score.h"
#include <iostream>


Score::Score() {
    player1 = 0;
    player2 = 0;

    fontPath = "/arial.ttf";

    position = sf::Vector2f(600, 400);
    font.loadFromFile("arial.ttf");


    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);
    updateText();
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
    text.setString(std::to_string(player1) + "-" + std::to_string(player2));
}

void Score::draw(sf::RenderWindow& window) {
    window.draw(text);
}
