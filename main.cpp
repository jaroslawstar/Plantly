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
int Click_Value = 0;

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
    check_user();

    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(1280, 780), "Plantly Care", sf::Style::Titlebar | sf::Style::Close);
    UserData User_Data;

    char url[70] = "https://github.com/jaroslawstar/Plantly/blob/master/README.md";
    std::string op = std::string("start ").append(url);

    if (!UserSighned)
        draw_clear_screen(window);
    else if (UserSighned)
        draw_main_screen(window);

    open_plants_db();
    // Główna pętla
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Zamykanie okna
            window.clear();


            if (UserSighned == false) {
                sf::RectangleShape targetL(sf::Vector2f(105, 36)); // Rectangle of size 105x36
                sf::RectangleShape targetS(sf::Vector2f(105, 36)); // Rectangle of size 105x36
                sf::RectangleShape targetN(sf::Vector2f(105, 36)); // Rectangle of size 105x36
                targetL.setPosition(520, 212); // Position at (300, 250)
                targetS.setPosition(655, 212); // Position at (300, 250)
                targetN.setPosition(585, 467); // Position at (300, 250)

                // Check for mouse button click
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
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
                        UserSighned = true;
                        draw_signup_screen(window); // Call functionS
                    }
                }


            }
            else {//Main Window after login
                ///*
                draw_main_screen(window);
                draw_buttons(window, event, APRotation);

                sf::RectangleShape targetHB(sf::Vector2f(51, 51)); // Rectangle of size 105x36
                sf::RectangleShape targetMB(sf::Vector2f(51, 51)); // Rectangle of size 105x36
                sf::RectangleShape targetAPB(sf::Vector2f(51, 51)); // Rectangle of size 105x36
                sf::RectangleShape targetFB(sf::Vector2f(51, 51)); // Rectangle of size 105x36
                sf::RectangleShape targetQMB(sf::Vector2f(51, 51)); // Rectangle of size 105x36
                targetHB.setPosition(40, 40); // Position at (300, 250)
                targetMB.setPosition(45, 115); // Position at (300, 250)
                targetAPB.setPosition(35, 200); // Position at (300, 250)
                targetFB.setPosition(35, 300); // Position at (300, 250)
                targetQMB.setPosition(50, 400); // Position at (300, 250)

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked at: ("
                        << mousePosition.x << ", "
                        << mousePosition.y << ")" << std::endl;
                    // Check if click is in targetL
                    if (targetHB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'Home' button" << std::endl;

                        APRotation = false;
                        draw_plants(window);
                    }
                    if (targetMB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'Menu' button" << std::endl;

                        APRotation = false;
                        draw_menu(window, event, true);
                    }
                    if (targetAPB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'Add Plant' button" << std::endl;
                        if (!APRotation)
                            APRotation = true;
                        else if (APRotation)
                            APRotation = false;
                        // Call functionS
                    }
                    if (targetFB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'Feed' button" << std::endl;

                        APRotation = false;
                        draw_text(window);
                    }
                    if (targetQMB.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        std::cout << "Click at 'Question Mark' button" << std::endl;

                        APRotation = false;
                        system(op.c_str());
                        
                    }
                }
                //draw_signup_screen(window);
                
                //draw_logo(window);
                //open_menu(window, event, draw_buttons(window, event, APRotation));
                //draw_buttons(window, event, APRotation);
                //buttons_engine(window, event);
                window.display();
            }
        }
    }

    return 0;
}

/*

}*/
