#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#define NOMINMAX
#ifdef _WIN32
#include <windows.h>
#else
//#include <cstdlib> // dla system()
#endif
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>
#include "Header.h"
#include <SQLite/sqlite3.h>
#include <fstream>
#include "sqlitecloud/sqcloud.h"
#include <chrono>

AppState appState = AppState::LOGGED_OUT;

UserData User;

bool UserSighned = 0;

const size_t plantsnum = 10;

Plant usersPlants[plantsnum];

/*
class Plant {
public:111
    std::string name;
    int amount;
    std::string color;

    void getInput() {
        std::cout << "Enter object name: ";
        std::getline(std::cin, name);
        std::cout << "Enter amount: ";
        std::cin >> amount;
        std::cin.ignore(); // Clear newline from input buffer
        std::cout << "Enter color: ";
        std::getline(std::cin, color);
    }
};
*/



int main() {
    //check_user();
   /*
    if (init_sqcloud()) {
        std::cout << "FUCKING FINALLY" << std::endl; 
    }
   */
    //Window creation




    int a = 5, b = 10;

    int sum = callAddNumbers(a, b);
    std::cout << "The sum of " << a << " and " << b << " is: " << sum << std::endl;


    a = 10; b = 10;
    sum = callAddNumbers(a, b);
    // Call the function that interacts with Python
    std::cout << "The sum of " << a << " and " << b << " is: " << sum << std::endl;


    //std::cout << "Test ai Hello: " << callPythonFunctionHello() << std::endl;


    sum = callAddNumbers(a, b);
    std::cout << "The sum of " << a << " and " << b << " is: " << sum << std::endl;

    sf::RenderWindow window(sf::VideoMode(1280, 780), "Plantly Care", sf::Style::Titlebar | sf::Style::Close);
    sf::Image LogoIcon;
    LogoIcon.loadFromFile("Resources/images/Logo.png");
    window.setIcon(LogoIcon.getSize().x, LogoIcon.getSize().y, LogoIcon.getPixelsPtr());

    UserData User_Data;


    //----------Link_for_QM----------
    char url[70] = "https://github.com/jaroslawstar/Plantly/blob/master/README.md";
    std::string op = std::string("start ").append(url);

    //----------Buttons----------
    //_Logged_OUT_
    sf::RectangleShape targetL(sf::Vector2f(105, 36)); //Rectangle of size 105x36
    sf::RectangleShape targetS(sf::Vector2f(105, 36));
    sf::RectangleShape targetN(sf::Vector2f(105, 36));
    targetL.setPosition(520, 212); //Position at (520, 212)
    targetS.setPosition(655, 212);
    targetN.setPosition(585, 467);
    //_Logged_IN_
    sf::RectangleShape targetHB(sf::Vector2f(51, 51));
    sf::RectangleShape targetMainScreen(sf::Vector2f(1160, 710));
    sf::RectangleShape targetMB(sf::Vector2f(51, 51));
    sf::RectangleShape targetAPB(sf::Vector2f(51, 51));
    sf::RectangleShape targetFB(sf::Vector2f(51, 51));
    sf::RectangleShape targetQMB(sf::Vector2f(51, 51));
    targetHB.setPosition(40, 40);
    targetMainScreen.setPosition(120, 70);
    targetMB.setPosition(45, 115);
    targetAPB.setPosition(35, 200);
    targetFB.setPosition(35, 300);
    targetQMB.setPosition(50, 400);

    //Open database (check if works)
    open_plants_db();

    
    //Main loop

    while (window.isOpen()) {
        sf::Event event;
        draw_clear_screen(window);
        while (appState == AppState::LOGGED_OUT) {  //Log out window loop (window.display() is unneseccary when defined in draw window functions)
            //draw_clear_screen(window);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    ExecutePy_FinalizeEx();
                    window.close();
                }

                if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
                    //----------Logged_OUT_Buttons----------
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked at: ("
                        << mousePosition.x << ", "
                        << mousePosition.y << ")" << std::endl;
                    // Check if click is in targetL
                    if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'LogIn' button" << std::endl;
                        draw_login_screen(window, event);
                    }
                    else if (targetS.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'SignUp' button" << std::endl;
                        draw_signup_screen(window, event);
                    }

                }
            }
        }
        window.display();
        window.clear();
        //window.display();
        

        if (appState == AppState::LOGGED_IN)
        {
            draw_main_screen(window);
            draw_plants(window, event, false, "plantly.db");

            while (appState == AppState::LOGGED_IN) {   //Log in window loop
                draw_main_screen(window);
                //draw_plants(window, event, false, "plantly.db");

                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        ExecutePy_FinalizeEx();
                        window.close();
                    }
                    if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {

                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        std::cout << "Mouse clicked at: ("
                            << mousePosition.x << ", "
                            << mousePosition.y << ")" << std::endl;
                        if (targetHB.getGlobalBounds().contains(mousePosition.x, mousePosition.y) ||
                            targetMainScreen.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            std::cout << "Click at 'Home' button" << std::endl;
                            draw_menu(window, event, false);
                            draw_plants(window, event, true, "plantly.db", mousePosition);
                        }
                        else if (targetMB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            std::cout << "Click at 'Menu' button" << std::endl;

                            draw_menu(window, event, true);

                        }
                        else if (targetAPB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            std::cout << "Click at 'Add Plant' button" << std::endl;
                            draw_menu(window, event, false);
                            //draw_main_screen(window);
                            //auto blob = GetFileBlobDialog();
                            /*
                            if (!blob.empty()) {
                                std::cout << "File loaded successfully with size: " << blob.size() << " bytes." << std::endl;
                            }
                            else {
                                std::cout << "No file loaded or operation failed." << std::endl;
                            }
                            */
                            draw_AP_screen(window, event, true);
                        }
                        else if (targetFB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            std::cout << "Click at 'Feed' button" << std::endl;
                            draw_text(window, true);
                        }
                        else if (targetQMB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                            std::cout << "Click at 'Question Mark' button" << std::endl;
                            system(op.c_str());

                        }
                    }
                }
            }
        }
    }

    return 0;
}