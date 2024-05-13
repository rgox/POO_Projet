#ifndef ARENE_HPP
#define ARENE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Hexagone {
private:
    sf::Vector2f points[7];

public:
    Hexagone(int windowWidth, int windowHeight) {
		float radius = std::min(windowWidth, windowHeight) * 0.5f; // 50% of the smallest dimension
		float centerX = windowWidth / 2.0f;
		float centerY = windowHeight / 2.0f;

		for (int i = 0; i < 6; ++i) {
			points[i].x = centerX + radius * cos(i * 2 * M_PI / 6);
			points[i].y = centerY + radius * sin(i * 2 * M_PI / 6);
		}
		points[6] = points[0]; // Close the hexagon
	}

    bool isInside(float x, float y) const ;

    void drawHexagon(sf::RenderWindow& window, const sf::Color& color) const ;

	// Ajout pour récupérer un point spécifique
    sf::Vector2f getPoint(int index) const {
        if (index >= 0 && index < 6) {
            return points[index];
        }
        return sf::Vector2f(0, 0); // Retourne un point nul si l'index est hors limites
    }

};

#endif // ARENE_HPP
