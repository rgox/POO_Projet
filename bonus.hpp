#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour rand et srand
#include <ctime>   // Pour time
#include "arene.hpp"



class Bonus {
private:
	sf::Vector2f position;
	sf::CircleShape circleShape;
	sf::RectangleShape rectangleShape;
	sf::ConvexShape triangleShape;
	std::string shape;
	int type=rand()%4+1;
	int value=rand()%10+1;
	int apptime=10;
	
public:
    Bonus(Hexagone arene) {
        // Initialiser le générateur de nombres pseudo-aléatoires avec le temps actuel
        srand(static_cast<unsigned int>(time(nullptr)));

        // Générer une position aléatoire dans la fenêtre
        position.x = static_cast<float>(rand() % 800); // Position x aléatoire dans une fenêtre de 800x600
        position.y = static_cast<float>(rand() % 600); // Position y aléatoire dans une fenêtre de 800x600
		while(arene.isInside(position.x,position.y)){
			position.x = static_cast<float>(rand() % 800); 
        	position.y = static_cast<float>(rand() % 600); }   

        // Créer une forme aléatoire (dans cet exemple, un cercle, un rectangle ou un triangle)
        int shapeType = rand() % 3;
        switch (shapeType) {
            case 0: // Cercle
                circleShape.setRadius(20);
                circleShape.setFillColor(sf::Color::Green);
                circleShape.setOutlineThickness(2);
                circleShape.setOutlineColor(sf::Color::Black);
                circleShape.setOrigin(20, 20); // Origine au centre du cercle
                circleShape.setPosition(position);
				shape="cercle";
                break;
            case 1: // Rectangle
                rectangleShape.setSize(sf::Vector2f(40, 40));
                rectangleShape.setFillColor(sf::Color::Blue);
                rectangleShape.setOutlineThickness(2);
                rectangleShape.setOutlineColor(sf::Color::Black);
                rectangleShape.setOrigin(20, 20); // Origine au centre du rectangle
                rectangleShape.setPosition(position);
				shape="rectangle";
                break;
            case 2: // Triangle
                triangleShape.setPointCount(3);
                triangleShape.setPoint(0, sf::Vector2f(0, -20));
                triangleShape.setPoint(1, sf::Vector2f(20, 20));
                triangleShape.setPoint(2, sf::Vector2f(-20, 20));
                triangleShape.setFillColor(sf::Color::Red);
                triangleShape.setOutlineThickness(2);
                triangleShape.setOutlineColor(sf::Color::Black);
                triangleShape.setOrigin(0, 0); // Origine au centre du triangle
                triangleShape.setPosition(position);
				shape="triangle";
                break;
        }
    }
	sf::Vector2f get_position(){
		return position;
	}
    sf::CircleShape get_circleShape(){
		return circleShape;
	}
    sf::RectangleShape get_rectangleShape(){
		return rectangleShape;
	}
	sf::ConvexShape get_triangleShape(){
		return triangleShape;
	}

	std::string get_shape(){
		return shape;
	}

	int get_bonustype(){
		return type;
	}
	int get_value(){
		return value;
	}

    void drawBonus(sf::RenderWindow& window) const ;

};
#endif //BONUS_HPP