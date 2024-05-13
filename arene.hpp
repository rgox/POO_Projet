#ifndef ARENE_HPP
#define ARENE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Hexagone {
private:
    sf::Vector2f points[7];

public:
	Hexagone() {};
    Hexagone(int windowWidth, int windowHeight) {
        float size = std::min(windowWidth, windowHeight) * 0.5f; // Taille de l'hexagone à 80% de la taille de la fenêtre
        float centerX = windowWidth / 2.0f;
        float centerY = windowHeight / 2.0f;

        for (int i = 0; i < 6; ++i) {
            points[i].x = centerX + size * std::cos(i * 2 * M_PI / 6);
            points[i].y = centerY + size * std::sin(i * 2 * M_PI / 6);
        }
        // Fermer l'hexagone en connectant le dernier point au premier point
        points[6] = points[0];
    }
	Hexagone(Hexagone &hex){
		for (int i = 0; i < 7; ++i) {
			points[i] = hex.points[i];
		}


	}

    bool isInside(float x, float y) const ;

    void drawHexagon(sf::RenderWindow& window, const sf::Color& color) const ;

};

#endif // ARENE_HPP
