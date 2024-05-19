#include <SFML/Graphics.hpp>
#include "sniper.hpp"
#include "Tank.hpp"
#include "Course.hpp"
#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"
#include "affichage.hpp"
#include "Init.hpp"
int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Robot and Hexagon Arena");
    sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

	bool running = true;
    while (running) {
        // Afficher le menu principal
        Init debut;
        int nbplay = 0;
        Robot* rob1 = nullptr;
        Robot* rob2 = nullptr;
        char* player1 = nullptr;
        char* player2 = nullptr;

        while (debut.menu(window, &nbplay)) {}

        if (debut.name(window, player1, player2)) {
            if (!debut.fin) {
                int res[2];
                if (debut.choose(window, res)) {
                    if ((res[0] == 0) || (res[1] == 0)) {
                        continue; // Retourner au menu si une option invalide est choisie
                    }
                    Hexagone hexagon(window.getSize().x, window.getSize().y);

                    if (res[0] == 1) rob1 = new Sniper(hexagon, 600 , window.getSize().y / 2, 'A', sf::Color::Red);
                    if (res[0] == 2) rob1 = new Tank(hexagon, 600, window.getSize().y / 2, 'A', sf::Color::Red);
                    if (res[0] == 3) rob1 = new Course(hexagon,600 , window.getSize().y / 2, 'A', sf::Color::Red);
                    if (res[1] == 1) rob2 = new Sniper(hexagon, 1200, window.getSize().y / 2, 'B', sf::Color::Blue);
                    if (res[1] == 2) rob2 = new Tank(hexagon, 1200, window.getSize().y / 2, 'B', sf::Color::Blue);
                    if (res[1] == 3) rob2 = new Course(hexagon,1200 , window.getSize().y / 2, 'B', sf::Color::Blue);

                    if (!rob1 || !rob2) {
                        if (!rob1) {
                            std::cerr << "Erreur lors de l'initialisation de rob 1" << std::endl;
                        }
                        if (!rob2) {
                            std::cerr << "Erreur lors de l'initialisation de rob 2" << std::endl;
                        }
                        return 1;
                    }

                    rob1->set_name(player1, font);
                    rob2->set_name(player2, font);
					rob2->set_Orientation(rob2->get_Orientation()+3.1415);

                    Affiche aff(hexagon, *rob1, *rob2);
                    aff.set_nbPlayers(nbplay);

                    sf::Clock clock;
                    const sf::Time timePerMove = sf::milliseconds(50);
                    sf::Event event;

                    while (!aff.refresh(window, timePerMove, clock, event)) {
                        aff.updateControls(*rob1);
                        if (aff.getNbPlayers() == 2) {
                            aff.updateControls(*rob2);
                        }
                        rob1->updateProjectiles(window, *rob2);
                        rob2->updateProjectiles(window, *rob2);
                    }

                    delete rob1;
                    delete rob2;
                    rob1 = nullptr;
                    rob2 = nullptr;
                }
            }
        }

        // Réinitialiser les valeurs pour la prochaine itération
        delete rob1;
        delete rob2;
        rob1 = nullptr;
        rob2 = nullptr;
        player1 = nullptr;
        player2 = nullptr;

		// Vérifier si la fenêtre a été fermée
        if (!window.isOpen()) {
            running = false;
        }
    }

    return 0;
}


