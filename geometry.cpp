#include "geometry.hpp"

bool doLinesIntersect(const LineSegment& line1, const LineSegment& line2) {
    auto crossProduct = [](const sf::Vector2f& a, const sf::Vector2f& b) -> float {
        return a.x * b.y - a.y * b.x;
    };

    auto subtract = [](const sf::Vector2f& a, const sf::Vector2f& b) -> sf::Vector2f {
        return sf::Vector2f(a.x - b.x, a.y - b.y);
    };

    sf::Vector2f r = subtract(line1.p2, line1.p1);
    sf::Vector2f s = subtract(line2.p2, line2.p1);
    sf::Vector2f qp = subtract(line2.p1, line1.p1);

    float rxs = crossProduct(r, s);
    float qpxr = crossProduct(qp, r);

    if (rxs == 0 && qpxr == 0) {
        // Collinear
        return false;
    }

    if (rxs == 0 && qpxr != 0) {
        // Parallel and non-intersecting
        return false;
    }

    float t = crossProduct(qp, s) / rxs;
    float u = crossProduct(qp, r) / rxs;

    return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
}
