#include <SFML/Graphics.hpp>

int main()
{
    // Tworzenie okna o rozmiarze 800x600
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Działa!");

    // Tworzenie kółka o promieniu 50
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green); // Ustawienie koloru kółka na zielony

    // Ustawienie pozycji kółka na środku okna
    shape.setPosition(400 - 50, 300 - 50);

    // Główna pętla programu
    while (window.isOpen())
    {
        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Czyszczenie okna
        window.clear();

        // Rysowanie kółka
        window.draw(shape);

        // Wyświetlenie zawartości okna
        window.display();
    }

    return 0;
}