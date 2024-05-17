#include <algorithm>
#include <cmath>
#include "Robot.hpp"
#include <cmath>

// Constructeur

Robot::Robot(Hexagone hex, float x, float y, char controlScheme, sf::Color color)
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
Robot& Robot::operator=( Robot* other) {
    if (this != other) {
        //On copie chaque attribut de l'objet passé en argument
		hexagon=other->hexagon;
    	position=other->position;
    	health=other->health;       // Santé actuelle du robot
    	speed=other->speed;      // Vitesse de déplacement du robot
    	attackPower=other->attackPower;  // Puissance d'attaque
    	defense=other->defense;      // Capacité de défense
		lastPosX=other->lastPosX;
		lastPosY=other->lastPosY;
		rectangleShape=other->rectangleShape;
		controlScheme=other->controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
		color=other->color;
		width = other->width;   // Largeur du robot, à adapter selon votre setup
    	height = other->height;  // Hauteur du robot, à adapter selon votre setup
		lastValidPosition=other->lastValidPosition;
		orientation=other->orientation; // Angle en radians
        
    }
    return *this;
}
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
		correctPosition();
    }
}

void Robot::moveBackward() {
    float newX = position.x - speed * std::cos(orientation);
    float newY = position.y - speed * std::sin(orientation);
    if (canMove(newX, newY)) {
        position.x = newX;
        position.y = newY;
        rectangleShape.setPosition(position);
		correctPosition();
    }
}

bool Robot::isInsideBoundary() {
    const float margin = 5.0f; // Marge de sécurité en pixels

    // Vérifier toutes les coins du rectangle avec l'orientation
    sf::Transform transform;
    transform.rotate(orientation * 180 / M_PI, position);

    // Calculer les coins du rectangle après transformation
    sf::Vector2f topLeft = transform.transformPoint(sf::Vector2f(position.x - width / 2, position.y - height / 2));
    sf::Vector2f topRight = transform.transformPoint(sf::Vector2f(position.x + width / 2, position.y - height / 2));
    sf::Vector2f bottomLeft = transform.transformPoint(sf::Vector2f(position.x - width / 2, position.y + height / 2));
    sf::Vector2f bottomRight = transform.transformPoint(sf::Vector2f(position.x + width / 2, position.y + height / 2));

    // Vérifier si les coins sont à l'intérieur de l'hexagone
    return hexagon.isInside(topLeft.x, topLeft.y) &&
           hexagon.isInside(topRight.x, topRight.y) &&
           hexagon.isInside(bottomLeft.x, bottomLeft.y) &&
           hexagon.isInside(bottomRight.x, bottomRight.y);
}

void Robot::rotateLeft() {
    float oldOrientation = orientation; // Sauvegarder l'ancienne orientation
    orientation -= 0.1f; // Ajuster cette valeur pour la vitesse de rotation
    rectangleShape.setRotation(orientation * 180 / M_PI);

    if (!isInsideBoundary()) {
        orientation = oldOrientation; // Réinitialiser à l'ancienne orientation si on sort des limites
        rectangleShape.setRotation(orientation * 180 / M_PI);
    }
}

void Robot::rotateRight() {
    float oldOrientation = orientation; // Sauvegarder l'ancienne orientation
    orientation += 0.1f; // Ajuster cette valeur pour la vitesse de rotation
    rectangleShape.setRotation(orientation * 180 / M_PI);

    if (!isInsideBoundary()) {
        orientation = oldOrientation; // Réinitialiser à l'ancienne orientation si on sort des limites
        rectangleShape.setRotation(orientation * 180 / M_PI);
    }
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

    // Vérifier toutes les coins du rectangle avec l'orientation
    sf::Transform transform;
    transform.rotate(orientation * 180 / M_PI, pos);

    // Calculer les coins du rectangle après transformation
    sf::Vector2f topLeft = transform.transformPoint(sf::Vector2f(pos.x - width / 2, pos.y - height / 2));
    sf::Vector2f topRight = transform.transformPoint(sf::Vector2f(pos.x + width / 2, pos.y - height / 2));
    sf::Vector2f bottomLeft = transform.transformPoint(sf::Vector2f(pos.x - width / 2, pos.y + height / 2));
    sf::Vector2f bottomRight = transform.transformPoint(sf::Vector2f(pos.x + width / 2, pos.y + height / 2));

    // Vérifier si les coins sont à l'intérieur de l'hexagone
    bool inside = hexagon.isInside(topLeft.x, topLeft.y) &&
                  hexagon.isInside(topRight.x, topRight.y) &&
                  hexagon.isInside(bottomLeft.x, bottomLeft.y) &&
                  hexagon.isInside(bottomRight.x, bottomRight.y);

    if (!inside) {
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
    rectangleShape.setPosition(position);
    rectangleShape.setRotation(orientation * 180 / M_PI);
    window.draw(rectangleShape);

	// Dessiner les points de débogage
    drawDebugPoints(window);
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

void Robot::correctPosition() {
    const float margin = 5.0f; // Marge de sécurité en pixels

    // Vérifier toutes les coins du rectangle avec l'orientation
    sf::Transform transform;
    transform.rotate(orientation * 180 / M_PI, position);

    // Calculer les coins du rectangle après transformation
    sf::Vector2f topLeft = transform.transformPoint(sf::Vector2f(position.x - width / 2, position.y - height / 2));
    sf::Vector2f topRight = transform.transformPoint(sf::Vector2f(position.x + width / 2, position.y - height / 2));
    sf::Vector2f bottomLeft = transform.transformPoint(sf::Vector2f(position.x - width / 2, position.y + height / 2));
    sf::Vector2f bottomRight = transform.transformPoint(sf::Vector2f(position.x + width / 2, position.y + height / 2));

    // Ajuster la position pour ramener les coins à l'intérieur de l'hexagone
    if (!hexagon.isInside(topLeft.x, topLeft.y)) {
        position.x += margin;
        position.y += margin;
    }
    if (!hexagon.isInside(topRight.x, topRight.y)) {
        position.x -= margin;
        position.y += margin;
    }
    if (!hexagon.isInside(bottomLeft.x, bottomLeft.y)) {
        position.x += margin;
        position.y -= margin;
    }
    if (!hexagon.isInside(bottomRight.x, bottomRight.y)) {
        position.x -= margin;
        position.y -= margin;
    }
}
