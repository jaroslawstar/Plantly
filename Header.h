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
//std::chrono::system_clock::time_point parseDateTime(const std::string& datetime);   
std::string timePointToString(const std::chrono::system_clock::time_point& timePoints);

bool isDateInPast(const std::string& dateStr, const std::string& format = "%d.%m.%Y");
class UserData {
public:
    int id;
    std::string name;
    std::string email;
    std::string password;
    std::string pstatus;
    std::vector<uint8_t> image;
    std::tm datetimestamp = {};


    void saveToDatabase(const std::string& dbFile); // Function declaration
    void set_image(const std::string& dbFile);

private:
    bool parseDateTimeStamp(const std::string& datetime) {
        std::istringstream ss(datetime);
        ss >> std::get_time(&datetimestamp, "%Y-%m-%d %H:%M:%S");
        return !ss.fail();
    }
};





class Plant {
public:
    int id;
    int userid;
    int days;
    std::string name;
    std::string type;
    std::string location;
    std::string info;
    std::vector<uint8_t> image;
    std::tm datetimestamp = {};
    std::tm waterDate = {};
    //daaaaate

    Plant() : id(NULL), userid(NULL), days(NULL), name(""), type(""), location(""), info(""), image(NULL), datetimestamp({}), waterDate({}) { // Default constructor
        std::cout << "Plant default constructor called." << std::endl;
    }
    void showObject(sf::RenderWindow& Window, sf::Texture& frameTexture, sf::Texture& maskTexture, sf::Sprite& Sprite, float posX, float posY, sf::Font& Font);
    void showObjectInfo(sf::RenderWindow& window, sf::Texture& frameTexture, sf::Texture& MaskTexture, sf::Sprite& Sprite, float posX, float posY, sf::Font& Font, bool show);
    void showWTTObject(sf::RenderWindow& window, sf::Texture& frameTexture, sf::Texture& MaskTexture, sf::Sprite& Sprite, float posX, float posY, sf::Font& Font);
    void saveToDatabase(const std::string& dbFile);
    void fetch_plants_from_db(const std::string& dbFile);
    bool fetchDateTime(const std::string& dbFile, bool dateAdded);
    void GenerateAndInsertInfo(const std::string& dbFile);
    void insertCurrentDateTime(const std::string& dbFile);
    void insertWaterLog(const std::string& dbFile);
    void populate(int id_, int userid_, int days_, const std::string& name_, const std::string& type_, const std::string& location_, const std::string& info_, std::vector<uint8_t> image_) { ///daaaaaate
        id = id_;
        userid = userid_;
        days = days_;
        name = name_;
        type = type_;
        location = location_;
        info = info_;
        image = image_;
    };
    void displayDatetime() const {
        std::cout << "Stored DateTimeStamp: " << std::put_time(&datetimestamp, "%Y-%m-%d %H:%M:%S") << std::endl;
        std::cout << "Stored WaterDate: " << std::put_time(&waterDate, "%Y-%m-%d %H:%M:%S") << std::endl;
    };

    // Method to add seconds and return resulting datetime as a string
    std::string getDatetimeAfterSeconds(int seconds) const {
        std::tm tempDatetime = waterDate; // Create a temporary copy
        time_t time = std::mktime(&tempDatetime);
        time += seconds;

        // Create a temporary std::tm object to store the result
        std::tm resultDatetime;
        localtime_s(&resultDatetime, &time); // Use localtime_s to safely convert time_t to std::tm

        return formatDatetime(resultDatetime);
    }

    // Method to add days and return resulting datetime as a string
    std::string getDatetimeAfterDays(int days) const {
        return getDatetimeAfterSeconds(days * 24 * 3600); // Delegate to seconds
    }

    // Method to set the current datetime
    void setCurrentDatetime() {
        std::time_t now = std::time(nullptr);  // Get current time as time_t
        localtime_s(&waterDate, &now);     // Use localtime_s for safer conversion
    }
    // Helper method to format a std::tm object as a string
    std::string formatDatetime(const std::tm& datetime) const {
        std::ostringstream oss;
        oss << std::put_time(&datetime, "%d.%m.%Y"); // Here to change appearance
        return oss.str();
    }

private:
    // Method to parse a datetime string into std::tm
    bool parseDateTimeStamp(const std::string& datetime) {
        std::istringstream ss(datetime);
        ss >> std::get_time(&datetimestamp, "%Y-%m-%d %H:%M:%S");
        return !ss.fail();
    };
    bool parseWaterDateTime(const std::string& datetime) {
        std::istringstream ss(datetime);
        ss >> std::get_time(&waterDate, "%Y-%m-%d %H:%M:%S");
        return !ss.fail();
    }
};


extern UserData User;
extern Plant usersPlants[];




int callAddNumbers(int a, int b);
std::string callGeneratePlantInfo(const std::string& subject);
std::string callGenerateHello(const std::string& subject);
std::string callPythonFunctionHello();
void ExecutePy_FinalizeEx();
void MakeText(sf::Text* sfText, const std::string& text, float maxWidth);
#endif 