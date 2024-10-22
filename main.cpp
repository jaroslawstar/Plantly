#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

int main() {
    // Tworzenie okna
    sf::RenderWindow window(sf::VideoMode(1280, 780), "SFML Window");

    // Ustawienia tekstu
    /*
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1; // Zakończ program, jeśli nie uda się załadować czcionki
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(200, 250); // Pozycja tekstu
    */
    // Główna pętla gry
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Zamykanie okna
        }

        // Czyszczenie okna i rysowanie tekstu
        window.clear();
       // window.draw(text);
        window.display();
    }

    return 0;
}
