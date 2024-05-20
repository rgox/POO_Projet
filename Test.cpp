#include "Test.hpp"
#include <boost/test/unit_test.hpp>
#include "arene.hpp"
#include "bonus.hpp"
#include "Course.hpp"
#include "Tank.hpp"
#include "Sniper.hpp"
#include "Robot.hpp"

TestSuite::TestSuite() {
    // Initialisation de la suite de tests si nécessaire
}

TestSuite::~TestSuite() {
    // Nettoyage si nécessaire
}

void TestSuite::runTests() {
    // Lancer les tests, cette méthode sera complétée avec des tests spécifiques pour chaque classe
}

// Déclaration des tests pour Boost.Test
BOOST_AUTO_TEST_SUITE(GameTestSuite)


  // ########################## TEST CLASSE ARENE ######################################################""
// Test de la méthode isInside
BOOST_AUTO_TEST_CASE(testIsInside) {
    Arene arene(200, 200);
    BOOST_CHECK(arene.isInside(100, 100));  // Point à l'intérieur
    BOOST_CHECK(!arene.isInside(0, 0));     // Point à l'extérieur
}

// Test de la méthode getCenter
BOOST_AUTO_TEST_CASE(testGetCenter) {
    Arene arene(200, 200);
    sf::Vector2f center = arene.getCenter();
    BOOST_CHECK_CLOSE(center.x, 100.0f, 0.1);
    BOOST_CHECK_CLOSE(center.y, 100.0f, 0.1);
}

// Test de la méthode getRadius
BOOST_AUTO_TEST_CASE(testGetRadius) {
    Arene arene(200, 200);
    float radius = arene.getRadius();
    sf::Vector2f center = arene.getCenter();
    sf::Vector2f point = arene.getPoint(0);
    float expectedRadius = std::sqrt(std::pow(center.x - point.x, 2) + std::pow(center.y - point.y, 2));
    BOOST_CHECK_CLOSE(radius, expectedRadius, 0.1);
}

// Test de la méthode getHexagonSegments
BOOST_AUTO_TEST_CASE(testGetHexagonSegments) {
    Arene arene(200, 200);
    std::vector<LineSegment> segments = arene.getHexagonSegments();
    BOOST_CHECK_EQUAL(segments.size(), 6);
    for (int i = 0; i < 6; ++i) {
        BOOST_CHECK(segments[i].p1 == arene.getPoint(i));
        BOOST_CHECK(segments[i].p2 == arene.getPoint((i + 1) % 6));
    }
}

//#############################################" TEST CLASSE BONUS" ############################################"""

BOOST_AUTO_TEST_CASE(testBonusCreation) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Bonus bonus(arene, window);

    // Vérifier que la position est à l'intérieur de l'arène
    sf::Vector2f position = bonus.getPosition();
    BOOST_CHECK(arene.isInside(position.x, position.y));

    // Vérifier le type de bonus
    int bonusType = bonus.getBonusType();
    BOOST_CHECK(bonusType >= 1 && bonusType <= 4);

    // Vérifier la forme du bonus
    std::string shape = bonus.getShape();
    BOOST_CHECK(shape == "cercle" || shape == "rectangle" || shape == "triangle");

    // Vérifier les formes spécifiques
    if (shape == "cercle") {
        const sf::CircleShape& circleShape = bonus.getCircleShape();
        BOOST_CHECK(circleShape.getRadius() == 20);
        BOOST_CHECK(circleShape.getFillColor() == sf::Color::Green);
    } else if (shape == "rectangle") {
        const sf::RectangleShape& rectangleShape = bonus.getRectangleShape();
        BOOST_CHECK(rectangleShape.getSize() == sf::Vector2f(40, 40));
        BOOST_CHECK(rectangleShape.getFillColor() == sf::Color::Blue);
    } else if (shape == "triangle") {
        const sf::ConvexShape& triangleShape = bonus.getTriangleShape();
        BOOST_CHECK(triangleShape.getPointCount() == 3);
        BOOST_CHECK(triangleShape.getFillColor() == sf::Color::Red);
    }
}

