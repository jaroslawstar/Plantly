/*

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Header.h"

using namespace std;

void open_menu(sf::RenderWindow& window) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
           if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { // Sprawdzanie, czy kliknięto lewym przyciskiem
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Pobranie pozycji kursora w oknie

                    // Sprawdzanie, czy kliknięcie miało miejsce w obszarze prostokąta
                    if (rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                        std::cout << "Kliknięto wewnątrz prostokąta!" << std::endl;
                        rectangle.setFillColor(sf::Color::Red); // Zmiana koloru prostokąta po kliknięciu
                    }
                    else {
                        std::cout << "Kliknięto poza prostokątem." << std::endl;
                    }
                }
            }
        }

        // Czyszczenie okna
        window.clear(sf::Color::White);

        // Rysowanie prostokąta
        window.draw(rectangle);

        // Wyświetlanie zawartości okna
        window.display();
    }

    return 0;
}

*/