#include <algorithm>
#include <cmath>
#include "Robot.hpp"
#include "geometry.hpp"
#include "Projectile.hpp"

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

std::vector<LineSegment> Robot::getLineSegments() const {
    std::vector<LineSegment> segments;
    
    sf::Vector2f topLeft = getTransformedPoint(-width / 2, -height / 2);
    sf::Vector2f topRight = getTransformedPoint(width / 2, -height / 2);
    sf::Vector2f bottomLeft = getTransformedPoint(-width / 2, height / 2);
    sf::Vector2f bottomRight = getTransformedPoint(width / 2, height / 2);
    
    segments.push_back({topLeft, topRight});
    segments.push_back({topRight, bottomRight});
    segments.push_back({bottomRight, bottomLeft});
    segments.push_back({bottomLeft, topLeft});
    
    return segments;
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
    saveLastPosition();
    float newX = position.x + speed * std::cos(orientation);
    float newY = position.y + speed * std::sin(orientation);
    if (canMove(newX, newY)) {
        position.x = newX;
        position.y = newY;
        rectangleShape.setPosition(position);
        if (isTouchingBoundary()) {
            repositionToCenter();
        }
    } else {
        repositionToCenter();
    }
}

bool Robot::checkCollision(const Robot& other) const {
    return rectangleShape.getGlobalBounds().intersects(other.rectangleShape.getGlobalBounds());
}

void Robot::moveBackward() {
    saveLastPosition();
    float newX = position.x - speed * std::cos(orientation);
    float newY = position.y - speed * std::sin(orientation);
    if (canMove(newX, newY)) {
        position.x = newX;
        position.y = newY;
        rectangleShape.setPosition(position);
        if (isTouchingBoundary()) {
            repositionToCenter();
        }
    } else {
        repositionToCenter();
    }
}


bool Robot::isInsideBoundary() const {
    const float margin = 2.0f; // Marge de sécurité en pixels
    sf::Vector2f topLeft = getTransformedPoint(-width / 2, -height / 2);
    sf::Vector2f topRight = getTransformedPoint(width / 2, -height / 2);
    sf::Vector2f bottomLeft = getTransformedPoint(-width / 2, height / 2);
    sf::Vector2f bottomRight = getTransformedPoint(width / 2, height / 2);

    return hexagon.isInside(topLeft.x - margin, topLeft.y - margin) &&
           hexagon.isInside(topRight.x + margin, topRight.y - margin) &&
           hexagon.isInside(bottomLeft.x - margin, bottomLeft.y + margin) &&
           hexagon.isInside(bottomRight.x + margin, bottomRight.y + margin);
}

void Robot::rotateLeft() {
    saveLastOrientation();
    float newOrientation = orientation - 0.1f; // Ajustez cette valeur pour la vitesse de rotation
    rectangleShape.setRotation(newOrientation * 180 / M_PI);
    if (!isInsideBoundary()) {
        revertToLastOrientation();
    } else {
        orientation = newOrientation;
    }
}

bool Robot::isTouchingBoundary() const {
    const int margin = 20; // Marge de sécurité en pixels
    sf::Vector2f corners[] = {
        getTransformedPoint(-width / 2, -height / 2),
        getTransformedPoint(width / 2, -height / 2),
        getTransformedPoint(-width / 2, height / 2),
        getTransformedPoint(width / 2, height / 2)
    };

    for (const auto& corner : corners) {
		for(int i=-margin ; i<margin;i++){
			if (!hexagon.isInside(corner.x - margin, corner.y - margin)) {
				printf("aaaaaaaaaaaaaaaaaaaaah \n");
            	return true;
		}
        
        }
    }
    return false;
}

void Robot::repositionToCenter() {
    const float offset = 10.0f; // Distance à quelques pixels du mur
    sf::Vector2f center = hexagon.getCenter();

    // Calculer la direction du centre de l'arène
    float deltaX = center.x - position.x;
    float deltaY = center.y - position.y;
    float angleToCenter = std::atan2(deltaY, deltaX);

    // Repositionner le robot loin des bords
    position.x = center.x - (center.x - position.x) * (hexagon.getRadius() - offset) / hexagon.getRadius();
    position.y = center.y - (center.y - position.y) * (hexagon.getRadius() - offset) / hexagon.getRadius();
    rectangleShape.setPosition(position);

    // Réorienter vers le centre
    orientation = angleToCenter;
    rectangleShape.setRotation(orientation * 180 / M_PI);
}



