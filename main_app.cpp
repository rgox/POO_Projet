//On inclu SFML et les classes nécessaires au bon déroulement de notre jeu
#include <SFML/Graphics.hpp>
#include "Sniper.hpp"
#include "Tank.hpp"
#include "Course.hpp"
#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"
#include "affichage.hpp"
#include "Init.hpp"


int main() {
	//Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Robot and Hexagon Arena");

	//On crée la police d'écriture qui nous plaît pour notre jeu
    sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

	//On crée un booléen qui nous permet de mesurer si le jeu est encore actif
	bool running = true;
    while (running) {
        // On crée le menu initial 
        Init debut;
        int nbplay = 0;//On initialise le nombre de joueurs à 0

		//On crée deux pointeurs vers les classes robots qui seront initialisés plus tard
        Robot* rob1 = nullptr;
        Robot* rob2 = nullptr;

		//On crée nos chaînes de caracthères permettant de stocker les deux prénoms de nos joueurs
        char* player1 = nullptr;
        char* player2 = nullptr;

		//On affiche le menu de démarrage permettant de savoir si l'utilisateur veut joueur tout seul ou en multijoueur
        while (debut.menu(window, &nbplay)) {}

		//On affiche un menu permettant d'initialiser les prénoms de nos deux joueurs
        if (debut.name(window, player1, player2)) {

			//On test si le jeu a pris fin ou pas à cause d'une erreur de chargement ou du fait que l'utilisateur a fermé la fenêtre
            if (!debut.fin) {
                int res[2];//Variable stockant les choix de personnage des joueurs

				//Menu où les joueurs choississent leur personnage
                if (debut.choose(window, res)) {
                    if ((res[0] == 0) || (res[1] == 0)) { //On teste s'il y a eu une erreur
                        continue; // Retourner au menu si une option invalide est choisie
                    }

					//On initialise l'arène
                    Arene hexagon(window.getSize().x, window.getSize().y);

					//On initilise les joueurs
                    if (res[0] == 1) rob1 = new Sniper(hexagon, 600 , window.getSize().y / 2, 'B', sf::Color::Red);
                    if (res[0] == 2) rob1 = new Tank(hexagon, 600, window.getSize().y / 2, 'B', sf::Color::Red);
                    if (res[0] == 3) rob1 = new Course(hexagon,600 , window.getSize().y / 2, 'B', sf::Color::Red);
                    if (res[1] == 1) rob2 = new Sniper(hexagon, 1200, window.getSize().y / 2, 'A', sf::Color::Blue);
                    if (res[1] == 2) rob2 = new Tank(hexagon, 1200, window.getSize().y / 2, 'A', sf::Color::Blue);
                    if (res[1] == 3) rob2 = new Course(hexagon,1200 , window.getSize().y / 2, 'A', sf::Color::Blue);

					//On vérifie qu'ils ont bien été initialisés
                    if (!rob1 || !rob2) {
                        if (!rob1) {
                            std::cerr << "Erreur lors de l'initialisation de rob 1" << std::endl;
                        }
                        if (!rob2) {
                            std::cerr << "Erreur lors de l'initialisation de rob 2" << std::endl;
                        }
                        return 1;
						}

					//On set le prénom des joueurs
                    rob1->set_name(player1, font);
                    rob2->set_name(player2, font);

					//On oriente la deuxième voiture face à la première 
					rob2->set_Orientation(rob2->get_Orientation()+3.1415);

					//On initialise la classe Affichage qui permet de regrouper els différentes classes afin d'assurer le bon déroulement du jeu
                    Affiche aff(hexagon, *rob1, *rob2);
                    aff.set_nbPlayers(nbplay);

					//On initialise le timer qui nous permet de refresh la fenêtre
                    sf::Clock clock;

					//On définit le temps par mouvement
                    const sf::Time timePerMove = sf::milliseconds(50);

					//On initialise un evenement SFML qui nous permet de traiter ce qu'il se passe sur l'écran
                    sf::Event event;

					//On lance la fonction refresh qui lance le jeu 
                    while (!aff.refresh(window, timePerMove, clock, event)) {
						//On met à jour la position et les projectiles de chaque personnage
                        aff.updateControls(*rob1);
                        if (aff.getNbPlayers() == 2) {
                            aff.updateControls(*rob2);
                        }
                        rob1->handleCollision(window, *rob2);
                        rob2->handleCollision(window, *rob2);
                    }

					//On effece les robots créés
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
			// Libérez la mémoire avant de quitter le programme
			free(rob1);
			free(rob2);
			free(player1);
			free(player2);
        }
    }

    return 0;
}


