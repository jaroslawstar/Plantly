#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"

#ifdef _WIN32
	
	#include <windows.h>
	#include <string>
#endif

using namespace std;

void buttons_engine(sf::RenderWindow& window, sf::Event event) {
	switch (Click_Value){
	case 1:
		std::cout << "Click at 'Home' button SSSSS" << std::endl;
		draw_plants();
		draw_menu(window, event, false);
		break;
	case 2:
		draw_menu(window, event, true);
		break;
	case 3:
		
		break;
	case 4:

		break;
	case 5:
		openURL("https://github.com/jaroslawstar/Plantly/blob/master/README.md");
		break;
	default:
		break;
	}



}

void openURL(const std::string& url) {
#ifdef _WIN32
	std::wstring wide_url = std::wstring(url.begin(), url.end());
	ShellExecute(0, 0, wide_url.c_str(), 0, 0, SW_SHOW);
#endif
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