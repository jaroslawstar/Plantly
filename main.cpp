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
//#include <sqlite3.h>
#include <fstream>


using namespace std;

bool APRotation = false;
int Click_Value = 0;

bool UserSighned = 0;
bool PremiumUser = false;

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

int main() {
    check_user();

    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(1280, 780), "Plantly Care", sf::Style::Titlebar | sf::Style::Close);




    draw_clear_screen(window);

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
                    cout << "Mouse clicked at: ("
                        << mousePosition.x << ", "
                        << mousePosition.y << ")" << std::endl;
                    // Check if click is in targetL
                    if (targetL.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        cout << "Click at 'LogIn' button" << std::endl;
                        draw_login_screen(window); // Call functionL
                    }
                    if (targetS.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        cout << "Click at 'SignUp' button" << std::endl;
                        draw_signup_screen(window); // Call functionS
                    }
                    if (targetN.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        cout << "Click at 'Next' button" << std::endl;
                        UserSighned = true;
                        draw_signup_screen(window); // Call functionS
                    }
                }


            }
            else {


                //draw_signup_screen(window);
                draw_main_screen(window);
                draw_buttons(window, event, APRotation);
                //draw_logo(window);
                //open_menu(window, event, draw_buttons(window, event, APRotation));
                //draw_buttons(window, event, APRotation);
                buttons_engine(window, event);
                window.display();
            }
        }
    }

    return 0;
}

/*

}*/
