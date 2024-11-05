#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"

using namespace std;

int APRotation = 0;

int main() {
    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(1280, 780), "Plantly Care", sf::Style::Titlebar | sf::Style::Close);
    


    // Główna pętla
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Zamykanie okna

        // Czyszczenie okna i rysowanie tekstu
        //window.clear();
        
        }
        draw_main_screen(window);
        draw_buttons(window, event, APRotation);
        draw_logo(window);
        //open_menu(window, draw_buttons(window, event, APRotation));
        window.display();
    }

    return 0;
}