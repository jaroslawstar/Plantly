#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <string>

#include "Header.h"
#include <SQLite/sqlite3.h>
#include <fstream>



bool APRotation = false;
bool show = false;

ButtonClick buttonClick = ButtonClick::undefined;

bool UserSighned = 0;
bool PremiumUser = false;
/*
class Plant {
public:
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

    //Window creation
    sf::RenderWindow window(sf::VideoMode(1280, 780), "Plantly Care", sf::Style::Titlebar | sf::Style::Close);
    UserData User_Data;
    AppState appState = AppState::LOGGED_OUT;
    
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
    sf::RectangleShape targetMB(sf::Vector2f(51, 51));
    sf::RectangleShape targetAPB(sf::Vector2f(51, 51));
    sf::RectangleShape targetFB(sf::Vector2f(51, 51));
    sf::RectangleShape targetQMB(sf::Vector2f(51, 51));
    targetHB.setPosition(40, 40);
    targetMB.setPosition(45, 115);
    targetAPB.setPosition(35, 200);
    targetFB.setPosition(35, 300);
    targetQMB.setPosition(50, 400);

    //Open database (check)
    open_plants_db();
    draw_clear_screen(window);
    //Main loop
    //draw_clear_screen(window);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check for mouse button click
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                //----------Logged_OUT_Buttons----------
                if (appState == AppState::LOGGED_OUT) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked at: ("
                        << mousePosition.x << ", "
                        << mousePosition.y << ")" << std::endl;
                    // Check if click is in targetL
                    if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'LogIn' button" << std::endl;
                        draw_login_screen(window); // Call functionL
                    }
                    if (targetS.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'SignUp' button" << std::endl;
                        draw_signup_screen(window); // Call functionS
                    }
                    if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'Next' button" << std::endl;
                        appState = AppState::LOGGED_IN;
                    }
                }
                //----------Logged_IN_Buttons----------
                if (appState == AppState::LOGGED_IN) {
                    buttonsEngine(window, targetHB, targetMB, targetAPB, targetFB, targetQMB);
                }
            }
        }
        window.clear();

        if (appState == AppState::LOGGED_OUT) {
            draw_clear_screen(window);
        }
        else if (appState == AppState::LOGGED_IN) {
            draw_main_screen(window);
            draw_buttons(window, APRotation);
            //draw_plants(window, true);
            //if (buttonClick == ButtonClick::Menu) {
            //   draw_menu(window, true);
            //    std::cout << "draw_menu(window, true);" << std::endl;
            //}
            //else {
            //    draw_menu(window, false);
            //    std::cout << "draw_menu(window, FALSE);" << std::endl;
            //}

            switch (buttonClick) {
            case ButtonClick::Home:
                draw_plants(window, true);
                draw_menu(window, false);
                draw_text(window, false);
                window.display();
                break;
            case ButtonClick::Menu:
                draw_plants(window, false);
                draw_menu(window, true);
                draw_text(window, false);
                window.display();
                break;
            case ButtonClick::AP:
                draw_plants(window, false);
                draw_menu(window, false);
                draw_text(window, false);
                window.display();
                break;
            case ButtonClick::Feed:
                draw_plants(window, false);
                draw_menu(window, false);
                draw_text(window, true);
                window.display();
                break;
            case ButtonClick::QM:
                system(op.c_str());
                buttonClick = ButtonClick::undefined;
                break;
            default:
                break;
            }
        }

        window.display();
    }
    
    return 0;
}