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
/*
#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdlib> // dla system()
#endif
*/
using namespace std;


int draw_main_screen(sf::RenderWindow& window){

	int Click_Value = 0;

	// Tworzenie prostok?ta
	sf::RectangleShape rectangle_main(sf::Vector2f(1280.0f, 780.0f)); // Rozmiar prostokata na cale okno
	rectangle_main.setFillColor(sf::Color(0xF7F7F7FF));
	window.draw(rectangle_main);
	sf::RectangleShape rectangle_white(sf::Vector2f(1160.0f, 70.0f)); 
	rectangle_white.setFillColor(sf::Color::White);
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

void draw_menu(sf::RenderWindow& window, sf::Event event, bool show) { //, int Click_Value_m
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
	if (!PFP.loadFromFile("Resources/images/pfp.png")) {
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
	PFPb.setPosition(300, 100);
	PFPb.setScale(0.15f, 0.15f);

	

	if (show == true) {
		window.draw(rectangle_shadow);
		window.draw(rectangle_white);
		window.draw(name);
		window.draw(PFPb);
		window.draw(Preferences);
		window.draw(AS);
		window.draw(RP);
		//draw_menu(window, event, true);
	}
	else if (show == false) {
		rectangle_white.setPosition(2000, 2000);
		rectangle_shadow.setPosition(2000, 2000);
		name.setPosition(2000, 2000); // Pozycja tekstu
		Preferences.setPosition(2000, 2000);
		AS.setPosition(2000, 2000);
		RP.setPosition(2000, 2000);
		PFPb.setPosition(2000, 2000);
	}
	//window.display();
}

int draw_buttons(sf::RenderWindow& window, sf::Event event, bool rotation){

	//int Click_Value = 0;

	sf::RectangleShape rectangle_green(sf::Vector2f(120.0f, 780.0f));
	rectangle_green.setFillColor(sf::Color(0xC4F7B7FF)); // Kolor prostokata (Cornflower Blue)

	sf::Texture Home;
	sf::Texture Menu;
	sf::Texture AP;
	sf::Texture Feed;
	sf::Texture QM;
	if (!Home.loadFromFile("Resources/images/Home.png") || !Menu.loadFromFile("Resources/images/Menu.png") || !AP.loadFromFile("Resources/images/AP.png") || !Feed.loadFromFile("Resources/images/Feed.png") || !QM.loadFromFile("Resources/images/QM.png")) {
		cout << "Failed to load image!" << endl;
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
	APButton.setScale(0.12f, 0.12f);
	if (rotation) {
		APButton.setRotation(45);
		APButton.setPosition(63.0f, 186.0f);
	}
	else if (!rotation) {
	APButton.setPosition(35.0f, 200.0f);
	}

	sf::Sprite FeedButton;
	FeedButton.setTexture(Feed);
	FeedButton.setPosition(45.0f, 300.0f);
	FeedButton.setScale(0.08f, 0.08f);

	sf::Sprite QMButton;
	QMButton.setTexture(QM);
	QMButton.setPosition(50.0f, 400.0f);
	QMButton.setScale(0.05f, 0.05f);
	
	window.draw(rectangle_green);
	window.draw(HomeButton);
	window.draw(MenuButton);
	window.draw(APButton);
	window.draw(FeedButton);
	window.draw(QMButton);
	//window.display();

	
	//while (window.pollEvent(event)) {
		//if (event.type == sf::Event::Closed)
			//window.close(); // Zamykanie okna
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) { // Sprawdzanie, czy kliknięto lewym przyciskiem
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Pobranie pozycji kursora w oknie
				// Sprawdzanie, czy kliknięcie miało miejsce w obszarze prostokąta
				if (HomeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 1) {
					std::cout << "Click at 'Home' button" << std::endl;
					Click_Value = 1;
					//return Click_Value; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (HomeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 1) {
					std::cout << "UnClick at 'Home' button" << std::endl;
					Click_Value = 0;
					//return Click_Value; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (MenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 2) {
					std::cout << "Click at 'Menu' button" << std::endl;
					Click_Value = 2;
					//return Click_Value = 2; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (MenuButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 2) {
					std::cout << "UnClick at 'Menu' button" << std::endl;
					Click_Value = 0;
					//return Click_Value = 2; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (APButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 3) {
					std::cout << "Click at 'Add Plant' button" << std::endl;
					APRotation = true;
					Click_Value = 3;
					//return Click_Value = 3; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (APButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 3) {
					std::cout << "UnClick at 'Add Plant' button" << std::endl;
					APRotation = false;
					Click_Value = 0;
					//return Click_Value = 0; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (FeedButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 4) {
					std::cout << "Click at 'Feed' button" << std::endl;
					Click_Value = 4; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (FeedButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 4) {
					std::cout << "UnClick at 'Feed' button" << std::endl;
					Click_Value = 0;
					//return Click_Value = 4; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (QMButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value != 5) {
					std::cout << "Click at 'Question Mark' button" << std::endl;
					Click_Value = 5; // Zmiana wartosci zmiennej a po kliknięciu
				}
				else if (QMButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && Click_Value == 5) {
					std::cout << "UnClick at 'Question Mark' button" << std::endl;
					Click_Value = 0;
					//return Click_Value = 5; // Zmiana wartosci zmiennej a po kliknięciu
				}
				//else
					//return Click_Value;
				return Click_Value;
			}
			
		}
	//}
	
}

void draw_plants() {

}

