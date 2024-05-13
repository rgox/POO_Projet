#include <algorithm>
#include <cmath>
#include "Robot.hpp"

// Constructeur

Robot::Robot(float x, float y, int health, float speed, int attackPower, int defense,char controlScheme, sf::Color color)
    : health(health), speed(speed), attackPower(attackPower), defense(defense), controlScheme(controlScheme){
		rectangleShape.setSize(sf::Vector2f(40, 40));
		rectangleShape.setFillColor( color);
		rectangleShape.setOutlineThickness(2);
		rectangleShape.setOutlineColor(color);
		rectangleShape.setOrigin(20, 20); // Origine au centre du rectangle
		rectangleShape.setPosition(position);
		}

// Destructeurbarrière

Robot::~Robot() {}

void Robot::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

// Getters
float Robot::getX() const {
    return position.x;
}

float Robot::getY() const {
    return position.y;
}

int Robot::getHealth() const {
    return health;
}

float Robot::getSpeed() const {
    return speed;
}

// Setters
void Robot::setHealth(int newHealth) {
    health = newHealth;
}

void Robot::moveUp() {
    position.y = std::max(0.0f, position.y - speed);
}

void Robot::moveDown() {
    position.y = std::min(600.0f, position.y + speed);
}

void Robot::moveLeft() {
    position.x = std::max(0.0f, position.x - speed);
}

void Robot::moveRight() {
    position.x = std::min(800.0f, position.x + speed);
}

void Robot::update(sf::RenderWindow& window) {
    if (controlScheme == 'A') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveRight();
    } else if (controlScheme == 'B') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight();
    }
}

void Robot::handleCollision(Robot& other) {
    if (this->getX() < other.getX() + 50 && this->getX() + 50 > other.getX() &&
        this->getY() < other.getY() + 50 && this->getY() + 50 > other.getY()) {

        // Calcul de la direction de recul
        float deltaX = position.x - other.position.x;
        float deltaY = position.y - other.position.y;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Normalisation du vecteur de recul
        if (distance != 0) {
            deltaX /= distance;
            deltaY /= distance;
        }

        // Appliquer un léger recul
        float recul = 5.0f; // Vous pouvez ajuster ce paramètre selon le besoin
        position.x += deltaX * recul;
        position.y+= deltaY * recul;
        other.position.x -= deltaX * recul;
        other.position.y -= deltaY * recul;

        // Vérifier les limites de la fenêtre pour chaque robot
        position.x = std::min(std::max(0.0f, position.x), 800.0f - 50.0f); // Largeur de fenêtre moins largeur de robot
        position.y = std::min(std::max(0.0f, position.y), 600.0f - 50.0f); // Hauteur de fenêtre moins hauteur de robot
        other.position.x = std::min(std::max(0.0f, other.position.x), 800.0f - 50.0f);
        other.position.y = std::min(std::max(0.0f, other.position.y), 600.0f - 50.0f);
    }
}

void Robot::handleCollision(Bonus& bonus) {

    // Obtenir les limites globales des formes
    sf::FloatRect robotBounds = get_Shape().getGlobalBounds();
    sf::FloatRect bonusBounds;

    if (bonus.get_shape() == "circle") {
        // Obtenir les limites globales du cercle
        sf::FloatRect circleBounds = bonus.get_circleShape().getGlobalBounds();

        // Vérifier la collision entre le robot et le cercle
        if (robotBounds.intersects(circleBounds)) {
            revertToLastPosition(); // Revenir à la dernière position sûre
            // Autres actions à effectuer en cas de collision avec un cercle
        }
    } else if (bonus.get_shape() == "rectangle") {
        // Obtenir les limites globales du rectangle
        sf::FloatRect rectangleBounds = bonus.get_rectangleShape().getGlobalBounds();

        // Vérifier la collision entre le robot et le rectangle
        if (robotBounds.intersects(rectangleBounds)) {
            revertToLastPosition(); // Revenir à la dernière position sûre
            // Autres actions à effectuer en cas de collision avec un rectangle
        }
    } else if (bonus.get_shape() == "triangle") {
        // Obtenir les limites globales du triangle
        sf::FloatRect triangleBounds = bonus.get_triangleShape().getGlobalBounds();

        // Vérifier la collision entre le robot et le triangle
        if (robotBounds.intersects(triangleBounds)) {
            revertToLastPosition(); // Revenir à la dernière position sûre
            // Autres actions à effectuer en cas de collision avec un triangle
        }
    }
}



void Robot::draw(sf::RenderWindow& window) {
    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));  // La taille devrait être un membre de la classe Robot
    shape.setPosition(position.x, position.y);
    shape.setFillColor(color);  // La couleur pourrait aussi être un attribut de Robot
    window.draw(shape);
}