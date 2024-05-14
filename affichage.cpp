#include "affichage.hpp"
#include <iomanip> // Inclure la bibliothèque pour std::setprecision
#include <sstream> // Inclure la bibliothèque pour std::ostringstream

bool Affiche::menu(sf::RenderWindow& window) {
	
    sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        // Gestion de l'erreur si le chargement de la police échoue
        return false;
    }
	
    sf::Text title;
    title.setFont(font);
    title.setString("RobotVroomVromm");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::White);
	title.setPosition(window.getSize().x/2-300,200);
	sf::Text clonetitle(title);
	clonetitle.setPosition(window.getSize().x/2-300,window.getSize().y-350);

    sf::Text singlePlayerOption;
    singlePlayerOption.setFont(font);
    singlePlayerOption.setString("Jouer tout seul");
    singlePlayerOption.setCharacterSize(20);
    singlePlayerOption.setFillColor(sf::Color::White);
    singlePlayerOption.setPosition(window.getSize().x/2-50, window.getSize().y/2-100);

    sf::Text multiPlayerOption;
    multiPlayerOption.setFont(font);
    multiPlayerOption.setString("Jouer a deux joueurs");
    multiPlayerOption.setCharacterSize(20);
    multiPlayerOption.setFillColor(sf::Color::White);
    multiPlayerOption.setPosition(window.getSize().x/2-75, window.getSize().y/2-50);

    sf::Text goButton;
    goButton.setFont(font);
    goButton.setString("Go !");
    goButton.setCharacterSize(25);
    goButton.setFillColor(sf::Color::White);
    goButton.setPosition(window.getSize().x/2, window.getSize().y/2+20);

	// Rectangle vert pour encadrer l'option sélectionnée
    sf::RectangleShape selectionRect(sf::Vector2f(singlePlayerOption.getLocalBounds().width + 60, singlePlayerOption.getLocalBounds().height + 20));
    selectionRect.setFillColor(sf::Color::Transparent);
    selectionRect.setOutlineThickness(2);
    selectionRect.setOutlineColor(sf::Color::Green);
    selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, 5)); // Déplacer le rectangle autour de l'option sélectionnée

	//Indicateur 
	sf::Texture texture1;
    if (!texture1.loadFromFile("Indicateur.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        return EXIT_FAILURE;
    }
	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
	sprite1.setScale(0.1, 0.1);
	sprite1.setPosition(singlePlayerOption.getPosition() + sf::Vector2f(200, 5));

	//Background
	// Chargement des images de la séquence vidéo
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= 50; ++i) { // Suppose que vous avez 100 images dans votre séquence
        sf::Texture texture2;
		std::string filename = "background1/background1_out00" + std::to_string(i) + ".png"; // Nom de fichier de l'image
		
		if(i<10){
			filename = "background1/background1_out000" + std::to_string(i) + ".png"; // Nom de fichier de l'image
		}
        if (!texture2.loadFromFile(filename)) {
            // Gestion de l'erreur si le chargement de l'image échoue
            return EXIT_FAILURE;
        }
        frames.push_back(texture2);
    }
	// Création du sprite pour afficher les images
    sf::Sprite sprite;

    // Boucle de lecture des images
    int currentFrame = 0;
	sf::Clock clock;

    // Boucle principale du menu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
				fin=true;
                return false; // Retourne false si la fenêtre est fermée
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (singlePlayerOption.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode un joueur
                    // Exemple : initialiser un seul robot
                    nbPlayers=1;
					selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, 5)); 
					sprite1.setPosition(singlePlayerOption.getPosition() + sf::Vector2f(200, 5));
                } else if (multiPlayerOption.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode deux joueurs
                    // Exemple : initialiser deux robots
                    nbPlayers=2;
					selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, -45));
            		sprite1.setPosition(singlePlayerOption.getPosition() + sf::Vector2f(200, 45));
                } else if (goButton.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour lancer le jeu après avoir choisi le mode de jeu
                    return false; // Retourne true pour démarrer le jeu
                }
            }
			
		
        }
		// Affichage de l'image actuelle
        sprite.setTexture(frames[currentFrame]);
		sprite.setScale((window.getSize().x)/480,(window.getSize().y)/300);

		// Avancer au prochain frame toutes les 100 millisecondes (10 images par seconde)
        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            currentFrame = (currentFrame + 1) % frames.size();
            clock.restart();
        } 	  
        

        window.display();
        window.clear();
		window.draw(sprite);
        window.draw(title);
		window.draw(clonetitle);
		window.draw(selectionRect);
		window.draw(sprite1);
        window.draw(singlePlayerOption);
        window.draw(multiPlayerOption);
        window.draw(goButton);
        window.display();
    }
	
    return false; // Retourne false par défaut
}


