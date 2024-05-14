#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <SFML/Graphics.hpp>
#include "bonus.hpp"

class Robot {
public:
    // Constructeur
	Robot();
    Robot(Hexagone& hex, float x, float y, char controlScheme, sf::Color color);
	
	
	
    // Destructeur
    virtual ~Robot();

    // Fonctions de mouvement
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

	void moveForward();
	void moveBackward();
	void rotateLeft();
	void rotateRight();

	void setPosition(float x, float y);

	void saveLastPosition() {
        lastPosX = position.x;
        lastPosY = position.y;
    }

	void revertToLastPosition() {
        position.x = lastPosX;
        position.y = lastPosY;
		rectangleShape.setPosition(position);
    }
	void saveLastOrientation() {
        lastOrientation = orientation;
    }

    void revertToLastOrientation() {
        orientation = lastOrientation;
        rectangleShape.setRotation(orientation * 180 / M_PI);
    }
	void ensureInsideBoundary();
	bool isInsideBoundary() const;
	bool isTouchingBoundary() const;
	void repositionToCenter();
	bool checkCollision(const Robot& other) const;

	bool canMove(float newX, float newY);

    // Getters et Setters
    float getX() const;
    float getY() const;
    int getHealth() const;
	float getSpeed() const;
	float getWidth() const {
		return this->width;
	}
	int getDefense() const {
		return this->defense;
	}
	float getHeight() const {
		return this->height;
	}
	float getOrientation() const { return orientation; }
	char getControlScheme() const { return controlScheme; }  // Ajoutez ce getter
	std::vector<LineSegment> getLineSegments() const;


    void setHealth(int newHealth);

	void update(sf::RenderWindow& window);
	void handleCollision(Robot& other);
	void handleCollision(Bonus& other);

	void correctPosition(sf::Vector2f& pos);

	virtual void draw(sf::RenderWindow& window)=0;

		sf::RectangleShape get_Shape(){
		return rectangleShape;
	}

	void saveLastValidPosition() {
        if (hexagon.isInside(position.x, position.y)) {
            lastValidPosition = position;
        }
    }

	sf::Vector2f getTransformedPoint(float offsetX, float offsetY) const;

	// Nouvelle méthode pour dessiner les points de débogage
    void drawDebugPoints(sf::RenderWindow& window);

protected:

	Hexagone& hexagon;
    sf::Vector2f position;
    int health=10;       // Santé actuelle du robot
    float speed=10;      // Vitesse de déplacement du robot
    int attackPower;  // Puissance d'attaque
    int defense;      // Capacité de défense
	float lastPosX, lastPosY; 
	sf::RectangleShape rectangleShape;
	char controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
	sf::Color color;
	float width = 40;   // Largeur du robot, à adapter selon votre setup
    float height = 30;  // Hauteur du robot, à adapter selon votre setup
	sf::Vector2f lastValidPosition;
	float orientation; // Angle en radians
	float lastOrientation; // Sauvegarde de la dernière orientation
};



#endif // ROBOT_HPP