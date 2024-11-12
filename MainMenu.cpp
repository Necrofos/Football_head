#include "MainMenu.h"


MainMenu::MainMenu(float height, float width) {
	font.loadFromFile("fonts//arial.ttf");
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(600, 300));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setCharacterSize(50);
	menu[1].setPosition(sf::Vector2f(600, 400));

	selectedItemIndex = 0;
	backgroundTexture.loadFromFile("icons/menu/main2.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	click.openFromFile("sounds/click.wav");
	music.openFromFile("sounds/MainMenu.ogg");
	music.play();
}

void MainMenu::draw(sf::RenderWindow& window) {
	window.draw(backgroundSprite);
	for (int i = 0; i < 2; i++) {
		window.draw(menu[i]);
	}

}

void MainMenu::moveUp() {
	if (selectedItemIndex == 1) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex -= 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenu::moveDown() {
	if (selectedItemIndex == 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex += 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}



