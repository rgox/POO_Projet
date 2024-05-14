#include <SFML/Graphics.hpp>
#include "Robot.hpp"
#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"
#include "affichage.hpp"


int main() {
	sf::Event event;

    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(50);  // Définir l'intervalle de mise à jour
	Hexagone hexagon(window.getSize().x, window.getSize().y);
    /// Appliquez un décalage vers le centre pour chaque robot
	sf::Vector2f pos1 = hexagon.getPoint(0);
	sf::Vector2f pos3 = hexagon.getPoint(3);



    Robot robot1(hexagon, pos1.x - robot1.getWidth()/2, pos1.y - robot1.getHeight()/2, 100, 5, 20, 10, 'A', sf::Color::Red);
	robot1.setPosition(400,300);
    Robot robot2(hexagon, pos3.x, pos3.y, 100, 5, 15, 10, 'B', sf::Color::Blue);
	robot2.setPosition(200,300);

    Affiche aff(hexagon,  robot1,  robot2);
	while(aff.menu(window)){}
	
	if(!aff.fin){

		while(aff.refresh(window,timePerMove,clock,event)){}   
		
	}
    return 0;
}
