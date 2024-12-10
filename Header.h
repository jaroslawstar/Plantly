#pragma once
#ifndef Header
#define Header
extern bool APRotation;
extern bool show;
extern bool UserSighned;
extern bool PremiumUser;

enum class AppState {
    LOGGED_OUT,
    LOGGED_IN,
};

enum class ButtonClick {
    undefined,
    Home,
    Menu,
    AP,
    Feed,
    QM,
};
extern ButtonClick buttonClick;

void draw_signup_screen(sf::RenderWindow& window);
void draw_login_screen(sf::RenderWindow& window);
void draw_clear_screen(sf::RenderWindow& window);
void draw_main_screen(sf::RenderWindow& window);
//void draw_logo(sf::RenderWindow& window);
void draw_buttons(sf::RenderWindow& window, bool rotation);
void draw_menu(sf::RenderWindow& window, bool show);
void draw_plants(sf::RenderWindow& window, sf::Event event, bool show);
void draw_text(sf::RenderWindow& window, bool show); //, bool show


void buttonsEngine(sf::RenderWindow& window, sf::RectangleShape targetHB, sf::RectangleShape targetMB, sf::RectangleShape targetAPB, sf::RectangleShape targetFB, sf::RectangleShape targetQMB);
std::vector<unsigned char> readFile(const std::string& filePath);
void saveBlobToFile(const std::vector<unsigned char>& blobData, const std::string& fileName);
void open_plants_db();

void draw_AP_screen(sf::RenderWindow& window, bool show);
//void open_menu(sf::RenderWindow& window, sf::Event event, int Click_Value);
//void buttons_engine(sf::RenderWindow& window, sf::Event event);
//void openURL(const std::string& url);
//void check_user();

void handleTextInput(sf::Event& event, std::string& text, sf::Text& textDisplay);


class UserData {
public:
    std::string name;
    std::string age;
    std::string email;

    void saveToDatabase(); // Function declaration
};

class Plant {
public:
    std::string name;
    int amount;
    std::string color;

    void getInput();

    
};


#endif 