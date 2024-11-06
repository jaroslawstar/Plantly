#pragma once
#ifndef Header
#define Header
extern bool APRotation;
int draw_main_screen(sf::RenderWindow& window);
void draw_logo(sf::RenderWindow& window);
void draw_menu(sf::RenderWindow& window);
int draw_buttons(sf::RenderWindow& window, sf::Event event, bool rotation);
void draw_plants();



//void open_menu(sf::RenderWindow& window, sf::Event event, int Click_Value);
void buttons_engine(sf::RenderWindow& window, sf::Event event, int Click_Value);
#endif 