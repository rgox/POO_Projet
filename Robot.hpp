#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <SFML/Graphics.hpp>
#include "bonus.hpp"
#include "arene.hpp"
class Robot {
public:
    // Constructeur
    Robot(Hexagone& hex, float x, float y, int health, float speed, int attackPower, int defense, char controlScheme, sf::Color color);
	
	
	
    // Destructeur
    virtual ~Robot();

    // Fonctions de mouvement
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

	void setPosition(float x, float y);

	void saveLastPosition() {
        lastPosX = position.x;
        lastPosY = position.y;
    }

	void revertToLastPosition() {
        position.x = lastPosX;
        position.y = lastPosY;
    }

	void ensureInsideBoundary(sf::Vector2f& pos);

	bool canMove(float newX, float newY);

    // Getters et Setters
    float getX() const;
    float getY() const;
    int getHealth() const;
	float getSpeed() const;
	float getWidth() const {
		return this->width;
	}
	float getHeight() const {
		return this->height;
	}

    void setHealth(int newHealth);

	void update(sf::RenderWindow& window);
	void handleCollision(Robot& other);
	void handleCollision(Bonus& other);

	void correctPosition(sf::Vector2f& pos);

	void draw(sf::RenderWindow& window);
		sf::RectangleShape get_Shape(){
		return rectangleShape;
	}

	void saveLastValidPosition() {
        if (hexagon.isInside(position.x, position.y)) {
            lastValidPosition = position;
        }
    }

	void drawDebug(sf::RenderWindow& window) {
		sf::CircleShape marker(1);
		marker.setFillColor(sf::Color::Red);
		marker.setPosition(position.x, position.y);
		window.draw(marker);
		marker.setPosition(position.x + width-1, position.y );
		window.draw(marker);
		marker.setPosition(position.x , position.y + height-1);
		window.draw(marker);
		marker.setPosition(position.x + width-1, position.y + height-1);
		window.draw(marker);
}




protected:

	Hexagone& hexagon;
    sf::Vector2f position;
    int health;       // Santé actuelle du robot
    float speed;      // Vitesse de déplacement du robot
    int attackPower;  // Puissance d'attaque
    int defense;      // Capacité de défense
	float lastPosX, lastPosY;
	sf::RectangleShape rectangleShape;
	char controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
	sf::Color color;
	float width = 40;   // Largeur du robot, à adapter selon votre setup
    float height = 30;  // Hauteur du robot, à adapter selon votre setup
	sf::Vector2f lastValidPosition;
};



#endif // ROBOT_HPP