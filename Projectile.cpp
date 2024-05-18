#include "Projectile.hpp"

Projectile::Projectile(float x, float y, float angle, float speed) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);

    velocity.x = speed * cos(angle);
    velocity.y = speed * sin(angle);
}

void Projectile::update() {
    shape.move(velocity);
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
} 

sf::Vector2f Projectile::getPosition() const {
    return shape.getPosition();
}

bool Projectile::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = shape.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

bool Projectile::isTouchingBorder(const sf::RenderWindow& window) const {
    sf::Vector2f pos = shape.getPosition();
    float radius = shape.getRadius();
    return pos.x - radius <= 0 || pos.x + radius >= window.getSize().x || pos.y - radius <= 0 || pos.y + radius >= window.getSize().y;
}
