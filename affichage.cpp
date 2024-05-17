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
    title.setPosition(180, 50);

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


bool Affiche::refresh(sf::RenderWindow& window, sf::Time timePerMove, sf::Clock& clock, sf::Event& event,Robot& P1, Robot& P2) {
    	// Effacement de la fenêtre
    	window.clear();

		//######## Infos des joueurs ##########
		std::cout << hexagon.getPoint(0).x << "Début refresh" <<std::endl;
		sf::Font font;
		if (!font.loadFromFile("Ecriture.ttf")) {
			// Gestion de l'erreur si le chargement de la police échoue
			return false;
		}
		//Joueur P1

		P1.setPosition(window.getSize().x/2-100,window.getSize().y/2);
		P2.setPosition(window.getSize().x/2+100,window.getSize().y/2);

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

		sf::Text DefenseP1;
    	DefenseP1.setFont(font);
		DefenseP1.setString( std::to_string(P1.getDefense()) );
		DefenseP1.setCharacterSize(50);
		DefenseP1.setFillColor(sf::Color::Black);
		DefenseP1.setPosition(100, 200);


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

		sf::Text DefenseP2;
    	DefenseP2.setFont(font);
		DefenseP2.setString( std::to_string(P2.getDefense()) );
		DefenseP2.setCharacterSize(50);
		DefenseP2.setFillColor(sf::Color::Black);
		DefenseP2.setPosition(window.getSize().x-400, 200);

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
		sprite3.setPosition(VieP1.getPosition() + sf::Vector2f(80, 0));
		cloneSprite3.setPosition(VieP2.getPosition() + sf::Vector2f(80, 0));

		//Petit shield
		sf::Texture texture5;
		if (!texture5.loadFromFile("shield.png") ) {
			// Gestion de l'erreur si le chargement de la texture échoue
			return EXIT_FAILURE;
		}
		sf::Sprite sprite5;
		sprite5.setTexture(texture5);
		sprite5.setScale(0.025,0.025);
		sf::Sprite cloneSprite5(sprite5);
		sprite5.setPosition(DefenseP1.getPosition() + sf::Vector2f(80, 0));
		cloneSprite5.setPosition(DefenseP2.getPosition() + sf::Vector2f(80, 0));


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
		sprite4.setPosition(SpeedP1.getPosition() + sf::Vector2f(140, 10));
		cloneSprite4.setPosition(SpeedP2.getPosition() + sf::Vector2f(140, 10));


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

	int initialHealth1=P1.getHealth();
	int initialHealth2=P2.getHealth();

		
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
				batterie1.setSize(sf::Vector2f(80, 160-(100-P1.getHealth()/initialHealth1*100)));
				batterie1.setPosition(5,35+(100-P1.getHealth()/initialHealth1*100));

				batterie2.setSize(sf::Vector2f(80, 160-(100-P2.getHealth()/initialHealth2*100)));
				batterie2.setPosition(window.getSize().x-95,35+(100-P2.getHealth()/initialHealth2*100));

				VieP1.setString(std::to_string(P1.getHealth()));
				VieP2.setString(std::to_string(P2.getHealth()));

				DefenseP1.setString( std::to_string(P1.getDefense()) );
				DefenseP2.setString( std::to_string(P2.getDefense()) );

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

				batterie2.setSize(sf::Vector2f(80, 160-(100-P2.getHealth()/initialHealth2*100)));
				batterie2.setPosition(window.getSize().x-95,35+(100-P2.getHealth()/initialHealth2*100));

				VieP1.setString(std::to_string(P1.getHealth()));

				DefenseP1.setString( std::to_string(P1.getDefense()) );
				DefenseP2.setString( std::to_string(P2.getDefense()) );

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
		window.draw(DefenseP1);
		window.draw(DefenseP2);
		window.draw(SpeedP1);
		window.draw(SpeedP2);
		window.draw(sprite4);
		window.draw(cloneSprite4);
		window.draw(sprite5);
		window.draw(cloneSprite5);
		window.display();
		std::cout << hexagon.getPoint(0).x << "Fin refresh"<< std::endl;
		}

	return false	  ;
}

void Affiche::updateControls(Robot& P1, Robot& P2) {
	std::cout << hexagon.getPoint(0).x << "controle"<<std::endl;
    if (P1.getControlScheme() == 'A') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) P1.moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) P1.moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) P1.rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) P1.rotateRight();
    } else if (P1.getControlScheme() == 'B') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) P1.moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) P1.moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) P1.rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) P1.rotateRight();
    }
	if (nbPlayers == 2) {
            if (P2.getControlScheme() == 'A') {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) P2.moveForward();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) P2.moveBackward();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) P2.rotateLeft();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) P2.rotateRight();
			} else if (P2.getControlScheme() == 'B') {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) P2.moveForward();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) P2.moveBackward();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) P2.rotateLeft();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) P2.rotateRight();
    } 
            }
}

