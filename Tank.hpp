#ifndef TANK_HPP
#define TANK_HPP

#include "Robot.hpp"

class Tank : public Robot {
public:
    Tank(Arene& hex, float x, float y, char controlScheme, sf::Color color)
        : Robot(hex, x, y, controlScheme, color) {
            // Nouveaux attributs
            health = 200;
            speed = 2;
			attackPower=25;
			defense=40;

        // Charger la texture une seule fois
        if (!texture1.loadFromFile("tank.png")) {
            // Gestion de l'erreur si le chargement de la texture échoue
            printf("Problème chargement image Tank");
        }

        sprite1.setTexture(texture1);
        sprite1.setScale(0.25, 0.25);

        // Mise à jour des dimensions du sprite en fonction de la texture chargée et de l'échelle
        float textureWidth = texture1.getSize().x;
        float textureHeight = texture1.getSize().y;
        width = textureWidth * 0.25;
        height = textureHeight * 0.25;

        sprite1.setOrigin(textureWidth / 2, textureHeight / 2);
    }

    void draw(sf::RenderWindow& window) override;
	int getAttackPower() const { return attackPower; }
    const sf::Texture& getTexture() const { return texture1; }
    const sf::Sprite& getSprite() const { return sprite1; }


private:
    sf::Texture texture1;
    sf::Sprite sprite1;
};

#endif // TANK_HPP