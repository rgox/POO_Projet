#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib> // Pour rand et srand
#include <ctime>   // Pour time
#include "arene.hpp"

class Bonus {
private:
    sf::Vector2f position;
    sf::CircleShape circleShape;
    sf::RectangleShape rectangleShape;
    sf::ConvexShape triangleShape;
    std::string shape;
    int type = rand() % 4 + 1;
    int value = rand() % 10 + 1;
    int apptime = 10;

public:
    Bonus(Hexagone& arene,const sf::RenderWindow& window) {
        // Initialiser le générateur de nombres pseudo-aléatoires avec le temps actuel
        srand(static_cast<unsigned int>(time(nullptr)));

        // Générer une position aléatoire dans l'hexagone
        do {
            position.x = static_cast<float>(rand() % window.getSize().x); // Position x aléatoire dans les limites de la fenêtre
            position.y = static_cast<float>(rand() % window.getSize().y); // Position y aléatoire dans une fenêtre de 800x600
        } while (!arene.isInside(position.x, position.y));

        // Créer une forme aléatoire (dans cet exemple, un cercle, un rectangle ou un triangle)
        int shapeType = rand() % 3;
        switch (shapeType) {
            case 0: // Cercle
                circleShape.setRadius(20);
                circleShape.setFillColor(sf::Color::Green);
                circleShape.setOutlineThickness(2);
                circleShape.setOutlineColor(sf::Color::Black);
                circleShape.setOrigin(20, 20); // Origine au centre du cercle
                circleShape.setPosition(position);
                shape = "cercle";
                break;
            case 1: // Rectangle
                rectangleShape.setSize(sf::Vector2f(40, 40));
                rectangleShape.setFillColor(sf::Color::Blue);
                rectangleShape.setOutlineThickness(2);
                rectangleShape.setOutlineColor(sf::Color::Black);
                rectangleShape.setOrigin(20, 20); // Origine au centre du rectangle
                rectangleShape.setPosition(position);
                shape = "rectangle";
                break;
            case 2: // Triangle
                triangleShape.setPointCount(3);
                triangleShape.setPoint(0, sf::Vector2f(0, -20));
                triangleShape.setPoint(1, sf::Vector2f(20, 20));
                triangleShape.setPoint(2, sf::Vector2f(-20, 20));
                triangleShape.setFillColor(sf::Color::Red);
                triangleShape.setOutlineThickness(2);
                triangleShape.setOutlineColor(sf::Color::Black);
                triangleShape.setOrigin(0, 0); // Origine au centre du triangle
                triangleShape.setPosition(position);
                shape = "triangle";
                break;
        }
    }

    // Getters pour les formes
    const sf::CircleShape& getCircleShape() const { return circleShape; }
    const sf::RectangleShape& getRectangleShape() const { return rectangleShape; }
    const sf::ConvexShape& getTriangleShape() const { return triangleShape; }
    const std::string& getShape() const { return shape; }

    // Getters pour les propriétés du bonus
    int getBonusType() const { return type; }
    int getValue() const { return value; }

    void drawBonus(sf::RenderWindow& window) const {
        if (circleShape.getRadius() != 0) {
            window.draw(circleShape);
        } else if (rectangleShape.getSize() != sf::Vector2f(0, 0)) {
            window.draw(rectangleShape);
        } else {
            window.draw(triangleShape);
        }
    }

    sf::Vector2f getPosition() const { return position; }
};

#endif // BONUS_HPP
