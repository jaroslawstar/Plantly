#pragma once
#ifndef Header
#define Header

#include<chrono>

enum class AppState {
    LOGGED_OUT,
    LOGGED_IN,
};

extern AppState appState;
extern bool UserSighned;
extern const size_t plantsnum;

void draw_signup_screen(sf::RenderWindow& window, sf::Event event);
void draw_login_screen(sf::RenderWindow& window, sf::Event event);
void draw_clear_screen(sf::RenderWindow& window);
void draw_main_screen(sf::RenderWindow& window);
//void draw_logo(sf::RenderWindow& window);
void draw_menu(sf::RenderWindow& window, sf::Event event, bool show);
void draw_plants(sf::RenderWindow& window, sf::Event event, bool show, const std::string& dbFile, sf::Vector2i mousePosition = sf::Vector2i(-1, -1));
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

void CenterBlobImage(sf::RenderWindow& window, const std::vector<uint8_t>& image, sf::Texture& texture, sf::Sprite& sprite);
//bool init_sqcloud();
int plants_number();

std::string timePointToString(const std::chrono::system_clock::time_point& timePoint);
std::chrono::system_clock::time_point parseDateTime(const std::string& datetime);   
std::string timePointToString(const std::chrono::system_clock::time_point& timePoints);
class UserData {
public:
    int id;
    std::string name;
    std::string email;
    std::string password;
    std::string pstatus;
    std::vector<uint8_t> image;
    int datetimestamp;

    void saveToDatabase(const std::string& dbFile); // Function declaration
    void set_image(const std::string& dbFile);
};

class Plant {
public:
    int id;
    int userid;
    int days;
    std::string name;
    std::string type;
    std::string location;
    std::vector<uint8_t> image;
    int datetimestamp;
    std::string waterDate;
    //daaaaate

    Plant() : id(NULL), userid(NULL), days(NULL), name(""), type(""), location(""), image(NULL), datetimestamp(NULL), waterDate("") { // Default constructor
        std::cout << "Plant default constructor called." << std::endl;
    }
    void showObject(sf::RenderWindow& Window, sf::Texture& frameTexture, sf::Texture& maskTexture, sf::Sprite& Sprite, float posX, float posY, sf::Font& Font);
    void showObjectInfo(sf::RenderWindow& window, sf::Texture& frameTexture, sf::Texture& MaskTexture, sf::Sprite& Sprite, float posX, float posY, sf::Font& Font);
    void saveToDatabase(const std::string& dbFile);
    void fetch_plants_from_db(const std::string& dbFile);
    std::string fetchDateTime(const std::string& dbFile, bool dateAdded);
    void insertCurrentDateTime(const std::string& dbFile);
    void populate(int id_, int userid_, int days_, const std::string& name_, const std::string& type_, const std::string& location_, std::vector<uint8_t> image_, int datetimestamp_, int waterDate_) { ///daaaaaate
        id = id_;
        userid = userid_;
        days = days_;
        name = name_;
        type = type_;
        location = location_;
        image = image_;
        datetimestamp = datetimestamp_;
        waterDate = waterDate_;
    }
};


extern UserData User;
extern Plant usersPlants[];

#endif 