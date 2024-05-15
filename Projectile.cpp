#include "Projectile.hpp"

Projectile::Projectile(float x, float y, float angle, float speed) {
    shape.setRadius(5);
    shape.setFillColor(sf::Color::Yellow);
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

bool Projectile::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = shape.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}
