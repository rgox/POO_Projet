#include "affichage.hpp"
#include <iomanip> // Inclure la bibliothèque pour std::setprecision
#include <sstream> // Inclure la bibliothèque pour std::ostringstream



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
		
		
		P1.get_name().setCharacterSize(70);
		
		P1.get_name().setFillColor(sf::Color::Black);
		P1.setNamePosition(100, 10);
		
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
		P2.get_name().setFont(font);
		P2.get_name().setCharacterSize(70);
		P2.get_name().setFillColor(sf::Color::Black);
		P2.setNamePosition(window.getSize().x-400, 10);
		
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
P1.update(window,P2);
P2.update(window,P1);

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
P1.update(window,P2);

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
clock.restart(); // Redémarrer l'horloge après chaque mise à jour
}

        // Apparition aléatoire des bonus
        if (bonuses.size() < 3 && rand() % 100 < 0.001) { // Ajustez la probabilité d'apparition des bonus
            bonuses.push_back(Bonus(hexagon,window));
        }

        // Gestion des collisions des robots avec les bonus
        for (auto it = bonuses.begin(); it != bonuses.end(); ) {
            if (P1.get_Shape().getGlobalBounds().intersects(it->getCircleShape().getGlobalBounds()) ||
                P1.get_Shape().getGlobalBounds().intersects(it->getRectangleShape().getGlobalBounds()) ||
                P1.get_Shape().getGlobalBounds().intersects(it->getTriangleShape().getGlobalBounds())) {
                // Appliquer le bonus au robot P1
                if (it->getBonusType() == 1) {
                    P1.setHealth(P1.getHealth() + 10);
                }
				if (it->getBonusType() == 2) {
                    P1.setSpeed(P1.getSpeed() + 5);
                }
				if (it->getBonusType() == 3) {
                    P1.setDefense(P1.getDefense() + 10);
                }
                // Ajoutez d'autres types de bonus ici
                it = bonuses.erase(it); // Supprimer le bonus une fois collecté
            } else if (nbPlayers == 2 &&
                (P2.get_Shape().getGlobalBounds().intersects(it->getCircleShape().getGlobalBounds()) ||
                P2.get_Shape().getGlobalBounds().intersects(it->getRectangleShape().getGlobalBounds()) ||
                P2.get_Shape().getGlobalBounds().intersects(it->getTriangleShape().getGlobalBounds()))) {
                // Appliquer le bonus au robot P2
                if (it->getBonusType() == 1) {
                    P2.setHealth(P2.getHealth() + 10);
                }
				if (it->getBonusType() == 2) {
                    P2.setSpeed(P2.getSpeed() + 5);
                }
				if (it->getBonusType() == 3) {
                    P2.setDefense(P2.getDefense() + 10);
                }
                // Ajoutez d'autres types de bonus ici
                it = bonuses.erase(it); // Supprimer le bonus une fois collecté
            } else {
                ++it;
            }
        }

        // Effacement de la fenêtre
        window.clear(sf::Color::White);

        // Dessiner tout ce qui doit être affiché
        hexagon.drawHexagon(window, sf::Color::Red);
        P1.draw(window); // Dessiner le premier robot
        if (nbPlayers == 2) P2.draw(window); // Dessiner le deuxième robot

        // Dessiner les bonus
        for (const auto& bonus : bonuses) {
            bonus.drawBonus(window);
        }

		window.draw(batterie1);
        window.draw(sprite1);

		window.draw(batterie2);

		window.draw(cloneSprite1);
		
			
		window.draw(P1.get_name_draw());
		window.draw(P2.get_name_draw());

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
		
		// Dessiner les projectiles
        for (auto& projectile : P1.getProjectiles()) {
            projectile.draw(window);
        }
        if (nbPlayers == 2) {
            for (auto& projectile : P2.getProjectiles()) {
                projectile.draw(window);
            }
        }
		// Affichage des barres de vie
        sf::RectangleShape batterie1(sf::Vector2f(80, 160 * P1.getHealth() / 100.0f));
        batterie1.setPosition(5, 35 + (100 - P1.getHealth()));
        batterie1.setFillColor(sf::Color::Green);
        window.draw(batterie1);
        window.draw(sprite1);

        sf::RectangleShape batterie2(sf::Vector2f(80, 160 * P2.getHealth() / 100.0f));
        batterie2.setPosition(window.getSize().x - 95, 35 + (100 - P2.getHealth()));
        batterie2.setFillColor(sf::Color::Green);
        window.draw(batterie2);
        window.draw(cloneSprite1);


		window.display();
		
    }

    return false;
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

