#include "Init.hpp"
#include <iomanip> // Inclure la bibliothèque pour std::setprecision
#include <sstream> // Inclure la bibliothèque pour std::ostringstream
#include <iostream>
#include <cstring> // Pour strdup
bool Init::menu(sf::RenderWindow& window,int* i) {
	
    sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        // Gestion de l'erreur si le chargement de la police échoue
        return false;
    }
	
    sf::Text title; //on creer le titre
	
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

                    *i=1;
					selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, 5)); 
					sprite1.setPosition(singlePlayerOption.getPosition() + sf::Vector2f(200, 5));
                } else if (multiPlayerOption.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode deux joueurs

                    *i=2;
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


bool Init::choose(sf::RenderWindow& window,int *res) {

	res[0]=0;
	res[1]=0;


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
	title.setPosition(window.getSize().x/2-300,200);
	sf::Text clonetitle(title);
	clonetitle.setPosition(window.getSize().x/2-300,window.getSize().y-200);

    sf::Text Player1;
    Player1.setFont(font);
    Player1.setString("Player 1");
    Player1.setCharacterSize(35);
    Player1.setFillColor(sf::Color::White);
    Player1.setPosition(window.getSize().x/2-250, window.getSize().y/2-100);


	sf::Text Player2;
    Player2.setFont(font);
    Player2.setString("Player 2");
    Player2.setCharacterSize(35);
    Player2.setFillColor(sf::Color::White);
    Player2.setPosition(window.getSize().x/2+250, window.getSize().y/2-100);


	 sf::Text Stats;
    Stats.setFont(font);
    Stats.setString("Statistics : ");
    Stats.setCharacterSize(20);
    Stats.setFillColor(sf::Color::White);
    Stats.setPosition(window.getSize().x/2-250, window.getSize().y/2+100);
	sf::Text Stats2(Stats);
	Stats2.setPosition(window.getSize().x/2+250,window.getSize().y/2+100);


	sf::Text Life1;
	Life1.setFont(font);
    Life1.setString("");
    Life1.setCharacterSize(20);
    Life1.setFillColor(sf::Color::White);
	Life1.setPosition(window.getSize().x/2-250, window.getSize().y/2+120);
	sf::Text Life2(Life1);
	Life2.setPosition(window.getSize().x/2+250,window.getSize().y/2+120);

	sf::Text Defense1;
	Defense1.setFont(font);
    Defense1.setString("");
    Defense1.setCharacterSize(20);
    Defense1.setFillColor(sf::Color::White);
	Defense1.setPosition(window.getSize().x/2-250, window.getSize().y/2+140);
	sf::Text Defense2(Defense1);
	Defense2.setPosition(window.getSize().x/2+250,window.getSize().y/2+140);

	sf::Text Attack1;
	Attack1.setFont(font);
    Attack1.setString("");
    Attack1.setCharacterSize(20);
    Attack1.setFillColor(sf::Color::White);
	Attack1.setPosition(window.getSize().x/2-250, window.getSize().y/2+160);
	sf::Text Attack2(Attack1);
	Attack2.setPosition(window.getSize().x/2+250,window.getSize().y/2+160);

	sf::Text Speed1;
	Speed1.setFont(font);
    Speed1.setString("");
    Speed1.setCharacterSize(20);
    Speed1.setFillColor(sf::Color::White);
	Speed1.setPosition(window.getSize().x/2-250, window.getSize().y/2+180);
	sf::Text Speed2(Speed1);
	Speed2.setPosition(window.getSize().x/2+250,window.getSize().y/2+180);


    

    sf::Text goButton;
    goButton.setFont(font);
    goButton.setString("Go !");
    goButton.setCharacterSize(25);
    goButton.setFillColor(sf::Color::White);
    goButton.setPosition(window.getSize().x/2, window.getSize().y/2+20);
	
	//Indicateur Gauche
	sf::Texture textLeftButton;
    if (!textLeftButton.loadFromFile("flatDark23.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        return res;
    }
	sf::Sprite LeftButton1;
	LeftButton1.setTexture(textLeftButton);
	LeftButton1.setScale(1, 1);
	LeftButton1.setPosition(window.getSize().x/2-350,window.getSize().y/2);
	sf::Sprite LeftButton2;
	LeftButton2.setTexture(textLeftButton);
	LeftButton2.setScale(1, 1);
	LeftButton2.setPosition(window.getSize().x/2+150,window.getSize().y/2);

	//Indicateur Droit
	sf::Texture textRightButton;
    if (!textRightButton.loadFromFile("flatDark24.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        return res;
    }
	sf::Sprite RightButton1;
	RightButton1.setTexture(textRightButton);
	RightButton1.setScale(1, 1);
	RightButton1.setPosition(window.getSize().x/2-150,window.getSize().y/2);
	sf::Sprite RightButton2;
	RightButton2.setTexture(textRightButton);
	RightButton2.setScale(1, 1);
	RightButton2.setPosition(window.getSize().x/2+350,window.getSize().y/2);


	//Sniper
	sf::Texture police1;
    if (!police1.loadFromFile("police.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        printf("Problème chargement image sniper");
    }
	sf::Sprite sniper1;
	sniper1.setTexture(police1);
	sniper1.setScale(2, 2);
	sf::Sprite sniper2;
	sniper2.setTexture(police1);
	sniper2.setScale(2, 2);
	

	sniper1.setPosition(window.getSize().x/2-250,window.getSize().y/2);
	sniper2.setPosition(window.getSize().x/2+250,window.getSize().y/2);
	
	//Tank
	sf::Texture camion1;
    if (!camion1.loadFromFile("truckcabin.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        printf("Problème chargement image sniper");
    }
	sf::Sprite tank1;
	tank1.setTexture(camion1);
	tank1.setScale(2, 2);
	sf::Sprite tank2;
	tank2.setTexture(camion1);
	tank2.setScale(2, 2);
	

	tank1.setPosition(window.getSize().x/2-250,window.getSize().y/2);
	tank2.setPosition(window.getSize().x/2+250,window.getSize().y/2);
 
 	//Course
	sf::Texture F1;
    if (!F1.loadFromFile("formula.png") ) {
        // Gestion de l'erreur si le chargement de la texture échoue
        printf("Problème chargement image sniper");
    }
	sf::Sprite course1;
	course1.setTexture(F1);
	course1.setScale(2, 2);
	sf::Sprite course2;
	course2.setTexture(F1);
	course2.setScale(2, 2);
	

	course1.setPosition(window.getSize().x/2-250,window.getSize().y/2);
	course2.setPosition(window.getSize().x/2+250,window.getSize().y/2);
 



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
            return res;
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
                return false; // Retourne false si la fenêtre est fermée
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (RightButton1.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode un joueur
                    // Exemple : initialiser un seul robot
                    res[0]=res[0]+1;
                } else if (LeftButton1.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode deux joueurs
                    // Exemple : initialiser deux robots
                    res[0]=res[0]+1;
                } else if (goButton.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour lancer le jeu après avoir choisi le mode de jeu
                    return true; // Retourne true pour démarrer le jeu
                }else if (LeftButton2.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode deux joueurs
                    // Exemple : initialiser deux robots
                    res[1]=res[1]-1;
                } else if (RightButton2.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour lancer le jeu après avoir choisi le mode de jeu
                    res[1]=res[1]+1;// Retourne true pour démarrer le jeu
                }

            }
			
			
		
        }
		

        window.display();
        window.clear();
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
		window.draw(Stats);
        window.draw(Stats2);
		window.draw(Life1);
        window.draw(Life2);
		window.draw(Attack1);
        window.draw(Attack2);
		window.draw(Defense1);
        window.draw(Defense2);
		window.draw(Speed1);
        window.draw(Speed2);
		// Affichage de l'image actuelle
        sprite.setTexture(frames[currentFrame]);
		sprite.setScale((window.getSize().x)/480,(window.getSize().y)/300);

		// Avancer au prochain frame toutes les 100 millisecondes (10 images par seconde)
        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            currentFrame = (currentFrame + 1) % frames.size();
            clock.restart();
        } 	  
		
		while(res[0]<=0){
			res[0]=res[0]+3;
			
		}
		while(res[1]<=0){
			res[1]=res[1]+3;
		}
        if(res[0]%3==0){
			res[0]=3;
			window.draw(course1);
			Life1.setString("Life : 100");
			Defense1.setString("Defense : 25");
			Speed1.setString("Speed : 15");
			Attack1.setString("Attack : 25");
		
			}
		else if(res[0]%3==1){
			res[0]=1;
			window.draw(sniper1);
			Life1.setString("Life : 100");
			Defense1.setString("Defense : 10");
			Speed1.setString("Speed : 5");
			Attack1.setString("Attack : 50");
			}
		else{
			res[0]=2;
			window.draw(tank1);
			Life1.setString("Life : 200");
			Defense1.setString("Defense : 40");
			Speed1.setString("Speed : 2");
			Attack1.setString("Attack : 25");}

		if(res[1]%3==0){
			res[1]=3;
			window.draw(course2);
			Life2.setString("Life : 100");
			Defense2.setString("Defense : 25");
			Speed2.setString("Speed : 15");
			Attack2.setString("Attack : 25");}
		else if(res[1]%3==1){
			res[1]=1;
			window.draw(sniper2);
			Life2.setString("Life : 100");
			Defense2.setString("Defense : 10");
			Speed2.setString("Speed : 5");
			Attack2.setString("Attack : 50");}
		else{
			res[1]=2;
			window.draw(tank2);
			Life2.setString("Life : 200");
			Defense2.setString("Defense : 40");
			Speed2.setString("Speed : 2");
			Attack2.setString("Attack : 25");}
        window.display();
    }
	
    return false; // Retourne false par défaut
}


bool Init::name(sf::RenderWindow& window, char*& player1Name, char*& player2Name) {
        sf::Font font;
        if (!font.loadFromFile("Ecriture.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return false;
        }
		sf::Text Player1;
		Player1.setFont(font);
		Player1.setString("Player 1");
		Player1.setCharacterSize(35);
		Player1.setFillColor(sf::Color::White);
		Player1.setPosition(window.getSize().x/2-400, window.getSize().y/2-100);


		sf::Text Player2;
		Player2.setFont(font);
		Player2.setString("Player 2");
		Player2.setCharacterSize(35);
		Player2.setFillColor(sf::Color::White);
		Player2.setPosition(window.getSize().x/2+300, window.getSize().y/2-100);

        InputBox inputBox1(300, 50, font);
        inputBox1.setPosition(window.getSize().x/2-500, window.getSize().y/2);

        InputBox inputBox2(300, 50, font);
        inputBox2.setPosition(window.getSize().x/2+200, window.getSize().y/2);

        sf::Text goButton;
        goButton.setFont(font);
        goButton.setString("Go !");
        goButton.setCharacterSize(25);
        goButton.setFillColor(sf::Color::White);
        goButton.setPosition(window.getSize().x / 2.0f - 50, window.getSize().y / 2.0f + 50);

        bool isEnteringPlayer1 = true;
        inputBox1.setFocus(true);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (inputBox1.contains(event.mouseButton.x, event.mouseButton.y)) {
                        inputBox1.setFocus(true);
                        inputBox2.setFocus(false);
                    } else if (inputBox2.contains(event.mouseButton.x, event.mouseButton.y)) {
                        inputBox1.setFocus(false);
                        inputBox2.setFocus(true);
                    } else if (goButton.getGlobalBounds().contains(mousePosition)) {
                        player1Name = strdup(inputBox1.getString().c_str());
                        player2Name = strdup(inputBox2.getString().c_str());
                        return true; // Retourne true pour démarrer le jeu
                    } else {
                        inputBox1.setFocus(false);
                        inputBox2.setFocus(false);
                    }
                }

                inputBox1.handleEvent(event);
                inputBox2.handleEvent(event);

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    if (isEnteringPlayer1) {
                        inputBox1.setFocus(false);
                        inputBox2.setFocus(true);
                        isEnteringPlayer1 = false;
                    } else {
                        player1Name = strdup(inputBox1.getString().c_str());
                        player2Name = strdup(inputBox2.getString().c_str());
                        return true;
                    }
                }
            }

            window.clear();
            inputBox1.draw(window);
            inputBox2.draw(window);
            window.draw(goButton);
			window.draw(Player1);
			window.draw(Player2);
            window.display();
        }

        return false;
    }