#include "Game.h"
#include <thread>
#include <chrono>
Game::Game()
    : world(b2Vec2(0.0f, 20.0f)),
    box(world),
    ball(world),
    player1(world, sf::Color::Red, b2Vec2((2 * PLAYER_RADIUS + 20) / SCALE, 400 / SCALE)),
    player2(world, sf::Color::Blue, b2Vec2((WINDOW_WIDTH - 2 * PLAYER_RADIUS - 20) / SCALE, 400 / SCALE)),
    leftGoal(world),
    rightGoal(world),
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
    whistle.openFromFile("sounds/Whistle.wav");
    goalScore.openFromFile("sounds/goalscored3.wav");
    world.SetContactListener(contactListener);
    backgroundMusic.openFromFile("sounds/mainSound.wav");
    backgroundMusic.setVolume(15);

}

void Game::run() {
    while (window.isOpen()) {
        render(); 
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
            player1.setMoveDirection(-1);
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) and !sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player1.setMoveDirection(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player1.setMoveDirection(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player2.setMoveDirection(-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player2.setMoveDirection(1);
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            player2.setMoveDirection(0);
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

void Game::render() {
    if (inGame) {
        window.clear();
        window.draw(backgroundSprite);
        ball.render(window);
        player1.render(window);
        player2.render(window);
        score.render(window);
        leftGoal.render(window);
        rightGoal.render(window);
        window.display();
    }
    else {
        menu.draw(window);
        window.display();
    }
}

void Game::check_goal() {
    if (ball.getPosition().x <= leftGoal.getRoofPosition().x &&
        ball.getPosition().y >= leftGoal.getRoofPosition().y)
    {
        score.updateScore(2);
        ball.returnInInitialState();
        drawGoalText();
        player1.returnInStartPosition();
        player2.returnInStartPosition();
    }
    else if (ball.getPosition().x >= rightGoal.getRoofPosition().x &&
        ball.getPosition().y >= rightGoal.getRoofPosition().y )
    {
        score.updateScore(1);
        ball.returnInInitialState();
        drawGoalText();
        player1.returnInStartPosition();
        player2.returnInStartPosition();
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
            menu.playClick();
            if (menu.isPlaySelected()) {
                inGame = true;
                menu.stopMusic();
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
    if (score.getScorePlayer1() == BALLS_FOR_WIN || score.getScorePlayer2() == BALLS_FOR_WIN) {
        std::string winner;
        if (score.getScorePlayer1() == BALLS_FOR_WIN) {
            winner = "Winner: Player1";
        }
        else if (score.getScorePlayer2() == BALLS_FOR_WIN) {
            winner = "Winner: Player2";
        }
        text.setString(winner);

        inGame = false;
        score.returnInInitialState();
        window.draw(text);
        window.display();
        crowd.play();
        std::this_thread::sleep_for(std::chrono::seconds(4));
        backgroundMusic.stop();
        menu.playMusic();
    }
    else if (score.getTimeRemaining() == 0) {
        inGame = false;

        if (score.getScorePlayer1() > score.getScorePlayer2()) {
            text.setString("Winner: Player1");
        }
        else if (score.getScorePlayer2() > score.getScorePlayer2()) {
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

        score.returnInInitialState();
        menu.playMusic();
        player1.returnInStartPosition();
        player2.returnInStartPosition();
        ball.returnInInitialState();
    }
}


void Game::drawGoalText() {
    if (score.getScorePlayer1() != BALLS_FOR_WIN and score.getScorePlayer2() != BALLS_FOR_WIN) {
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
        ball.render(window);
        score.render(window);
        leftGoal.render(window);
        rightGoal.render(window);
        player1.render(window);
        player2.render(window);
        window.draw(text);
        window.display();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    whistle.play();
}









