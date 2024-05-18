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
	sf::Font font;
        if (!font.loadFromFile("Ecriture.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return false;
        }
	sf::Event event;
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(50);  // Définir l'intervalle de mise à jour
	Hexagone hexagon(window.getSize().x, window.getSize().y);
    /// Appliquez un décalage vers le centre pour chaque robot
	int nbplay=0;
	Robot* rob1 = nullptr;
	Robot* rob2 = nullptr;
	char* player1;
    char* player2;
    Init debut;
	int res[2];
    while (debut.menu(window,&nbplay)) {}
	if(debut.name(window,player1,player2)){
    if (!debut.fin) {
		if(debut.choose(window,res)){
			if((res[0]==0) | (res[1]==0)) {
				return 0;}
			if(res[0]==1)rob1=new Sniper (hexagon,600,window.getSize().y/2,'A',sf::Color::Red);
			if(res[0]==2)rob1=new Tank (hexagon,600,window.getSize().y/2,'A',sf::Color::Red);
			if(res[0]==3)rob1= new Course (hexagon,600,window.getSize().y/2,'A',sf::Color::Red);
			if(res[1]==1)rob2=new Sniper (hexagon,800,window.getSize().y/2,'B',sf::Color::Blue);
			if(res[1]==2)rob2=new Tank (hexagon,800,window.getSize().y/2,'B',sf::Color::Blue);
			if(res[1]==3)rob2= new Course (hexagon,800,window.getSize().y/2,'B',sf::Color::Blue);
			if (!rob1 || !rob2) {
				if(!rob1){
				std::cerr << "Erreur lors de l'initialisation de rob 1" << std::endl;}
				if(!rob2){
				std::cerr << "Erreur lors de l'initialisation de rob 2" << std::endl;}
				return 1;
			}
			
			rob1->set_name(player1,font);
			rob2->set_name(player2,font);
			
			Affiche aff(hexagon, *rob1, *rob2);
			
			aff.set_nbPlayers(nbplay);
			while (aff.refresh(window, timePerMove, clock, event)) {
				aff.updateControls(*rob1);
				if (aff.getNbPlayers() == 2) {
					aff.updateControls(*rob2);
				}
				(*rob1).updateProjectiles(window,*rob2);
				(*rob2).updateProjectiles(window,*rob2);
			}
    }
	}
	}
	delete rob1;
	delete rob2;


    return 0;
}

