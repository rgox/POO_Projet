#include <SFML/Graphics.hpp>
#include "Robot.hpp"
#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(100);  // Définir l'intervalle de mise à jour

    // Configuration initiale
    sf::RenderWindow window(sf::VideoMode(800, 600), "Robot and Hexagon Arena");
    Hexagone hexagon(window.getSize().x, window.getSize().y);

	// Appliquez un décalage vers le centre pour chaque robot
	sf::Vector2f pos1 = hexagon.getPoint(0);
	sf::Vector2f pos3 = hexagon.getPoint(3);



    Robot robot1(hexagon, pos1.x - robot1.getWidth()/2, pos1.y - robot1.getHeight()/2, 100, 5, 20, 10, 'A', sf::Color::Red);
	robot1.setPosition(400,300);
    Robot robot2(hexagon, pos3.x, pos3.y, 100, 5, 15, 10, 'B', sf::Color::Blue);
	robot2.setPosition(200,300);

	std::cout << "Hexagon Point 0: (" << pos1.x << ", " << pos1.y << ")" << std::endl;
	std::cout << "Robot 1 Position: (" << robot1.getX() << ", " << robot1.getY() << ")" << std::endl;

	Bonus bonus(hexagon);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (clock.getElapsedTime() >= timePerMove) {
            // Mettre à jour les mouvements des robots seulement quand l'intervalle de temps est atteint
            robot1.update(window);
            robot2.update(window);

            // Vérification des collisions entre les robots
            robot1.handleCollision(robot2);
            robot2.handleCollision(robot1);

            clock.restart();  // Redémarrer l'horloge après chaque mise à jour
        }

        window.clear(sf::Color::White);
        hexagon.drawHexagon(window, sf::Color::Green); 
		bonus.drawBonus(window); // Dessiner l'hexagone
        robot1.draw(window);  // Dessiner le premier robot
        robot2.draw(window);  // Dessiner le deuxième robot

		// Draw debugging visuals
		robot1.drawDebug(window);
		robot2.drawDebug(window);


        window.display();

		
    }

    return 0;
}
