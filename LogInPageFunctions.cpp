/*
Wazne parametry:
 Okno 1280x780
	sf::Vector2u windowSize = window.getSize(); //Pobor rozmiaru okna
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

//#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>

#include "Header.h"
#include <SQLite/sqlite3.h>
#include <fstream>

using namespace std;

void draw_clear_screen(sf::RenderWindow& window) {
	//window.clear();
	sf::Texture ClearScreen;
	if (!ClearScreen.loadFromFile("Resources/images/Clear_MainPage.png")) {
		cout << "Failed to load Clear screen!" << endl;
		return;
	}
	sf::Sprite ClearScreenP(ClearScreen);
	//ClearScreenP.setTexture(ClearScreen);
	//LogINScreenP.setPosition(0, 0);
	window.draw(ClearScreenP);
	window.display();

}

void draw_signup_screen(sf::RenderWindow& window) {
	//window.clear();
	sf::Texture SignUPScreen;
	if (!SignUPScreen.loadFromFile("Resources/images/SignUp_MainPage.png")) {
		cout << "Failed to load Sign up screen!" << endl;
		return;
	}
	sf::Sprite SignUPScreenP(SignUPScreen);
	window.draw(SignUPScreenP);
	window.display();

}

void draw_login_screen(sf::RenderWindow& window) {
	//window.clear();
	sf::Texture LogINScreen;
	if (!LogINScreen.loadFromFile("Resources/images/LogIn_MainPage.png")) {
		cout << "Failed to load Log in screen!" << endl;
		return;
	}
	sf::Sprite LogINScreenP(LogINScreen);
	window.draw(LogINScreenP);
	window.display();

}

void check_user() {
	if ("true!" == "true")
		UserSighned = true;
	else
		UserSighned = false;
}

