#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "arene.hpp"



// Définition de l'instance par défaut
Hexagone::Hexagone() {
    float windowWidth = 1920;
    float windowHeight = 1080;
    float radius = std::min(windowWidth, windowHeight) * 0.5f; // 50% of the smallest dimension
    float centerX = windowWidth / 2.0f;
    float centerY = windowHeight / 2.0f;

    for (int i = 0; i < 6; ++i) {
        points[i].x = centerX + radius * cos(i * 2 * M_PI / 6);
        points[i].y = centerY + radius * sin(i * 2 * M_PI / 6);
    }
    points[6] = points[0]; // Close the hexagon
}

// Définition de l'instance par défaut
Hexagone Hexagone::defaultInstance;

bool Hexagone::isInside(float x, float y) const {
    int crossings = 0;
    for (size_t i = 0; i < 6; ++i) {
        float x1 = points[i].x;
        float y1 = points[i].y;
        float x2 = points[(i + 1) % 6].x;
        float y2 = points[(i + 1) % 6].y;

        bool cond1 = (y1 <= y && y < y2);
        bool cond2 = (y2 <= y && y < y1);
        if (cond1 || cond2) {
            float xIntersection = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
            if (x <= xIntersection) {
                crossings++;
            }
        }
    }
    return crossings % 2 != 0;
}

void Hexagone::drawHexagon(sf::RenderWindow& window, const sf::Color& color) const {
    sf::VertexArray lines(sf::LineStrip);
    for (int i = 0; i < 7; ++i) {
        lines.append(sf::Vertex(points[i], color));
    }
    window.draw(lines);
}