// Test des getters de la classe Bonus
BOOST_AUTO_TEST_CASE(testBonusGetters) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Bonus bonus(arene, window);

    // Vérifier la forme du bonus
    std::string shape = bonus.getShape();
    if (shape == "cercle") {
        const sf::CircleShape& circleShape = bonus.getCircleShape();
        BOOST_CHECK(circleShape.getRadius() == 20);
        BOOST_CHECK(circleShape.getFillColor() == sf::Color::Green);
    } else if (shape == "rectangle") {
        const sf::RectangleShape& rectangleShape = bonus.getRectangleShape();
        BOOST_CHECK(rectangleShape.getSize() == sf::Vector2f(40, 40));
        BOOST_CHECK(rectangleShape.getFillColor() == sf::Color::Blue);
    } else if (shape == "triangle") {
        const sf::ConvexShape& triangleShape = bonus.getTriangleShape();
        BOOST_CHECK(triangleShape.getPointCount() == 3);
        BOOST_CHECK(triangleShape.getFillColor() == sf::Color::Red);
    }

    // Vérifier les getters pour les propriétés du bonus
    int bonusType = bonus.getBonusType();
    BOOST_CHECK(bonusType >= 1 && bonusType <= 4);

    sf::Vector2f position = bonus.getPosition();
    BOOST_CHECK(arene.isInside(position.x, position.y));
}

// Test de la méthode drawBonus de la classe Bonus
BOOST_AUTO_TEST_CASE(testDrawBonus) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Bonus bonus(arene, window);

    // Vérifier que la méthode drawBonus ne cause pas d'erreur
    BOOST_CHECK_NO_THROW(bonus.drawBonus(window));
}

//###################################### TEST CLASSE COURSE #########################################

// Test de la classe Course
BOOST_AUTO_TEST_CASE(testCourseInitialization) {
    Arene arene(200, 200);

    // Création d'un objet Course
    Course course(arene, 100, 100, 'A', sf::Color::Red);

    // Vérifier les attributs hérités
    BOOST_CHECK_EQUAL(course.getHealth(), 100);
    BOOST_CHECK_EQUAL(course.getSpeed(), 15);
    BOOST_CHECK_EQUAL(course.getAttackPower(), 25);
    BOOST_CHECK_EQUAL(course.getDefense(), 25);

    // Vérifier la texture et le sprite
    BOOST_CHECK(course.getTexture().getSize().x > 0);
    BOOST_CHECK(course.getTexture().getSize().y > 0);
    BOOST_CHECK_CLOSE(course.getSprite().getScale().x, 0.25f, 0.1);
    BOOST_CHECK_CLOSE(course.getSprite().getScale().y, 0.25f, 0.1);
}

// Test de la méthode draw de la classe Course
BOOST_AUTO_TEST_CASE(testCourseDraw) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Course course(arene, 100, 100, 'A', sf::Color::Red);

    // Vérifier que la méthode draw ne cause pas d'erreur (test visuel impossible)
    BOOST_CHECK_NO_THROW(course.draw(window));
}

//###################################### TEST CLASSE TANK #########################################

// Test de la classe Tank
BOOST_AUTO_TEST_CASE(testTankInitialization) {
    Arene arene(200, 200);

    // Création d'un objet Course
    Tank tank(arene, 100, 100, 'A', sf::Color::Red);

    // Vérifier les attributs hérités
    BOOST_CHECK_EQUAL(tank.getHealth(), 200);
    BOOST_CHECK_EQUAL(tank.getSpeed(), 2);
    BOOST_CHECK_EQUAL(tank.getAttackPower(), 25);
    BOOST_CHECK_EQUAL(tank.getDefense(), 40);

    // Vérifier la texture et le sprite
    BOOST_CHECK(tank.getTexture().getSize().x > 0);
    BOOST_CHECK(tank.getTexture().getSize().y > 0);
    BOOST_CHECK_CLOSE(tank.getSprite().getScale().x, 0.25f, 0.1);
    BOOST_CHECK_CLOSE(tank.getSprite().getScale().y, 0.25f, 0.1);
}

// Test de la méthode draw de la classe Tank
BOOST_AUTO_TEST_CASE(testTankDraw) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Tank tank(arene, 100, 100, 'A', sf::Color::Red);

    // Vérifier que la méthode draw ne cause pas d'erreur (test visuel impossible)
    BOOST_CHECK_NO_THROW(tank.draw(window));
}


