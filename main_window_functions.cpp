/*
Wazne parametry: 
 Okno 1280x780
	sf::Vector2u windowSize = window.getSize(); //Pob?r rozmiaru okna
 Czcionki:
	arial.ttf <Testing>
	Inria_Serif/InriaSerif-LightItalic.ttf <Text - glam>
	Instrument_Sans/static/InstrumentSans-SemiBold.ttf <Text - read>
	League_Script/LeagueScript-Regular.ttf <LOGO>

*/


#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Header.h"
using namespace std;


int draw_main_screen(sf::RenderWindow& window){

	int Click_Value = 0;

	// Tworzenie prostok?ta
	sf::RectangleShape rectangle_main(sf::Vector2f(1280.0f, 780.0f)); // Rozmiar prostokata na cale okno
	rectangle_main.setFillColor(sf::Color(0xF7F7F7FF));
	window.draw(rectangle_main);
	sf::RectangleShape rectangle_green(sf::Vector2f(120.0f, 780.0f));
	rectangle_green.setFillColor(sf::Color(0xC4F7B7FF)); // Kolor prostokata (Cornflower Blue)
	window.draw(rectangle_green);
	sf::RectangleShape rectangle_white(sf::Vector2f(1160.0f, 70.0f)); 
	rectangle_white.setFillColor(sf::Color(0xFFFFFFFF));
	rectangle_white.setPosition(120, 0);
	window.draw(rectangle_white);

	return Click_Value;
}

void draw_logo(sf::RenderWindow& window) {
	// Ustawienia tekstu
	sf::Font logo_font;
	if (!logo_font.loadFromFile("Resources/Fonts/League_Script/LeagueScript-Regular.ttf")) {
		cout << "Failed to load font";
	}
	sf::Text logo;
	logo.setFont(logo_font);
	logo.setString("PLANTLY");
	logo.setCharacterSize(50);
	logo.setFillColor(sf::Color::Black);
	logo.setPosition(640, 0); // Pozycja tekstu
	window.draw(logo);
	//window.display();
}

void draw_menu(sf::RenderWindow& window) {
	sf::RectangleShape rectangle_white(sf::Vector2f(250.0f, 780.0f));
	rectangle_white.setFillColor(sf::Color(0xFFFFFFFF));
	rectangle_white.setPosition(120, 70);

	sf::RectangleShape rectangle_shadow(sf::Vector2f(250.0f, 780.0f));
	rectangle_shadow.setFillColor(sf::Color(0, 0, 0, 50));
	rectangle_shadow.setPosition(125, 75);

	// Ustawienia tekstu
	sf::Font text_font;
	if (!text_font.loadFromFile("Resources/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf")) {
		cout << "Failed to load font";
	}

	sf::Texture PFP;
	if (!PFP.loadFromFile("Resources/images/Home.png")) {
		cout << "Failed to load profile picture!" << endl;
		return;
	}

	sf::Text name;
	name.setFont(text_font);
	name.setString("Name \nSurname");
	name.setCharacterSize(20);
	name.setFillColor(sf::Color::Black);
	name.setPosition(140, 100); // Pozycja tekstu

	sf::Text Preferences;
	Preferences.setFont(text_font);
	Preferences.setString("Preferences");
	Preferences.setCharacterSize(20);
	Preferences.setFillColor(sf::Color::Black);
	Preferences.setPosition(140, 160);

	sf::Text AS;
	AS.setFont(text_font);
	AS.setString("Account settings");
	AS.setCharacterSize(20);
	AS.setFillColor(sf::Color::Black);
	AS.setPosition(140, 190);

	sf::Text RP;
	RP.setFont(text_font);
	RP.setString("Restore purchases");
	RP.setCharacterSize(20);
	RP.setFillColor(sf::Color::Black);
	RP.setPosition(140, 220);

	sf::Sprite PFPb;
	PFPb.setTexture(PFP);
	PFPb.setPosition(300, 110);
	PFPb.setScale(0.07f, 0.07f);

	window.draw(rectangle_shadow);
	window.draw(rectangle_white);
	window.draw(name);
	window.draw(PFPb);
	window.draw(Preferences);
	window.draw(AS);
	window.draw(RP);
	//window.display();
}

void draw_buttons(sf::RenderWindow& window, int rotation){

	sf::Texture Home;
	sf::Texture Menu;
	sf::Texture AP;
	sf::Texture Feed;
	sf::Texture QM;
	if (!Home.loadFromFile("Resources/images/Home.png") || !Menu.loadFromFile("Resources/images/Menu.png") || !AP.loadFromFile("Resources/images/AP.png") || !Feed.loadFromFile("Resources/images/Feed.png") || !QM.loadFromFile("Resources/images/QM.png")) {
		cout << "Failed to load image!" << endl;
		return;
	}

	sf::Sprite HomeButton;
	HomeButton.setTexture(Home);
	HomeButton.setPosition(40.0f, 40.0f);
	HomeButton.setScale(0.1f, 0.1f);

	sf::Sprite MenuButton;
	MenuButton.setTexture(Menu);
	MenuButton.setPosition(45.0f, 115.0f);
	MenuButton.setScale(0.08f, 0.08f);

	sf::Sprite APButton;
	APButton.setTexture(AP);
	APButton.setPosition(35.0f, 200.0f);
	APButton.setScale(0.12f, 0.12f);
	APButton.setRotation(rotation);

	sf::Sprite FeedButton;
	FeedButton.setTexture(Feed);
	FeedButton.setPosition(45.0f, 300.0f);
	FeedButton.setScale(0.08f, 0.08f);

	sf::Sprite QMButton;
	QMButton.setTexture(QM);
	QMButton.setPosition(50.0f, 400.0f);
	QMButton.setScale(0.05f, 0.05f);

	window.draw(HomeButton);
	window.draw(MenuButton);
	window.draw(APButton);
	window.draw(FeedButton);
	window.draw(QMButton);
	//window.display();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) { // Sprawdzanie, czy kliknięto lewym przyciskiem
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Pobranie pozycji kursora w oknie

					// Sprawdzanie, czy kliknięcie miało miejsce w obszarze prostokąta
					if (rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
						std::cout << "Kliknięto wewnątrz prostokąta!" << std::endl;
						rectangle.setFillColor(sf::Color::Red); // Zmiana koloru prostokąta po kliknięciu
					}
					else {
						std::cout << "Kliknięto poza prostokątem." << std::endl;
					}
				}
			}
		}

		// Czyszczenie okna
		window.clear(sf::Color::White);

		// Rysowanie prostokąta
		window.draw(rectangle);

		// Wyświetlanie zawartości okna
		window.display();
	}
}



