#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "arene.hpp"



bool Hexagone::isInside(float x, float y) const {
        // Initialiser le nombre de croisements
        int crossings = 0;

        // Ligne horizontale depuis le pixel vers la droite
        float startX = x;
        float endX = points[0].x;

        // Test de croisement avec chaque segment de l'hexagone
        for (size_t i = 0; i < 6; ++i) {
            float x1 = points[i].x;
            float y1 = points[i].y;
            float x2 = points[(i + 1) % 6].x;
            float y2 = points[(i + 1) % 6].y;

            // Vérifier si la ligne croise le segment
            if (((y1 <= y) && (y < y2)) || ((y2 <= y) && (y < y1))) {
                float xIntersection = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
                if (xIntersection >= startX && xIntersection <= endX) {
                    crossings++;
                }
            }
        }

        // Vérifier si le nombre de croisements est impair
        return (crossings % 2 == 1);
    }

void Hexagone::drawHexagon(sf::RenderWindow& window, const sf::Color& color) const {
    sf::VertexArray lines(sf::LineStrip);
    for (int i = 0; i < 7; ++i) {
        lines.append(sf::Vertex(points[i], color));
    }
    window.draw(lines);
	
}
