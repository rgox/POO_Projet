#include <SFML/Graphics.hpp>
#include "sniper.hpp"
#include "Tank.hpp"

#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"
#include "affichage.hpp"


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

   	std::cout << hexagon.getPoint(0).x << std::endl;
    Affiche aff(hexagon);
    while (aff.menu(window)) {}

    if (!aff.fin) {
		int voit=aff.choose(window);
		if(voit%10==0){
			Sniper rob2(hexagon,600,450,'A',sf::Color::Blue);
			if(voit-1==10){
				Sniper rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
					aff.updateControls(rob2,rob1);
				}
			}
			else if(voit-1==20){
				Tank rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
					aff.updateControls(rob2,rob1);
				}
			}
			else{
				Course rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
					aff.updateControls(rob2,rob1);
				}
			}
		}
		else if(voit%10==1){
			Tank rob2(hexagon,600,450,'A',sf::Color::Blue);
			if(voit-1==10){
				Sniper rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
					aff.updateControls(rob2,rob1);
				}
			}
			else if(voit-1==20){
				Tank rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
					aff.updateControls(rob2,rob1);
				}
			}
			else{
				Course rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
					aff.updateControls(rob2,rob1);
				}
			}
		}
		else if(voit%10==2){
			Course rob2(hexagon,600,450,'A',sf::Color::Blue);
			if(voit-1==10){
				Sniper rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)){
					aff.updateControls(rob2,rob1);
				}
			}
			else if(voit-1==20){
				Tank rob1(hexagon,400,450,'B',sf::Color::Blue);
				while  (aff.refresh(window, timePerMove, clock, event,rob1,rob2)){
            		aff.updateControls(rob2,rob1);
        		}
			}
			else{
				Course rob1(hexagon,400,450,'B',sf::Color::Blue);
				while (aff.refresh(window, timePerMove, clock, event,rob1,rob2)) {
            		aff.updateControls(rob2,rob1);
        		}
			}
			
		}
		else{
			return 0;
		}
        
    }

    return 0;
}