int Affiche::choose(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        // Gestion de l'erreur si le chargement de la police échoue
        return false;
    }
    
    sf::Text title;
    title.setFont(font);
    title.setString("Choose your player");
    title.setCharacterSize(70);
    title.setFillColor(sf::Color::White);
    title.setPosition(window.getSize().x / 2 - 300, 200);
    sf::Text clonetitle(title);
    clonetitle.setPosition(window.getSize().x / 2 - 300, window.getSize().y - 350);

    sf::Text Player1;
    Player1.setFont(font);
    Player1.setString("Player 1");
    Player1.setCharacterSize(20);
    Player1.setFillColor(sf::Color::White);
    Player1.setPosition(window.getSize().x / 2 - 250, window.getSize().y / 2 - 100);

    sf::Text Player2;
    Player2.setFont(font);
    Player2.setString("Player 2");
    Player2.setCharacterSize(20);
    Player2.setFillColor(sf::Color::White);
    Player2.setPosition(window.getSize().x / 2 + 250, window.getSize().y / 2 - 100);

    sf::Text goButton;
    goButton.setFont(font);
    goButton.setString("Go !");
    goButton.setCharacterSize(25);
    goButton.setFillColor(sf::Color::White);
    goButton.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 20);
    
    sf::Texture textLeftButton, textRightButton;
    if (!textLeftButton.loadFromFile("flatDark23.png") || !textRightButton.loadFromFile("flatDark24.png")) {
        // Gestion de l'erreur si le chargement de la texture échoue
        return EXIT_FAILURE;
    }
    
    sf::Sprite LeftButton1(textLeftButton), LeftButton2(textLeftButton), RightButton1(textRightButton), RightButton2(textRightButton);
    LeftButton1.setScale(1, 1);
    LeftButton1.setPosition(window.getSize().x / 2 - 350, window.getSize().y / 2);
    LeftButton2.setScale(1, 1);
    LeftButton2.setPosition(window.getSize().x / 2 + 150, window.getSize().y / 2);
    RightButton1.setScale(1, 1);
    RightButton1.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2);
    RightButton2.setScale(1, 1);
    RightButton2.setPosition(window.getSize().x / 2 + 350, window.getSize().y / 2);

    // Chargement des images de fond
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= 50; ++i) {
        sf::Texture texture2;
        std::string filename = "background1/background1_out00" + std::to_string(i) + ".png";
        if (i < 10) filename = "background1/background1_out000" + std::to_string(i) + ".png";
        if (!texture2.loadFromFile(filename)) return EXIT_FAILURE;
        frames.push_back(texture2);
    }

    sf::Sprite sprite;
    int currentFrame = 0;
    sf::Clock clock;

    // Variables de sélection initialisées à 0
    int n = 0, n1 = 0, res = 0;
    Sniper snip1(hexagon, window.getSize().x / 2 - 250, window.getSize().y / 2, 'A', sf::Color::White);
    Sniper snip2(hexagon, window.getSize().x / 2 + 250, window.getSize().y / 2, 'A', sf::Color::White);
    Tank tank1(hexagon, window.getSize().x / 2 - 250, window.getSize().y / 2, 'A', sf::Color::White);
    Tank tank2(hexagon, window.getSize().x / 2 + 250, window.getSize().y / 2, 'A', sf::Color::White);
    Course course1(hexagon, window.getSize().x / 2 - 250, window.getSize().y / 2, 'A', sf::Color::White);
    Course course2(hexagon, window.getSize().x / 2 + 250, window.getSize().y / 2, 'A', sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                fin = true;
                return 0;
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (RightButton1.getGlobalBounds().contains(mousePosition)) {
                    n = (n + 1) % 3;
                } else if (LeftButton1.getGlobalBounds().contains(mousePosition)) {
                    n = (n - 1 + 3) % 3;
                } else if (RightButton2.getGlobalBounds().contains(mousePosition)) {
                    n1 = (n1 + 1) % 3;
                } else if (LeftButton2.getGlobalBounds().contains(mousePosition)) {
                    n1 = (n1 - 1 + 3) % 3;
                } else if (goButton.getGlobalBounds().contains(mousePosition)) {
                    res = (n * 10) + (n1 + 1);
                    return res;
                }
            }
        }

        window.clear();
        sprite.setTexture(frames[currentFrame]);
        sprite.setScale((window.getSize().x) / 480, (window.getSize().y) / 300);
        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            currentFrame = (currentFrame + 1) % frames.size();
            clock.restart();
        }

        window.draw(sprite);
        window.draw(title);
        window.draw(clonetitle);
        window.draw(Player1);
        window.draw(LeftButton1);
        window.draw(LeftButton2);
        window.draw(RightButton1);
        window.draw(RightButton2);
        window.draw(Player2);
        window.draw(goButton);

        if (n == 0) snip1.draw(window);
        else if (n == 1) tank1.draw(window);
        else course1.draw(window);

        if (n1 == 0) snip2.draw(window);
        else if (n1 == 1) tank2.draw(window);
        else course2.draw(window);

        window.display();
    }

    return 0;
}