bool Affiche::refresh(sf::RenderWindow& window, sf::Time timePerMove, sf::Clock& clock, sf::Event& event) {
    // Effacement de la fenêtre
    window.clear();

		//######## Infos des joueurs ##########

		sf::Font font;
		if (!font.loadFromFile("Ecriture.ttf")) {
			// Gestion de l'erreur si le chargement de la police échoue
			return false;
		}
		//Joueur P1
		sf::Text NomP1;
    	NomP1.setFont(font);
		NomP1.setString("Enbrrr");
		NomP1.setCharacterSize(70);
		NomP1.setFillColor(sf::Color::Black);
		NomP1.setPosition(100, 10);

		sf::Text VieP1;
    	VieP1.setFont(font);
		VieP1.setString( std::to_string(P1.getHealth()) );
		VieP1.setCharacterSize(50);
		VieP1.setFillColor(sf::Color::Black);
		VieP1.setPosition(100, 80);

		sf::Text SpeedP1;
    	SpeedP1.setFont(font);
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << P1.getSpeed(); // Limite à 2 chiffres après la virgule
		SpeedP1.setString(oss.str());
		SpeedP1.setCharacterSize(50);
		SpeedP1.setFillColor(sf::Color::Black);
		SpeedP1.setPosition(100, 140);


		//Joueur P2
		sf::Text NomP2;
    	NomP2.setFont(font);
		NomP2.setString("Hassoul");
		NomP2.setCharacterSize(70);
		NomP2.setFillColor(sf::Color::Black);
		NomP2.setPosition(window.getSize().x-400, 10);

		sf::Text VieP2;
    	VieP2.setFont(font);
		VieP2.setString(std::to_string(P2.getHealth()));
		VieP2.setCharacterSize(50);
		VieP2.setFillColor(sf::Color::Black);
		VieP2.setPosition(window.getSize().x-400, 80);

		sf::Text SpeedP2;
    	SpeedP2.setFont(font);
		oss.str("");
		oss << std::fixed << std::setprecision(2) << P2.getSpeed(); // Limite à 2 chiffres après la virgule
		SpeedP2.setString(oss.str());
		SpeedP2.setCharacterSize(50);
		SpeedP2.setFillColor(sf::Color::Black);
		SpeedP2.setPosition(window.getSize().x-400, 140);

		//Petit coeur
		sf::Texture texture3;
		if (!texture3.loadFromFile("life.png") ) {
			// Gestion de l'erreur si le chargement de la texture échoue
			return EXIT_FAILURE;
		}
		sf::Sprite sprite3;
		sprite3.setTexture(texture3);
		sf::IntRect textureRect(0, 0, 120, 100); 
    	sprite3.setTextureRect(textureRect);
		sprite3.setScale(0.6,0.6);
		sf::Sprite cloneSprite3(sprite3);
		sprite3.setPosition(VieP1.getPosition() + sf::Vector2f(60, 0));
		cloneSprite3.setPosition(VieP2.getPosition() + sf::Vector2f(60, 0));

		//Petit logo de vitesse
		sf::Texture texture4;
		if (!texture4.loadFromFile("speed.png") ) {
			// Gestion de l'erreur si le chargement de la texture échoue
			return EXIT_FAILURE;
		}
		sf::Sprite sprite4;
		sprite4.setTexture(texture4);
		sprite4.setScale(0.12,0.12);
		sf::Sprite cloneSprite4(sprite4);
		sprite4.setPosition(SpeedP1.getPosition() + sf::Vector2f(110, 5));
		cloneSprite4.setPosition(SpeedP2.getPosition() + sf::Vector2f(110, 5));


		//######## Barres de Vie ##########

		sf::Texture texture;
		if (!texture.loadFromFile("batterie.png") ) {
			// Gestion de l'erreur si le chargement de la texture échoue
			return EXIT_FAILURE;
		}
		sf::Sprite sprite1;
		sprite1.setTexture(texture);
		sprite1.setScale(0.15, 0.2);
		sf::Sprite cloneSprite1(sprite1);
		sprite1.setPosition(3,10);
		cloneSprite1.setPosition(window.getSize().x-100,10);
		// Créer un rectangle shape
    	sf::RectangleShape batterie1(sf::Vector2f(150, 150)); // Définir la taille du carré (largeur x hauteur)
    
    	// Définir la position du carré
		batterie1.setPosition(5, 35); // Coordonnées x et y du coin supérieur gauche du carré
		
		// Définir la couleur du carré
		batterie1.setFillColor(sf::Color::Green); // Choisir une couleur, ici bleu

		// Créer un rectangle shape
    	sf::RectangleShape batterie2(sf::Vector2f(35, 85)); // Définir la taille du carré (largeur x hauteur)
    
    // Définir la position deu carré
		batterie2.setPosition(window.getSize().x-100, 35); // Coordonnées x et y du coin supérieur gauche du carré
		
		// Définir la couleur du carré
		batterie2.setFillColor(sf::Color::Green); // Choisir une couleur, ici verte



		
//################################################################################################################

    
    while (window.isOpen()) {
        // Gestion des événements
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Mettre à jour les mouvements des robots seulement quand l'intervalle de temps est atteint
        if (clock.getElapsedTime() >= timePerMove) {
            if (nbPlayers == 2) {
                P1.update(window);
                P2.update(window);

                // Vérification des collisions entre les robots
                P1.handleCollision(P2);
                P2.handleCollision(P1);

				//#####Adaptation des barres de vie en fonction des hp des joueurs########
				batterie1.setSize(sf::Vector2f(80, 160-(100-P1.getHealth())));
				batterie1.setPosition(5,35+(100-P1.getHealth()));

				batterie2.setSize(sf::Vector2f(80, 160-(100-P2.getHealth())));
				batterie2.setPosition(window.getSize().x-95,35+(100-P2.getHealth()));

				VieP1.setString(std::to_string(P1.getHealth()));
				VieP2.setString(std::to_string(P2.getHealth()));

				oss.str("");
				oss << std::fixed << std::setprecision(2) << P1.getSpeed(); // Limite à 2 chiffres après la virgule
				SpeedP1.setString(oss.str());

				oss.str("");
				oss << std::fixed << std::setprecision(2) << P2.getSpeed(); // Limite à 2 chiffres après la virgule
				SpeedP2.setString(oss.str());
						
            } else {
                P1.update(window);

                // Vérification des collisions entre les robots
                P1.handleCollision(P2);

				batterie1.setSize(sf::Vector2f(80, 160-(100-P1.getHealth())));
				batterie1.setPosition(5,35+(100-P1.getHealth()));

				batterie2.setSize(sf::Vector2f(80, 160-(100-P2.getHealth())));
				batterie2.setPosition(window.getSize().x-95,35+(100-P2.getHealth()));

				VieP1.setString(std::to_string(P1.getHealth()));

				oss.str("");
				oss << std::fixed << std::setprecision(2) << P1.getSpeed(); // Limite à 2 chiffres après la virgule
				SpeedP1.setString(oss.str());
            }
            clock.restart();  // Redémarrer l'horloge après chaque mise à jour
        }
		// Définir le rectangle source dans la texture de l'image
		
		
		
		
		window.clear(sf::Color::White);
		
        hexagon.drawHexagon(window, sf::Color::Red); 
        P1.draw(window);  // Dessiner le premier robot
		if(nbPlayers==2) P2.draw(window);  // Dessiner le deuxième robot
		window.draw(batterie1);
        window.draw(sprite1);

		window.draw(batterie2);

		window.draw(cloneSprite1);
		
		window.draw(NomP1);
		window.draw(NomP2);

		window.draw(VieP1);
		window.draw(VieP2);
		window.draw(sprite3);
		window.draw(cloneSprite3);

		window.draw(SpeedP1);
		window.draw(SpeedP2);
		window.draw(sprite4);
		window.draw(cloneSprite4);
		window.display();
		
		}

	return false	  ;
}

void Affiche::updateControls(Robot& robot) {
    if (robot.getControlScheme() == 'A') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) robot.moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) robot.moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) robot.rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) robot.rotateRight();
    } else if (robot.getControlScheme() == 'B') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) robot.moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) robot.moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) robot.rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) robot.rotateRight();
    }
}