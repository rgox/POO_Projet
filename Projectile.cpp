#include "Projectile.hpp"

//Constructeur
Projectile::Projectile(float x, float y, float angle, float speed) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);

	
    velocity.x = speed * cos(angle);
    velocity.y = speed * sin(angle);
}


//Mets à jour la position du projectile en fonction de sa vitesse
void Projectile::update() {
    shape.move(velocity);
}

//Dessine le projectile
void Projectile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

//Retourne les points de atteints par l'image
sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
} 

//Retourne la position de la forme
sf::Vector2f Projectile::getPosition() const {
    return shape.getPosition();
}

//Détecte si le projectile est en dehors de l'écran
bool Projectile::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = shape.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

//Détecte si le missile touche le bord de l'image ou pas 
bool Projectile::isTouchingBorder(const sf::RenderWindow& window) const {
    sf::Vector2f pos = shape.getPosition();
    float radius = shape.getRadius();
    return pos.x - radius <= 0 || pos.x + radius >= window.getSize().x || pos.y - radius <= 0 || pos.y + radius >= window.getSize().y;
}
