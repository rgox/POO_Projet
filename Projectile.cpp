#include "Projectile.hpp"

Projectile::Projectile(float x, float y, float speed, float orientation) 
	: x(x), y(y), angle(orientation), speed(speed){
    if (!texture.loadFromFile("projectile.png")) {
        // Handle error if texture loading fails
        printf("Failed to load projectile image");
        return;
    }

    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    // Scale the image down by 4
    sprite.setScale(0.125f, 0.125f);

    // Center the sprite's origin
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);

    // Apply rotation based on the robot's orientation
    sprite.setRotation(orientation * 180 / M_PI); // Convert orientation from radians to degrees

    // Set the velocity using the orientation
    velocity.x = speed * std::cos(orientation);
    velocity.y = speed * std::sin(orientation);
}

void Projectile::update() {
    sprite.move(velocity);
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Projectile::getPosition() const {
    return sprite.getPosition();
}

bool Projectile::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = sprite.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

bool Projectile::isTouchingBorder(const sf::RenderWindow& window) const {
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return pos.x - bounds.width / 2 <= 0 || pos.x + bounds.width / 2 >= window.getSize().x || 
           pos.y - bounds.height / 2 <= 0 || pos.y + bounds.height / 2 >= window.getSize().y;
}
