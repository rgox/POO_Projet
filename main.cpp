#include <SFML/Graphics.hpp>
#include "sniper.hpp"
#include "Tank.hpp"

#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"
#include "affichage.hpp"


int main() {
    sf::Event event;
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(50);
    Hexagone hexagon(window.getSize().x, window.getSize().y);
    Affiche aff(hexagon);

    while (aff.menu(window)) {}

    if (!aff.fin) {
        int voit = aff.choose(window);
        Robot* rob1 = nullptr;
        Robot* rob2 = nullptr;

        switch (voit / 10) {
            case 0:
                rob2 = new Sniper(hexagon, 600, 450, 'A', sf::Color::Blue);
                break;
            case 1:
                rob2 = new Tank(hexagon, 600, 450, 'A', sf::Color::Blue);
                break;
            case 2:
                rob2 = new Course(hexagon, 600, 450, 'A', sf::Color::Blue);
                break;
        }

        switch (voit % 10) {
            case 1:
                rob1 = new Sniper(hexagon, 400, 450, 'B', sf::Color::Blue);
                break;
            case 2:
                rob1 = new Tank(hexagon, 400, 450, 'B', sf::Color::Blue);
                break;
            case 3:
                rob1 = new Course(hexagon, 400, 450, 'B', sf::Color::Blue);
                break;
        }

        if (rob1 && rob2) {
            while (aff.refresh(window, timePerMove, clock, event, *rob1, *rob2)) {
                aff.updateControls(*rob1, *rob2);
            }
        }

        delete rob1;
        delete rob2;
    }

    return 0;
}
