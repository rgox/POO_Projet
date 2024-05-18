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
    const sf::Time timePerMove = sf::milliseconds(50);  // Définir l'intervalle de mise à jour
	Hexagone hexagon(window.getSize().x, window.getSize().y);
    /// Appliquez un décalage vers le centre pour chaque robot
	sf::Vector2f pos1 = hexagon.getPoint(0);
	sf::Vector2f pos3 = hexagon.getPoint(3);

    Sniper snip(hexagon, pos1.x - 20, pos1.y - 15,  'A', sf::Color::Red);
	snip.setPosition(640,540);
    Tank robot2(hexagon, pos3.x - 20, pos3.y - 15,  'B', sf::Color::Blue);
	robot2.setPosition(1280,540);
    Affiche aff(hexagon, snip, robot2);
    while (aff.menu(window)) {}

    if (!aff.fin) {
        while (aff.refresh(window, timePerMove, clock, event)) {
            aff.updateControls(snip);
            if (aff.getNbPlayers() == 2) {
                aff.updateControls(robot2);
            }
            snip.update(window, robot2);
            if (aff.getNbPlayers() == 2) {
                robot2.update(window, snip);
            }
        }
    }

    return 0;
}
