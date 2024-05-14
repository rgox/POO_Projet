#include <algorithm>
#include <cmath>
#include "Robot.hpp"
#include <cmath>

// Constructeur
Robot::Robot(Hexagone& hex, float x, float y, char controlScheme, sf::Color color)
: hexagon(hex), position(x,y),  controlScheme(controlScheme),orientation(0.0f){
		rectangleShape.setSize(sf::Vector2f(width, height));
		rectangleShape.setFillColor(color);
		rectangleShape.setOutlineThickness(2);
		rectangleShape.setOutlineColor(color);
		rectangleShape.setOrigin(width/2,height/2);
		rectangleShape.setPosition(position);
		rectangleShape.setRotation(orientation * 180 / M_PI); // Initialiser l'orientation
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

void Robot::moveForward() {
    float newX = position.x + speed * std::cos(orientation);
    float newY = position.y + speed * std::sin(orientation);
    if (canMove(newX, newY)) {
        position.x = newX;
        position.y = newY;
        rectangleShape.setPosition(position);
    }
}

void Robot::moveBackward() {
    float newX = position.x - speed * std::cos(orientation);
    float newY = position.y - speed * std::sin(orientation);
    if (canMove(newX, newY)) {
        position.x = newX;
        position.y = newY;
        rectangleShape.setPosition(position);
    }
}

void Robot::rotateLeft() {
    orientation -= 0.1f; // Ajuster cette valeur pour la vitesse de rotation
    rectangleShape.setRotation(orientation * 180 / M_PI);
}

void Robot::rotateRight() {
    orientation += 0.1f; // Ajuster cette valeur pour la vitesse de rotation
    rectangleShape.setRotation(orientation * 180 / M_PI);
}

void Robot::update(sf::RenderWindow& window) {
    saveLastPosition();
    if (controlScheme == 'A') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rotateRight();
    } else if (controlScheme == 'B') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight();
    }
}

void Robot::handleCollision(Robot& other) {
    if (rectangleShape.getGlobalBounds().intersects(other.rectangleShape.getGlobalBounds())) {
        // Calculer la direction de recul basée sur l'orientation des robots
        float deltaX = position.x - other.position.x;
        float deltaY = position.y - other.position.y;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Normaliser le vecteur de recul
        if (distance != 0) {
            deltaX /= distance;
            deltaY /= distance;
        }

        // Appliquer un léger recul
        float recoil = 5.0f; // Vous pouvez ajuster ce paramètre selon les besoins
        position.x += deltaX * recoil;
        position.y += deltaY * recoil;
        other.position.x -= deltaX * recoil;
        other.position.y -= deltaY * recoil;

        // Assurer que les deux robots restent à l'intérieur de l'hexagone
        ensureInsideBoundary(position);
        ensureInsideBoundary(other.position);
    }
}

void Robot::ensureInsideBoundary(sf::Vector2f& pos) {
	const float margin = 5.0f; // Marge de sécurité en pixels

    // Vérifier toutes les coins du rectangle avec l'orientation
    sf::Transform transform;
    transform.rotate(orientation * 180 / M_PI, pos);

    sf::Vector2f topLeft = transform.transformPoint(sf::Vector2f(pos.x, pos.y));
    sf::Vector2f topRight = transform.transformPoint(sf::Vector2f(pos.x + width, pos.y));
    sf::Vector2f bottomLeft = transform.transformPoint(sf::Vector2f(pos.x, pos.y + height));
    sf::Vector2f bottomRight = transform.transformPoint(sf::Vector2f(pos.x + width, pos.y + height));

    if (!hexagon.isInside(topLeft.x - margin, topLeft.y - margin) ||
        !hexagon.isInside(topRight.x + margin, topRight.y - margin) ||
        !hexagon.isInside(bottomLeft.x - margin, bottomLeft.y + margin) ||
        !hexagon.isInside(bottomRight.x + margin, bottomRight.y + margin)) {
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


 void draw(sf::RenderWindow& window);

sf::Vector2f Robot::getTransformedPoint(float offsetX, float offsetY) const {
    float cosAngle = std::cos(orientation);
    float sinAngle = std::sin(orientation);

    // Appliquer la rotation à l'offset
    float x = position.x + offsetX * cosAngle - offsetY * sinAngle;
    float y = position.y + offsetX * sinAngle + offsetY * cosAngle;

    return sf::Vector2f(x, y);
}

bool Robot::canMove(float newX, float newY) {
    const float margin = 1.0f; // Marge de sécurité en pixels

    // Calculer les positions des coins après le déplacement
    sf::Vector2f newTopLeft = getTransformedPoint(- width / 2, - height / 2);
    sf::Vector2f newTopRight = getTransformedPoint(width / 2, - height / 2);
    sf::Vector2f newBottomLeft = getTransformedPoint(- width / 2, height / 2);
    sf::Vector2f newBottomRight = getTransformedPoint(width / 2, height / 2);

    // Vérifier si tous les coins sont à l'intérieur de l'hexagone avec une marge de sécurité
    return hexagon.isInside(newTopLeft.x - margin, newTopLeft.y - margin) &&
           hexagon.isInside(newTopRight.x + margin, newTopRight.y - margin) &&
           hexagon.isInside(newBottomLeft.x - margin, newBottomLeft.y + margin) &&
           hexagon.isInside(newBottomRight.x + margin, newBottomRight.y + margin);
}

void Robot::drawDebugPoints(sf::RenderWindow& window) {
    // Calculer les positions des coins
    sf::Vector2f topLeft = getTransformedPoint(0, 0 );
    sf::Vector2f topRight = getTransformedPoint(width , 0);
    sf::Vector2f bottomLeft = getTransformedPoint(0, height );
    sf::Vector2f bottomRight = getTransformedPoint(width , height );

    // Créer des cercles pour chaque coin
    sf::CircleShape pointShape(2);
    pointShape.setFillColor(sf::Color::Green);

    pointShape.setPosition(topLeft);
    window.draw(pointShape);

    pointShape.setPosition(topRight);
    window.draw(pointShape);

    pointShape.setPosition(bottomLeft);
    window.draw(pointShape);

    pointShape.setPosition(bottomRight);
    window.draw(pointShape);
}
