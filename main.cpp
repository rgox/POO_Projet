#include <SFML/Graphics.hpp>
#include "Robot.hpp"
#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"
#include "affichage.hpp"


int main() {
	sf::Event event;
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(200);  // Définir l'intervalle de mise à jour
	Hexagone hexagon(window.getSize().x, window.getSize().y);
    /// Appliquez un décalage vers le centre pour chaque robot
	sf::Vector2f pos1 = hexagon.getPoint(0);
	sf::Vector2f pos3 = hexagon.getPoint(3);

    Robot robot1(hexagon, pos1.x - 20, pos1.y - 15, 100, 5, 20, 10, 'A', sf::Color::Red);
	robot1.setPosition(200,350);
    Robot robot2(hexagon, pos3.x - 20, pos3.y - 15, 100, 5, 15, 10, 'B', sf::Color::Blue);
	robot2.setPosition(600,350);
    Affiche aff(hexagon, robot1, robot2);
    while (!aff.menu(window)) {}

    if (!aff.fin) {
        while (aff.refresh(window, timePerMove, clock, event)) {
            aff.updateControls(robot1);
            if (aff.getNbPlayers() == 2) {
                aff.updateControls(robot2);
            }
        }
    }

    return 0;
}
