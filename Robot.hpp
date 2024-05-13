#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <SFML/Graphics.hpp>
#include "bonus.hpp"
class Robot {
public:
    // Constructeur
	Robot() {};
    Robot(float x, float y, int health, float speed, int attackPower, int defense, char controlScheme, sf::Color color);
	
	
	
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

    // Getters et Setters
    float getX() const;
    float getY() const;
    int getHealth() const;
	float getSpeed() const;

    void setHealth(int newHealth);

	void update(sf::RenderWindow& window);
	void handleCollision(Robot& other);
	void handleCollision(Bonus& other);

	void draw(sf::RenderWindow& window);
	sf::RectangleShape get_Shape(){
		return rectangleShape;
	}

protected:
    sf::Vector2f position;
    int health;       // Santé actuelle du robot
    float speed;      // Vitesse de déplacement du robot
    int attackPower;  // Puissance d'attaque
    int defense;      // Capacité de défense
	float lastPosX, lastPosY;
	sf::RectangleShape rectangleShape;
	char controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
	sf::Color color;
};


#endif // ROBOT_HPP