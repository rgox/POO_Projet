#include "Projectile.hpp"

sf::Texture Projectile::texture;

//constructeur
Projectile::Projectile(float x, float y, float speed, float orientation) 
    : x(x), y(y), angle(orientation), speed(speed) {
    
    //utilise la texture static
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    sprite.setScale(0.125f, 0.125f);

    
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);

    
    sprite.setRotation(orientation * 180 / M_PI); 

    velocity.x = speed * std::cos(orientation);
    velocity.y = speed * std::sin(orientation);
}

bool Projectile::loadTexture() {
    if (!texture.loadFromFile("projectile.png")) {
        // Handle error if texture loading fails
        printf("Failed to load projectile image");
        return false;
    }
    return true;
}

//Mets à jour la position du projectile en fonction de sa vitesse
void Projectile::update() {
    sprite.move(velocity);
}

//Dessine le projectile
void Projectile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

//Retourne les points de atteints par l'image
sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}

//Retourne la position de la forme
sf::Vector2f Projectile::getPosition() const {
    return sprite.getPosition();
}

//Détecte si le projectile est en dehors de l'écran
bool Projectile::isOffScreen(const sf::RenderWindow& window) const {
    sf::Vector2f pos = sprite.getPosition();
    return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
}

//Détecte si le missile touche le bord de l'image ou pas 
bool Projectile::isTouchingBorder(const sf::RenderWindow& window) const {
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return pos.x - bounds.width / 2 <= 0 || pos.x + bounds.width / 2 >= window.getSize().x || 
           pos.y - bounds.height / 2 <= 0 || pos.y + bounds.height / 2 >= window.getSize().y;
}
