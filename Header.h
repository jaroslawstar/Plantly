#pragma once
#ifndef Header
#define Header
extern bool APRotation;
extern int Click_Value;
void draw_main_screen(sf::RenderWindow& window);
//void draw_logo(sf::RenderWindow& window);
void draw_menu(sf::RenderWindow& window, sf::Event event, bool show);
int draw_buttons(sf::RenderWindow& window, sf::Event event, bool rotation);
void draw_plants();



//void open_menu(sf::RenderWindow& window, sf::Event event, int Click_Value);
void buttons_engine(sf::RenderWindow& window, sf::Event event);
void draw_text(sf::RenderWindow& window); //, bool show
//void openURL(const std::string& url);
#endif 