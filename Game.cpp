#include "Game.h"
#include <thread>
#include <chrono>
Game::Game()
    : world(b2Vec2(0.0f, 20.0f)),
    box(world),
    ball(world),
    player1(world, sf::Color::Red, b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE)),
    player2(world, sf::Color::Blue, b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE)),
    leftGoal(world, true),
    rightGoal(world, false),
    score(),
    menu(window.getSize().x, window.getSize().y)
{
    inGame = false;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML + Box2D Circle");
    window.setFramerateLimit(60);
    backgroundTexture.loadFromFile("icons/backgrounds/background1.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    player1.playerBody->SetFixedRotation(true);
    player2.playerBody->SetFixedRotation(true);

}

void Game::run() {
    while (window.isOpen()) {
        draw();
        if (inGame) {
            processingEventsInGame();
            check_goal();
            update();
            checkWin();
        }
        else {
            processingEventsInMenu();
        }

    }
}

void Game::processingEventsInGame() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player1.direction = -1;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) and !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player1.direction = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player1.direction = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player2.direction = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player2.direction = 1;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player2.direction = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(player1.wasJumping)) {
            player1.jump();
            player1.wasJumping = true;


        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player1.kick(ball);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) {
            player2.kick(ball);
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player1.wasJumping = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !player2.wasJumping) {
            player2.jump();
            player2.wasJumping = true;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player2.wasJumping = false;
        }
        player1.move();
        player2.move();
    }
}

void Game::update() {
    if (inGame) {
        world.Step(1.0f / 60.0f, 8, 2);
        ball.update();
        player1.update();
        player2.update();
        score.updateText();
    }

}

void Game::draw() {
    if (inGame) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(box.sfGround);
        window.draw(ball.sfBall);
        window.draw(player1.sfPlayer);
        window.draw(player2.sfPlayer);
        score.draw(window);
        leftGoal.draw(window);
        rightGoal.draw(window);
        window.display();
    }
    else {
        menu.draw(window);
        window.display();
    }
}

void Game::check_goal() {
    if (ball.ballBody->GetPosition().x <= leftGoal.horizontalBody->GetPosition().x + (leftGoal.roofWidth / 2 / SCALE) &&
        ball.ballBody->GetPosition().y >= leftGoal.horizontalBody->GetPosition().y - (leftGoal.roofHeight / 2 / SCALE))
    {
        player2.score += 1;
        score.updateScore(2);
        ball.ballBody->SetTransform(b2Vec2(WINDOW_WIDTH / 2 / SCALE, WINDOW_HEIGHT / 2 / SCALE), 0);
        std::cout << "Player 2 score: " << player2.score << std::endl;
        ball.ballBody->SetLinearVelocity(b2Vec2(0, 0));
        ball.ballBody->SetAngularVelocity(0);
        drawGoalText();
        player1.playerBody->SetTransform(b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE), 0);
        player2.playerBody->SetTransform(b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE), 0);
    }
    else if (ball.ballBody->GetPosition().x >= rightGoal.horizontalBody->GetPosition().x - (rightGoal.roofWidth / 2 / SCALE) &&
        ball.ballBody->GetPosition().y >= leftGoal.horizontalBody->GetPosition().y - (leftGoal.roofHeight / 2 / SCALE))
    {
        player1.score += 1;
        score.updateScore(1);
        ball.ballBody->SetTransform(b2Vec2(WINDOW_WIDTH / 2 / SCALE, WINDOW_HEIGHT / 2 / SCALE), 0);
        std::cout << "Player 1 score: " << player1.score << std::endl;
        ball.ballBody->SetLinearVelocity(b2Vec2(0, 0));
        ball.ballBody->SetAngularVelocity(0);
        drawGoalText();
        player1.playerBody->SetTransform(b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE), 0);
        player2.playerBody->SetTransform(b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE), 0);
    }
}

void Game::processingEventsInMenu() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            menu.moveUp();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            menu.moveDown();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (menu.selectedItemIndex == 0) {
                inGame = true;
            }
            else {
                window.close();
            }
        }
    }
}

void Game::checkWin() {
    if (score.player1 == 5 || score.player2 == 5) {
        inGame = false;
        score.player1 = 0;
        score.player2 = 0;
    }
}

void Game::drawGoalText() {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");
    text.setFont(font);
    text.setString("GOAL!!!");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Red);
    text.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 50);

    window.draw(text);
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(2));

}






