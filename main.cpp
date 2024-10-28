#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"

using namespace std;

int main() {
    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(1280, 780), "Plantly Care", sf::Style::Titlebar | sf::Style::Close);
    /*
    // Ustawienia tekstu
    sf::Font font;
    if (!font.loadFromFile("Resorses/Fonts/arial.ttf")) {
        cout << "Failed to load font";
        return -1; // Zakończ program, jeśli nie uda się załadować czcionki
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(200, 250); // Pozycja tekstu
    */
    // Główna pętla
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Zamykanie okna
        }

        // Czyszczenie okna i rysowanie tekstu
        window.clear();
        
        //draw_main_screen(window);
        //draw_logo(window);
        //draw_menu(window);
        draw_buttons(window, 0);
        window.display();
    }

    return 0;
}