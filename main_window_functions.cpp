/*
Wa?ne parametry: 
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

void draw_main_screen(sf::RenderWindow& window){

	// Tworzenie prostok?ta
	sf::RectangleShape rectangle_main(sf::Vector2f(1280.0f, 780.0f)); // Rozmiar prostok?ta na ca?e okno
	rectangle_main.setFillColor(sf::Color(0xF7F7F7FF));
	window.draw(rectangle_main);
	sf::RectangleShape rectangle_green(sf::Vector2f(120.0f, 780.0f));
	rectangle_green.setFillColor(sf::Color(0xC4F7B7FF)); // Kolor prostok?ta (Cornflower Blue)
	window.draw(rectangle_green);
	sf::RectangleShape rectangle_white(sf::Vector2f(1160.0f, 70.0f)); 
	rectangle_white.setFillColor(sf::Color(0xFFFFFFFF));
	rectangle_white.setPosition(120, 0);
	window.draw(rectangle_white);
}

void draw_logo(sf::RenderWindow& window) {
	// Ustawienia tekstu
	sf::Font logo_font;
	if (!logo_font.loadFromFile("Resorses/Fonts/Inria_Serif/InriaSerif-LightItalic.ttf")) {
		cout << "Failed to load font";
	}
	sf::Text logo;
	logo.setFont(logo_font);
	logo.setString("PLANTLY");
	logo.setCharacterSize(50);
	logo.setFillColor(sf::Color::Black);
	logo.setPosition(640, 0); // Pozycja tekstu

	window.draw(logo);
}

int buttons(sf::RenderWindow& window){
	// Tworzenie ko?a
	sf::CircleShape circle(100.0f); // Promie? ko?a
	circle.setFillColor(sf::Color(255, 165, 0)); // Kolor ko?a (Pomara?czowy)
	circle.setPosition(350.0f, 200.0f); // Pozycja ko?a
	window.draw(circle);
	return 1;
}