void Robot::rotateRight() {
    saveLastOrientation();
    float newOrientation = orientation + 0.1f; // Ajustez cette valeur pour la vitesse de rotation
    rectangleShape.setRotation(newOrientation * 180 / M_PI);
    if (!isInsideBoundary()) {
        revertToLastOrientation();
    } else {
        orientation = newOrientation;
    }
}

void Robot::update(sf::RenderWindow& window, Robot& other) {
    saveLastPosition();
    if (controlScheme == 'A') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rotateRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) fire();
    } else if (controlScheme == 'B') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) moveForward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveBackward();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) rotateLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) rotateRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) fire();
    }

    updateProjectiles(window, other);
}

void Robot::handleCollision(Robot& other) {
    if (checkCollision(other)) {
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
        float recoil = 50.0f; // Vous pouvez ajuster ce paramètre selon les besoins
        position.x += deltaX * (recoil/defense);
        position.y += deltaY * (recoil/defense);
        other.position.x -= deltaX * (recoil/other.defense);
        other.position.y -= deltaY * (recoil/other.defense);

        // Assurer que les deux robots restent à l'intérieur de l'hexagone
        ensureInsideBoundary();
        other.ensureInsideBoundary();

        rectangleShape.setPosition(position);
        other.rectangleShape.setPosition(other.position);
    }
}

void Robot::ensureInsideBoundary() {
    const float margin = 2.0f; // Marge de sécurité en pixels
    std::vector<LineSegment> robotSegments = getLineSegments();
    std::vector<LineSegment> hexagonSegments = hexagon.getHexagonSegments();

    bool collisionDetected = false;

    for (const auto& robotSegment : robotSegments) {
        for (const auto& hexSegment : hexagonSegments) {
            if (doLinesIntersect(robotSegment, hexSegment)) {
                collisionDetected = true;
                break;
            }
        }
        if (collisionDetected) break;
    }

    if (collisionDetected || !isInsideBoundary()) {
        revertToLastPosition();
    }
	// Vérifier également si les coins du robot sont à l'intérieur avec la marge
    sf::Vector2f topLeft = getTransformedPoint(-width / 2, -height / 2);
    sf::Vector2f topRight = getTransformedPoint(width / 2, -height / 2);
    sf::Vector2f bottomLeft = getTransformedPoint(-width / 2, height / 2);
    sf::Vector2f bottomRight = getTransformedPoint(width / 2, height / 2);

    if (!hexagon.isInside(topLeft.x - margin, topLeft.y - margin) ||
        !hexagon.isInside(topRight.x + margin, topRight.y - margin) ||
        !hexagon.isInside(bottomLeft.x - margin, bottomLeft.y + margin) ||
        !hexagon.isInside(bottomRight.x + margin, bottomRight.y + margin)) {
        revertToLastPosition();
    }
}






void Robot::draw(sf::RenderWindow& window) {
    window.draw(rectangleShape);

    for (auto& projectile : projectiles) {
        projectile.draw(window);
    }
}

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
    sf::Vector2f topLeft = getTransformedPoint(-width / 2, -height / 2);
    sf::Vector2f topRight = getTransformedPoint(width / 2, -height / 2);
    sf::Vector2f bottomLeft = getTransformedPoint(-width / 2, height / 2);
    sf::Vector2f bottomRight = getTransformedPoint(width / 2, height / 2);

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

void Robot::fire() {
    projectiles.emplace_back(position.x, position.y, orientation, 15.0f); 
}

void Robot::updateProjectiles(sf::RenderWindow& window, Robot& other) {
    for (auto& projectile : projectiles) {
        projectile.update();
    }

    // Supprimer les projectiles qui sont hors de l'écran
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [this, &other](const Projectile& projectile) {
                if (!hexagon.isInside(projectile.getPosition().x, projectile.getPosition().y)) {
                    return true;
                }
                if (other.get_Shape().getGlobalBounds().contains(projectile.getPosition())) {
                    other.setHealth(other.getHealth() - this->attackPower);
                    return true;
                }
                return false;
            }),
        projectiles.end()
    );
}
