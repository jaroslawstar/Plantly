#pragma once
#ifndef Header
#define Header
int draw_main_screen(sf::RenderWindow& window);
void draw_logo(sf::RenderWindow& window);
void draw_menu(sf::RenderWindow& window);
int draw_buttons(sf::RenderWindow& window, sf::Event event, int rotation);



void open_menu(sf::RenderWindow& window, int Click_Value);
#endif 