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
    int type;
    int apptime = 10;

public:
    Bonus(Hexagone& arene, const sf::RenderWindow& window) {
        // Générer une position aléatoire dans l'hexagone
        do {
            position.x = static_cast<float>(rand() % window.getSize().x); // Position x aléatoire dans les limites de la fenêtre
            position.y = static_cast<float>(rand() % window.getSize().y); // Position y aléatoire dans une fenêtre de 800x600
        } while (!arene.isInside(position.x, position.y));

        // Initialiser le type de bonus et la forme de manière aléatoire
        type = rand() % 4 + 1; // Types de bonus de 1 à 4
        int shapeType = rand() % 3; // Type de forme (0: cercle, 1: rectangle, 2: triangle)
        switch (shapeType) {
            case 0: // Cercle
                circleShape.setRadius(20);
                circleShape.setFillColor(sf::Color::Green);
                circleShape.setOutlineThickness(2);
                circleShape.setOutlineColor(sf::Color::Green);
                circleShape.setOrigin(20, 20); // Origine au centre du cercle
                circleShape.setPosition(position);
                shape = "cercle";
                break;
            case 1: // Rectangle
                rectangleShape.setSize(sf::Vector2f(40, 40));
                rectangleShape.setFillColor(sf::Color::Blue);
                rectangleShape.setOutlineThickness(2);
                rectangleShape.setOutlineColor(sf::Color::Blue);
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
                triangleShape.setOutlineColor(sf::Color::Red);
                triangleShape.setOrigin(20, 20); // Origine au centre du triangle
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

    void drawBonus(sf::RenderWindow& window) const {
        if (shape == "cercle") {
            window.draw(circleShape);
        } else if (shape == "rectangle") {
            window.draw(rectangleShape);
        } else if (shape == "triangle") {
            window.draw(triangleShape);
        }
    }

    sf::Vector2f getPosition() const { return position; }
};

#endif // BONUS_HPP
