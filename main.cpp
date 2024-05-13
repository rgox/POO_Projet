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
    const sf::Time timePerMove = sf::milliseconds(200);  // Définir l'intervalle de mise à jour
	Hexagone hexagone(800,600);
    // Création des robots
    Robot robot1(400, 300, 100, 2, 20, 10, 'A', sf::Color::Red);
    Robot robot2(200, 300, 100, 2, 15, 10, 'B', sf::Color::Blue);
    Affiche aff(hexagone,  robot1,  robot2);
	while(!aff.menu(window)){}
	
	if(!aff.fin){

		while(aff.refresh(window,timePerMove,clock,event)){}   
		
	}
    return 0;
}