//###################################### TEST CLASSE SNIPER #########################################

// Test de la classe Sniper
BOOST_AUTO_TEST_CASE(testSniperInitialization) {
    Arene arene(200, 200);

    // Création d'un objet Course
    Sniper sniper(arene, 100, 100, 'A', sf::Color::Red);

    // Vérifier les attributs hérités
    BOOST_CHECK_EQUAL(sniper.getHealth(), 100);
    BOOST_CHECK_EQUAL(sniper.getSpeed(), 5);
    BOOST_CHECK_EQUAL(sniper.getAttackPower(), 50);
    BOOST_CHECK_EQUAL(sniper.getDefense(), 10);

    // Vérifier la texture et le sprite
    BOOST_CHECK(sniper.getTexture().getSize().x > 0);
    BOOST_CHECK(sniper.getTexture().getSize().y > 0);
    BOOST_CHECK_CLOSE(sniper.getSprite().getScale().x, 0.25f, 0.1);
    BOOST_CHECK_CLOSE(sniper.getSprite().getScale().y, 0.25f, 0.1);
}

// Test de la méthode draw de la classe Snaiper
BOOST_AUTO_TEST_CASE(testSnaiperDraw) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Sniper sniper(arene, 100, 100, 'A', sf::Color::Red);

    // Vérifier que la méthode draw ne cause pas d'erreur (test visuel impossible)
    BOOST_CHECK_NO_THROW(sniper.draw(window));
}

//########################################## TEST CLASSE ROBOT #################################################

BOOST_AUTO_TEST_CASE(testRobotSettersGetters) {
    Arene arene(200, 200);
    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Test des setters et getters
    robot.setPosition(150, 150);
    BOOST_CHECK_EQUAL(robot.getX(), 150);
    BOOST_CHECK_EQUAL(robot.getY(), 150);

    robot.setHealth(80);
    BOOST_CHECK_EQUAL(robot.getHealth(), 80);

    robot.setSpeed(20);
    BOOST_CHECK_EQUAL(robot.getSpeed(), 20);

    robot.setDefense(30);
    BOOST_CHECK_EQUAL(robot.getDefense(), 30);

    robot.set_Orientation(1.5f);
    BOOST_CHECK_CLOSE(robot.getOrientation(), 1.5f, 0.1);
}

BOOST_AUTO_TEST_CASE(testRobotMovement) {
    Arene arene(200, 200);
    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Vérifiez que la vitesse est bien définie
    robot.setSpeed(10);

    // Test des mouvements
    robot.set_Orientation(0);  // Orientation vers la droite
    robot.moveForward();
    BOOST_CHECK_CLOSE(robot.getX(), 110.0f, 0.1);

    robot.moveBackward();
    BOOST_CHECK_CLOSE(robot.getX(), 100.0f, 0.1);

    robot.rotateLeft();
    BOOST_CHECK_CLOSE(robot.getOrientation(), -0.1f, 0.1);

    robot.rotateRight();
    BOOST_CHECK_CLOSE(robot.getOrientation(), 0.0f, 0.1);
}

BOOST_AUTO_TEST_CASE(testRobotCollision) {
    Arene arene(200, 200);
    Course robot1(arene, 100, 100, 'A', sf::Color::Blue);
    Course robot2(arene, 110, 100, 'B', sf::Color::Red);

    // Test de la collision
    BOOST_CHECK(robot1.checkCollision(robot2));

    robot2.setPosition(200, 200);
    BOOST_CHECK(!robot1.checkCollision(robot2));
}

BOOST_AUTO_TEST_CASE(testRobotFire) {
    Arene arene(200, 200);
    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Test du tir de projectiles
    BOOST_CHECK_EQUAL(robot.getProjectiles().size(), 0);

    robot.fire();
    BOOST_CHECK_EQUAL(robot.getProjectiles().size(), 1);
}

BOOST_AUTO_TEST_CASE(testRobotDraw) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Vérifier que la méthode draw ne cause pas d'erreur (test visuel impossible)
    BOOST_CHECK_NO_THROW(robot.draw(window));
}

BOOST_AUTO_TEST_SUITE_END()