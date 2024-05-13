#include <algorithm>
#include <cmath>
#include "Robot.hpp"

// Constructeur
Robot::Robot(Hexagone& hex, float x, float y, int health, float speed, int attackPower, int defense,char controlScheme, sf::Color color)
    : hexagon(hex), position(x,y), health(health), speed(speed), attackPower(attackPower), defense(defense), controlScheme(controlScheme){
		rectangleShape.setSize(sf::Vector2f(width, height));
		rectangleShape.setFillColor(color);
		rectangleShape.setOutlineThickness(2);
		rectangleShape.setOutlineColor(color);
		rectangleShape.setOrigin(width/2,height/2);
		rectangleShape.setPosition(position);
		}

// Destructeur

Robot::~Robot() {}

void Robot::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
	rectangleShape.setPosition(x, y);
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
    float newY = position.y - speed;
    if (canMove(position.x, newY)) {
        position.y = newY;
    }
}

void Robot::moveDown() {
    float newY = position.y + speed;
    if (canMove(position.x, newY)) {
        position.y = newY;
    }
}

void Robot::moveLeft() {
    float newX = position.x - speed;
    if (canMove(newX, position.y)) {
        position.x = newX;
    }
}

void Robot::moveRight() {
    float newX = position.x + speed;
    if (canMove(newX, position.y)) {
        position.x = newX;
    }
}

void Robot::update(sf::RenderWindow& window) {
	saveLastPosition();
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
    if (this->getX() < other.getX() + width && this->getX() + width > other.getX() &&
        this->getY() < other.getY() + height && this->getY() + height > other.getY()) {

        // Calculate the direction of recoil
        float deltaX = position.x - other.position.x;
        float deltaY = position.y - other.position.y;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Normalize the recoil vector
        if (distance != 0) {
            deltaX /= distance;
            deltaY /= distance;
        }

        // Apply a slight recoil
        float recoil = 5.0f; // You may adjust this parameter based on needs
        position.x += deltaX * recoil;
        position.y += deltaY * recoil;
        other.position.x -= deltaX * recoil;
        other.position.y -= deltaY * recoil;

        // Ensure both robots remain inside the hexagon
		if(!canMove(position.x,position.y)) revertToLastPosition();
		if(!canMove(other.position.x,other.position.y)) other.revertToLastPosition();

        /*ensureInsideBoundary(position);
        ensureInsideBoundary(other.position);*/
    }
}

void Robot::ensureInsideBoundary(sf::Vector2f& pos) {
    // Check all corners of the robot's bounding box
    if (!hexagon.isInside(pos.x, pos.y) ||
        !hexagon.isInside(pos.x + width, pos.y) ||
        !hexagon.isInside(pos.x, pos.y + height) ||
        !hexagon.isInside(pos.x + width, pos.y + height)) {
        revertToLastPosition();
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
    sf::RectangleShape shape(sf::Vector2f(width, height));
    shape.setPosition(position.x, position.y);
    shape.setFillColor(color);  // La couleur pourrait aussi être un attribut de Robot
    window.draw(shape);
}

bool Robot::canMove(float newX, float newY) {
    sf::Vector2f newTopLeft(newX, newY);
    sf::Vector2f newTopRight(newX + width, newY );
    sf::Vector2f newBottomLeft(newX, newY + height);
    sf::Vector2f newBottomRight(newX + width, newY + height);

    return hexagon.isInside(newTopLeft.x, newTopLeft.y) &&
           hexagon.isInside(newTopRight.x, newTopRight.y) &&
           hexagon.isInside(newBottomLeft.x, newBottomLeft.y) &&
           hexagon.isInside(newBottomRight.x, newBottomRight.y);
}