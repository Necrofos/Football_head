#include "MainMenu.h"


MainMenu::MainMenu(float height, float width) {
	font.loadFromFile("fonts//arial.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(600, 300));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Exit");
	menu[1].setCharacterSize(50);
	menu[1].setPosition(sf::Vector2f(600, 400));

	selectedItemIndex = 0;
	backgroundTexture.loadFromFile("icons/menu/mainMenu3.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	click.openFromFile("sounds/click.wav");
	music.openFromFile("sounds/MainMenu.wav");
	music.play();

	font2.loadFromFile("fonts/font2.ttf");
	gameNameText.setFont(font2);
	gameNameText.setString("Head Ball");
	gameNameText.setCharacterSize(140); // ������ ������
	gameNameText.setFillColor(sf::Color::Red); // ���� ������
	gameNameText.setStyle(sf::Text::Bold);

	// �������� ������ ������
	sf::FloatRect textBounds = gameNameText.getLocalBounds();

	// ����������� ����� �� ������ � ������� ����� ����
	gameNameText.setOrigin(textBounds.width / 2, textBounds.height / 2);
	gameNameText.setPosition(1280 / 2, textBounds.height / 2 + 90 );


}
//��������� ����
void MainMenu::draw(sf::RenderWindow& window) {
	window.draw(backgroundSprite);
	window.draw(gameNameText);
	for (int i = 0; i < 2; i++) {
		window.draw(menu[i]);
	}

}

//����� ������� ��������� ������ � ����
void MainMenu::moveUp() {
	if (selectedItemIndex == 1) {
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex -= 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		click.play();
	}
}
//����� ������� ��������� ���� � ����
void MainMenu::moveDown() {
	if (selectedItemIndex == 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex += 1;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
		click.play();
	}
}
//�������� ������ � ����
void MainMenu::playMusic() {
	music.play();
}
//��������� ������ � ����
void MainMenu::stopMusic() {
	music.stop();
}
//���� �����
void MainMenu::playClick() {
	click.play();
}

//��������, ������� �� ������ ������
bool MainMenu::isPlaySelected() {
	return (selectedItemIndex == 0);
}