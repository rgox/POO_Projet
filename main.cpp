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
	sf::Event event;
    srand(static_cast<unsigned int>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(50);  // Définir l'intervalle de mise à jour
	Hexagone hexagon(window.getSize().x, window.getSize().y);
    /// Appliquez un décalage vers le centre pour chaque robot
	sf::Vector2f pos1 = hexagon.getPoint(0);
	sf::Vector2f pos3 = hexagon.getPoint(3);

	Robot* rob1 = nullptr;
	Robot* rob2 = nullptr;
    Init debut;
	int res[2];
    while (debut.menu(window)) {}

    if (!debut.fin) {
		if(debut.choose(window,res)){
			printf("res[0]= %d; res[1]=%d\n",res[0],res[1]);
		if(res[0]==0 | res[1]==0) {
			return 0;}
		if(res[0]==1)rob1=new Sniper (hexagon,600,window.getSize().y,'A',sf::Color::Red);
		if(res[0]==2)rob1=new Tank (hexagon,600,window.getSize().y,'A',sf::Color::Red);
		if(res[0]==3)rob1= new Course (hexagon,600,window.getSize().y,'A',sf::Color::Red);
		if(res[1]==1)rob2=new Sniper (hexagon,600,window.getSize().y,'A',sf::Color::Red);
		if(res[2]==2)rob2=new Tank (hexagon,600,window.getSize().y,'A',sf::Color::Red);
		if(res[3]==3)rob2= new Course (hexagon,600,window.getSize().y,'A',sf::Color::Red);
		printf("Peut-être \n");
		Affiche aff(hexagon, *rob1, *rob2);
		printf("ICI");
        while (aff.refresh(window, timePerMove, clock, event)) {
            aff.updateControls(*rob1);
            if (aff.getNbPlayers() == 2) {
                aff.updateControls(*rob2);
            }
			(*rob1).updateProjectiles(window);
    		(*rob2).updateProjectiles(window);
        }
    }
	}
	delete rob1;
	delete rob2;


    return 0;
}
