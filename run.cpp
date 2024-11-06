#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"
using namespace std;

void buttons_engine(sf::RenderWindow& window, sf::Event event, int Click_Value) {
	switch (Click_Value){
	case 1:
		std::cout << "Click at 'Home' button SSSSS" << std::endl;
		break;
	case 2:
		draw_menu(window);
		break;
	case 3:
		APRotation = true;
		break;
	default:
		break;
	}



}





void open_menu(sf::RenderWindow& window, sf::Event event,  int Click_Value) {
	if (Click_Value == 2)
		draw_menu(window);
	else if (Click_Value == 0) {
		draw_main_screen(window);
		draw_buttons(window, event, 0);
	}
	//else{
	//	draw_menu(window);
	//}
	
	
}




void Add_Plant(sf::RenderWindow& window, int Click_Value, int ButtonRotation) {
	if (Click_Value == 3){
		draw_menu(window);
	}
	else {
		draw_main_screen(window);
	}
}