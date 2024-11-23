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
    score(world),
    menu(window.getSize().x, window.getSize().y)
{
    inGame = false;
    gameStart = true;
    ballSound.openFromFile("sounds/ballCollide.wav");
    contactListener = new GameContactListener(ballSound);
    ballStartPosition = b2Vec2(WINDOW_WIDTH / 2 / SCALE, (WINDOW_HEIGHT / 2 - 100) / SCALE);
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Head soccer");
    window.setFramerateLimit(60);
    backgroundTexture.loadFromFile("icons/backgrounds/background1.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    player1.playerBody->SetFixedRotation(true);
    player2.playerBody->SetFixedRotation(true);
    whistle.openFromFile("sounds/Whistle.wav");
    goalScore.openFromFile("sounds/goalscored3.wav");
    world.SetContactListener(contactListener);
    backgroundMusic.openFromFile("sounds/mainSound.wav");
    backgroundMusic.setVolume(15);

}

void Game::run() {
    while (window.isOpen()) {
        draw(); 
        if (inGame) {
            processingEventsInGame();
            check_goal();
            update();
            checkWin();

            if (gameStart) {
                start();
            }
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
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space) {
                player1.kick(ball);
            }
            if (event.key.code == sf::Keyboard::RAlt) {
                player2.kick(ball);
            }
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
        window.draw(box.getSFGround());
        window.draw(ball.getSFBall());
        window.draw(player1.sfPlayer);
        window.draw(player2.sfPlayer);
        window.draw(player1.bootSprite);
        window.draw(player2.bootSprite);
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
    if (ball.getPosition().x <= leftGoal.horizontalBody->GetPosition().x + (leftGoal.roofWidth / 2 / SCALE) &&
        ball.getPosition().y >= leftGoal.horizontalBody->GetPosition().y - (leftGoal.roofHeight / 2 / SCALE))
    {
        player2.score += 1;
        score.updateScore(2);
        ball.getBallBody()->SetTransform(ballStartPosition, 0);
        ball.getBallBody()->SetLinearVelocity(b2Vec2(0, 0));
        ball.getBallBody()->SetAngularVelocity(0);
        drawGoalText();
        player1.playerBody->SetTransform(b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE), 0);
        player2.playerBody->SetTransform(b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE), 0);
    }
    else if (ball.getPosition().x >= rightGoal.horizontalBody->GetPosition().x - (rightGoal.roofWidth / 2 / SCALE) &&
        ball.getPosition().y >= leftGoal.horizontalBody->GetPosition().y - (leftGoal.roofHeight / 2 / SCALE))
    {
        player1.score += 1;
        score.updateScore(1);
        ball.getBallBody()->SetTransform(ballStartPosition, 0);
        ball.getBallBody()->SetLinearVelocity(b2Vec2(0, 0));
        ball.getBallBody()->SetAngularVelocity(0);
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
            menu.click.play();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            menu.click.play();
            menu.moveDown();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            menu.click.play();
            if (menu.selectedItemIndex == 0) {
                inGame = true;
                menu.music.stop();
                gameStart = true;
                backgroundMusic.play();
            }
            else {
                window.close();
            }
        }
    }
}

void Game::checkWin() {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");
    text.setCharacterSize(50);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 50);
    sf::Music crowd;
    crowd.openFromFile("sounds/goalscored3.wav");
    if (score.player1 == BALLS_FOR_WIN || score.player2 == BALLS_FOR_WIN) {
        std::string winner;
        if (score.player1 == BALLS_FOR_WIN) {
            winner = "Winner: Player1";
        }
        else if (score.player2 == BALLS_FOR_WIN) {
            winner = "Winner: Player2";
        }
        text.setString(winner);

        inGame = false;
        score.player1 = 0;
        score.player2 = 0;
        score.timeRemaining = GAME_TIME;
        window.draw(text);
        window.display();
        crowd.play();
        std::this_thread::sleep_for(std::chrono::seconds(4));
        backgroundMusic.stop();
        menu.music.play();
    }
    else if (score.timeRemaining == 0) {
        inGame = false;

        if (score.player1 > score.player2) {
            text.setString("Winner: Player1");
        }
        else if (score.player2 > score.player1) {
            text.setString("Winner: Player2");
        }
        else {
            text.setString("Draw");
            text.setPosition(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 - 50);
            text.setCharacterSize(80);
        }
        window.draw(text);
        window.display();
        crowd.play();
        std::this_thread::sleep_for(std::chrono::seconds(4));
        backgroundMusic.stop();

        score.player1 = 0;
        score.player2 = 0;
        score.timeRemaining = GAME_TIME;
        menu.music.play();
        player1.playerBody->SetTransform(b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE), 0);
        player2.playerBody->SetTransform(b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE), 0);
        ball.getBallBody()->SetTransform(ballStartPosition, 0);
        ball.getBallBody()->SetLinearVelocity(b2Vec2(0, 0));
        ball.getBallBody()->SetAngularVelocity(0);
    }
}


void Game::drawGoalText() {
    if (player1.score != BALLS_FOR_WIN and player2.score != BALLS_FOR_WIN) {
        backgroundMusic.setVolume(5);
        goalScore.play();
        sf::Text text;
        sf::Font font;
        font.loadFromFile("fonts/arial.ttf");
        text.setFont(font);
        text.setString("GOAL!!!");
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);
        text.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 50);
        window.draw(text);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        whistle.play();
        backgroundMusic.setVolume(50);
    }

}

void Game::start() {
    gameStart = false;

    sf::Text text;
    sf::Font font;
    font.loadFromFile("fonts/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);

    for (int i = 3; i >= 1; --i) {
        text.setString(std::to_string(i));
        text.setPosition(WINDOW_WIDTH / 2 - 24, WINDOW_HEIGHT / 2 - 50);
        window.clear();
        window.draw(backgroundSprite);
        window.draw(box.getSFGround());
        window.draw(ball.getSFBall());
        window.draw(player1.sfPlayer);
        window.draw(player2.sfPlayer);
        window.draw(player2.bootSprite);
        window.draw(player1.bootSprite);
        score.draw(window);
        leftGoal.draw(window);
        rightGoal.draw(window);

        window.draw(text);
        window.display();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    whistle.play();
}









