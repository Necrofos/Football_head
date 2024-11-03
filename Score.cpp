#include "Score.h"
#include <iostream>


Score::Score() {
    player1 = 0;
    player2 = 0;


    position = sf::Vector2f(600, 30);
    font.loadFromFile("fonts//arial.ttf");

    score1.setFont(font);
    score1.setCharacterSize(90);
    score1.setFillColor(sf::Color::White);
    score1.setPosition(sf::Vector2f(450, 60));

    score2.setFont(font);
    score2.setCharacterSize(90);
    score2.setFillColor(sf::Color::White);
    score2.setPosition(sf::Vector2f(740, 60));







    texture.loadFromFile("icons/scoreboard/board.png");
    
    boardShape.setSize(sf::Vector2f(459, 192));
    boardShape.setTexture(&texture);
    boardShape.setPosition(640 - 250, 0);

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
}

void Score::draw(sf::RenderWindow& window) {
    window.draw(boardShape);
    window.draw(score1);
    window.draw(score2);
}
