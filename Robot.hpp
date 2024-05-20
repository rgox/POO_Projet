#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <SFML/Graphics.hpp>
#include "bonus.hpp"
#include "Projectile.hpp"
#include "geometry.hpp"

class Projectile;

class Robot {

	public:
		// Constructeur
		Robot(Arene& hex, float x, float y, char controlScheme, sf::Color color);
		
		// Destructeur
		virtual ~Robot();

		// Fonctions de mouvement
		void moveForward();
		void moveBackward();
		void rotateLeft();
		void rotateRight();

		// Setters
		void setPosition(float x, float y);
		void setHealth(int newHealth);
		void setSpeed(int newSpeed);
		void setDefense(int newDefense);
		void set_Orientation(float newOrientation);
		void set_name(const std::string& n, sf::Font& font);
		void setNamePosition(float x, float y);

		// Getters 
		float getX() const;
		float getY() const;
		int getHealth() const;
		float getSpeed() const;
		float getWidth() const {return this->width;}
		int getDefense() const {return this->defense;}
		float getHeight() const {return this->height;}
		float getOrientation() const { return orientation; }
		float get_Orientation(){ return orientation ;}
		char getControlScheme() const { return controlScheme; }  // Ajoutez ce getter
		std::vector<LineSegment> getLineSegments() const;
		sf::Text get_name(){return name;}
		const sf::Text& get_name_draw() const { return name;} //Fonction particulière pour window.draw()
		sf::RectangleShape get_Shape(){ return rectangleShape;}
		sf::Vector2f getTransformedPoint(float offsetX, float offsetY) const;
		std::vector<Projectile>& getProjectiles() { return projectiles; }
		const std::vector<Projectile>& getProjectiles() const { return projectiles; }

		//Savers
		void saveLastPosition() {
			lastPosX = position.x;
			lastPosY = position.y;
		}

		void saveLastOrientation() {
			lastOrientation = orientation;
		}

		void saveLastValidPosition() {
			if (hexagon.isInside(position.x, position.y)) lastValidPosition = position;
		}

		//Reverters
		void revertToLastPosition() {
			position.x = lastPosX;
			position.y = lastPosY;
			rectangleShape.setPosition(position);
		}

		void revertToLastOrientation() {
			orientation = lastOrientation;
			rectangleShape.setRotation(orientation * 180 / M_PI);
		}

		//Gestion du contact entre la voiture et un autre élément 
		bool canMove(float newX, float newY);//Vérifie que suite à une collision la voiture peut encore bouger

		//Contact avec Bordures
		void ensureInsideBoundary();
		bool isInsideBoundary() const;
		bool isTouchingBoundary() const;
		void repositionToCenter(); //Repostitione la voiture face au centre de l'arène

		//Contact avec Robots
		bool checkCollision(const Robot& other) const;
		void handleCollision(Robot& other);


		//Gestion des Projectiles
		void fire();//Permet de tirer sur l'adversaire
		void updateProjectiles(sf::RenderWindow& window, Robot& other);//Mets à jour les projectiles


		//Updater
		void update(sf::RenderWindow& window, Robot& other);//Met l'image du robot à jour sur la fenêtre


		//Draw
		virtual void draw(sf::RenderWindow& window)=0;//Dessine le robot sur la fenêtre, estredéfinie dans les classes enfant
		void drawDebugPoints(sf::RenderWindow& window);// Méthode pour dessiner les points de débogage


	protected:

		Arene& hexagon;
		sf::Vector2f position;
		sf::Vector2f lastValidPosition;
		std::vector<Projectile> projectiles;
		sf::Text name;
		sf::RectangleShape rectangleShape;
		sf::Color color;
		int health=10;       // Santé actuelle du robot
		int attackPower;  // Puissance d'attaque
		int defense;      // Capacité de défense
		float speed=10;      // Vitesse de déplacement du robot
		float lastPosX, lastPosY; 
		float width = 40;   // Largeur du robot, à adapter selon votre setup
		float height = 30;  // Hauteur du robot, à adapter selon votre setup
		float orientation; // Angle en radians
		float lastOrientation; // Sauvegarde de la dernière orientation
		char controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
};

#endif // ROBOT_HPP