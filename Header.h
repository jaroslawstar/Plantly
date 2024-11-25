#pragma once
#ifndef Header
#define Header
extern bool APRotation;
extern int Click_Value;
extern bool UserSighned;
extern bool PremiumUser;

void draw_signup_screen(sf::RenderWindow& window);
void draw_login_screen(sf::RenderWindow& window);
void draw_clear_screen(sf::RenderWindow& window);
void draw_main_screen(sf::RenderWindow& window);
//void draw_logo(sf::RenderWindow& window);
void draw_menu(sf::RenderWindow& window, sf::Event event, bool show);
void draw_buttons(sf::RenderWindow& window, sf::Event event, bool rotation);
void draw_plants(sf::RenderWindow& window);

std::vector<unsigned char> readFile(const std::string& filePath);
void saveBlobToFile(const std::vector<unsigned char>& blobData, const std::string& fileName);
//void open_plants_db();

//void open_menu(sf::RenderWindow& window, sf::Event event, int Click_Value);
void buttons_engine(sf::RenderWindow& window, sf::Event event);
void draw_text(sf::RenderWindow& window); //, bool show
//void openURL(const std::string& url);
void check_user();


#endif 