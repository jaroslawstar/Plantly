#pragma once
#ifndef Header
#define Header


enum class AppState {
    LOGGED_OUT,
    LOGGED_IN,
};

extern AppState appState;
extern bool UserSighned;


void draw_signup_screen(sf::RenderWindow& window, sf::Event event);
void draw_login_screen(sf::RenderWindow& window, sf::Event event);
void draw_clear_screen(sf::RenderWindow& window);
void draw_main_screen(sf::RenderWindow& window);
//void draw_logo(sf::RenderWindow& window);
void draw_X(sf::RenderWindow& window, int x, int y);
void draw_menu(sf::RenderWindow& window, sf::Event event, bool show);
void draw_plants(sf::RenderWindow& window, sf::Event event, bool show, const std::string& dbFile);
void draw_text(sf::RenderWindow& window, bool show); 


std::vector<unsigned char> readFile(const std::string& filePath);
void saveBlobToFile(const std::vector<unsigned char>& blobData, const std::string& fileName);
void open_plants_db();
std::vector<uint8_t> GetFileBlobDialog();

void draw_AP_screen(sf::RenderWindow& window, sf::Event event, bool show);
//void open_menu(sf::RenderWindow& window, sf::Event event, int Click_Value);
//void buttons_engine(sf::RenderWindow& window, sf::Event event);
//void openURL(const std::string& url);
bool check_user(std::string email, std::string password, const std::string& dbFile);
bool check_user(std::string name, std::string email, std::string password1, std::string password2, const std::string& dbFile);
void check_user_in(std::string email, std::string password, const std::string& dbFile);

std::string join(const std::vector<std::string>& elements, const std::string& delimiter);
void showErrorDialog(const std::string& title, const std::string& message);
std::string generate_username(std::string email);

class UserData {
public:
    int id;
    std::string name;
    std::string email;
    std::string password;
    std::string pstatus;
    std::vector<uint8_t> image;

    void saveToDatabase(const std::string& dbFile); // Function declaration
    void set_image(const std::string& dbFile);
};

class Plant {
public:
    std::string name;
    int days;
    std::string filePath;

    void saveToDatabase(const std::string& dbFile);

    
};

extern UserData User;
extern Plant usersPlants[];

#endif 