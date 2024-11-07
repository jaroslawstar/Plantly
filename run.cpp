#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"


#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

void buttons_engine(sf::RenderWindow& window, sf::Event event) {
	char url[70] = "https://github.com/jaroslawstar/Plantly/blob/master/README.md";
	std::string op = std::string("start ").append(url);

	switch (Click_Value){
	case 1:
		std::cout << "Click at 'Home' button SSSSS" << std::endl;
		draw_plants();
		//draw_menu(window, event, false);
		break;
	case 2:
		//draw_main_screen(window);
		draw_menu(window, event, true);
		break;
	case 3:
		//draw_text(window, false);
		break;
	case 4:
		draw_text(window);
		break;
	case 5:
		system(op.c_str());
		Click_Value = 0;
		break;
	default:
		break;
	}



}


/*
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

*/


/*

void Add_Plant(sf::RenderWindow& window, int Click_Value, int ButtonRotation) {
	if (Click_Value == 3){
		draw_menu(window);
	}
	else {
		draw_main_screen(window);
	}
}
*/