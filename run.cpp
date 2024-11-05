#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"

using namespace std;

void open_menu(sf::RenderWindow& window, int Click_Value) {
	if (Click_Value == 2)
		draw_menu(window);
	else
		draw_main_screen(window);
}

void Add_Plant(sf::RenderWindow& window, int Click_Value, int APRotation) {
	if (Click_Value == 3){
		draw_menu(window);
	}
	else {
		draw_main_screen(window);
	
	}
}