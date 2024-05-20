#ifndef SNIPER_HPP
#define SNIPER_HPP

#include "Robot.hpp"

class Sniper : public Robot {
public:
    Sniper(Hexagone& hex, float x, float y, char controlScheme, sf::Color color)
        : Robot(hex, x, y, controlScheme, color) {
        // Ajustez les attributs existants ici si nécessaire
        health = 100;
            speed = 5;
			attackPower=50;
			defense=10;

        // Charger la texture une seule fois
        if (!texture1.loadFromFile("sniper.png")) {
            // Gestion de l'erreur si le chargement de la texture échoue
            printf("Problème chargement image Sniper");
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

    void draw(sf::RenderWindow& window) override {
        sprite1.setPosition(position);
        sprite1.setRotation(orientation * 180 / M_PI);
        window.draw(sprite1);
    }

private:
    sf::Texture texture1;
    sf::Sprite sprite1;
};

#endif // SNIPER_HPP
