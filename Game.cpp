#include "Game.h"
Game::Game()
    : world(b2Vec2(0.0f, 20.0f)),
    box(world),
    ball(world),
    player1(world, sf::Color::Red, b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 100 / SCALE)),
    player2(world, sf::Color::Blue, b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 100 / SCALE)),
    leftGoal(world, true),
    rightGoal(world, false),
    score()
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML + Box2D Circle");
    window.setFramerateLimit(60);
    player1.playerBody->SetFixedRotation(true);
    player2.playerBody->SetFixedRotation(true);

}

void Game::run() {
    while (window.isOpen()) {
        processingEvents();
        check_goal();
        update();
        draw();
    }
}

void Game::processingEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        float direction1 = 0.0f;
        float direction2 = 0.0f;
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction1 = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction1 = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction2 = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction2 = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !(player1.wasJumping)) {
            player1.jump();
            player1.wasJumping = true;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            }
            player1.kick(ball);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) {
            player2.kick(ball);
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player1.wasJumping = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !player2.wasJumping) {
            player2.jump();
            player2.wasJumping = true;
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player2.wasJumping = false;
        }
        player1.move(direction1);
        player2.move(direction2);
    }
}

void Game::update() {
    world.Step(1.0f / 60.0f, 8, 2);
    ball.update();
    player1.update();
    player2.update();
}

void Game::draw() {
    window.clear();
    window.draw(box.sfGround);
    window.draw(ball.sfBall);
    window.draw(player1.sfPlayer);
    window.draw(player2.sfPlayer);

    leftGoal.draw(window);
    rightGoal.draw(window);
    window.display();
}

void Game::check_goal() {
    if (ball.ballBody->GetPosition().x <= leftGoal.horizontalBody->GetPosition().x + (leftGoal.roofWidth / 2 / SCALE) &&
        ball.ballBody->GetPosition().y >= leftGoal.horizontalBody->GetPosition().y - (leftGoal.roofHeight / 2 / SCALE))
    {
        player2.score += 1;
        ball.ballBody->SetTransform(b2Vec2(WINDOW_WIDTH / 2 / SCALE, WINDOW_HEIGHT / 2 / SCALE), 0);
        std::cout << "Player 2 score: " << player2.score << std::endl;
        ball.ballBody->SetLinearVelocity(b2Vec2(0, 0));
    }
    else if (ball.ballBody->GetPosition().x >= rightGoal.horizontalBody->GetPosition().x - (rightGoal.roofWidth / 2 / SCALE) &&
        ball.ballBody->GetPosition().y >= leftGoal.horizontalBody->GetPosition().y - (leftGoal.roofHeight / 2 / SCALE))
    {
        player1.score += 1;
        ball.ballBody->SetTransform(b2Vec2(WINDOW_WIDTH / 2 / SCALE, WINDOW_HEIGHT / 2 / SCALE), 0);
        std::cout << "Player 1 score: " << player1.score << std::endl;
        ball.ballBody->SetLinearVelocity(b2Vec2(0, 0));
    }
}

