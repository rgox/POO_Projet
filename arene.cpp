#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "arene.hpp"


//Methode qui vérifie si un point est à l'intérieur
bool Arene::isInside(float x, float y) const {
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

//Fonction qui dessine l'hexagone représentant l'arène
void Arene::drawHexagon(sf::RenderWindow& window, const sf::Color& color) const {
    sf::VertexArray lines(sf::LineStrip);
    for (int i = 0; i < 7; ++i) {
        lines.append(sf::Vertex(points[i], color));
    }
    window.draw(lines);
}


//Getter des limites de l'arène
std::vector<LineSegment> Arene::getHexagonSegments() const {
    std::vector<LineSegment> segments;
    for (int i = 0; i < 6; ++i) {
        segments.push_back({points[i], points[(i + 1) % 6]});
    }
    return segments;
}


//Getter du centre de l'Hexagone
sf::Vector2f Arene::getCenter() const {
    float centerX = 0;
    float centerY = 0;
    for (int i = 0; i < 6; ++i) {
        centerX += points[i].x;
        centerY += points[i].y;
    }
    centerX /= 6;
    centerY /= 6;
    return sf::Vector2f(centerX, centerY);
}

//Getter du rayon de l'hexagone
float Arene::getRadius() const {
    sf::Vector2f center = getCenter();
    return std::sqrt(std::pow(center.x - points[0].x, 2) + std::pow(center.y - points[0].y, 2));
}

