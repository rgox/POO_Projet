#include "Test.hpp"
#include <algorithm>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "arene.hpp"
#include "bonus.hpp"
#include "Course.hpp"
#include "Tank.hpp"
#include "Sniper.hpp"
#include "Robot.hpp"
#include "affichage.hpp"
#include <SFML/System/String.hpp>
#include <iostream>
#include "geometry.hpp"
#include "Init.hpp"
#include "Projectile.hpp"


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

	sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
	robot.set_name("TestName", font);
    BOOST_CHECK_EQUAL(robot.get_name().getString().toAnsiString(), "TestName");

    robot.setNamePosition(200, 200);
    BOOST_CHECK_EQUAL(robot.get_name_draw().getPosition().x, 200);
    BOOST_CHECK_EQUAL(robot.get_name_draw().getPosition().y, 200);

    BOOST_CHECK_EQUAL(robot.getWidth(), 77);
    BOOST_CHECK_EQUAL(robot.getHeight(), 36);
    BOOST_CHECK_EQUAL(robot.getControlScheme(), 'A');
    BOOST_CHECK(!robot.getLineSegments().empty());
    BOOST_CHECK(robot.get_Shape().getSize().x > 0);
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
BOOST_AUTO_TEST_CASE(testRobotBoundaryHandling) {
    Arene arene(200, 200);
    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Test de isInsideBoundary
    BOOST_CHECK(robot.isInsideBoundary());

    // Test de isTouchingBoundary
    robot.setPosition(10, 10); // Mettez la position près du bord pour toucher la limite
    BOOST_CHECK(robot.isTouchingBoundary());

    // Test de repositionToCenter
    robot.repositionToCenter();
    BOOST_CHECK(robot.getX() > 0 && robot.getX() < 200);
    BOOST_CHECK(robot.getY() > 0 && robot.getY() < 200);
}

BOOST_AUTO_TEST_CASE(testRobotCollisionHandling) {
    Arene arene(200, 200);
    Course robot1(arene, 100, 100, 'A', sf::Color::Blue);
    Course robot2(arene, 110, 100, 'B', sf::Color::Red);

    // Test de handleCollision
    robot1.handleCollision(robot2);
    BOOST_CHECK(robot1.getX() != 100 || robot1.getY() != 100);
    BOOST_CHECK(robot2.getX() != 110 || robot2.getY() != 100);
}

BOOST_AUTO_TEST_CASE(testRobotSaveAndRevert) {
    Arene arene(200, 200);
    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Test de saveLastPosition et revertToLastPosition
    robot.saveLastPosition();
    robot.setPosition(150, 150);
    robot.revertToLastPosition();
    BOOST_CHECK_EQUAL(robot.getX(), 100);
    BOOST_CHECK_EQUAL(robot.getY(), 100);

    // Test de saveLastOrientation et revertToLastOrientation
    robot.saveLastOrientation();
    robot.set_Orientation(1.0f);
    robot.revertToLastOrientation();
    BOOST_CHECK_CLOSE(robot.getOrientation(), 0.0f, 0.1);
}

BOOST_AUTO_TEST_CASE(testRobotDrawDebugPoints) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    Arene arene(200, 200);

    Course robot(arene, 100, 100, 'A', sf::Color::Blue);

    // Vérifier que la méthode drawDebugPoints ne cause pas d'erreur (test visuel impossible)
    BOOST_CHECK_NO_THROW(robot.drawDebugPoints(window));
}

//#################################### TEST CLASSE AFFICHAGE ###############################################

BOOST_AUTO_TEST_CASE(testAfficheConstructor) {
    Arene arene(800, 600);
    Course robot1(arene, 100, 100, 'A', sf::Color::Blue);
    Course robot2(arene, 200, 200, 'B', sf::Color::Red);

    BOOST_CHECK_NO_THROW(Affiche affiche(arene, robot1, robot2));
}



BOOST_AUTO_TEST_CASE(testAfficheUpdateControls) {
    Arene arene(800, 600);
    Course robot1(arene, 100, 100, 'A', sf::Color::Blue);
    Course robot2(arene, 200, 200, 'B', sf::Color::Red);
    Affiche affiche(arene, robot1, robot2);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    // Simulate key press
    robot1.setSpeed(10);
    sf::Keyboard::Key key = sf::Keyboard::Up;
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = key;

    // Test moveForward
    window.pollEvent(event);
    affiche.updateControls(robot1);
    BOOST_CHECK_EQUAL(robot1.getX(), 100);
    BOOST_CHECK_EQUAL(robot1.getY(), 100);

    // Reset position for other tests
    robot1.setPosition(100, 100);
    key = sf::Keyboard::Left;
    event.key.code = key;

    // Test rotateLeft
    window.pollEvent(event);
    affiche.updateControls(robot1);
    BOOST_CHECK_EQUAL(robot1.getOrientation(), 0);
}

BOOST_AUTO_TEST_CASE(testAfficheShowEndMessage) {
    Arene arene(800, 600);
    Course robot1(arene, 100, 100, 'A', sf::Color::Blue);
    Course robot2(arene, 200, 200, 'B', sf::Color::Red);
    Affiche affiche(arene, robot1, robot2);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");

    BOOST_CHECK_NO_THROW(affiche.showEndMessage(window, "Player 1"));
}

// ########################################## TEST CLASSE GEOMETRY #################################################

BOOST_AUTO_TEST_CASE(testCrossProduct) {
    sf::Vector2f a(1, 2);
    sf::Vector2f b(3, 4);
    float result = crossProduct(a, b);
    BOOST_CHECK_CLOSE(result, -2.0f, 0.1);
}

BOOST_AUTO_TEST_CASE(testSubtract) {
    sf::Vector2f a(5, 6);
    sf::Vector2f b(3, 4);
    sf::Vector2f result = subtract(a, b);
    BOOST_CHECK_EQUAL(result.x, 2.0f);
    BOOST_CHECK_EQUAL(result.y, 2.0f);
}

BOOST_AUTO_TEST_CASE(testDoLinesIntersect_Intersecting) {
    LineSegment line1 = { sf::Vector2f(0, 0), sf::Vector2f(4, 4) };
    LineSegment line2 = { sf::Vector2f(0, 4), sf::Vector2f(4, 0) };
    bool result = doLinesIntersect(line1, line2);
    BOOST_CHECK(result);
}

BOOST_AUTO_TEST_CASE(testDoLinesIntersect_NonIntersecting) {
    LineSegment line1 = { sf::Vector2f(0, 0), sf::Vector2f(2, 2) };
    LineSegment line2 = { sf::Vector2f(3, 3), sf::Vector2f(5, 5) };
    bool result = doLinesIntersect(line1, line2);
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE(testDoLinesIntersect_Parallel) {
    LineSegment line1 = { sf::Vector2f(0, 0), sf::Vector2f(2, 2) };
    LineSegment line2 = { sf::Vector2f(1, 1), sf::Vector2f(3, 3) };
    bool result = doLinesIntersect(line1, line2);
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE(testDoLinesIntersect_CollinearNonOverlapping) {
    LineSegment line1 = { sf::Vector2f(0, 0), sf::Vector2f(2, 2) };
    LineSegment line2 = { sf::Vector2f(3, 3), sf::Vector2f(4, 4) };
    bool result = doLinesIntersect(line1, line2);
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE(testDoLinesIntersect_CollinearOverlapping) {
    LineSegment line1 = { sf::Vector2f(0, 0), sf::Vector2f(3, 3) };
    LineSegment line2 = { sf::Vector2f(2, 2), sf::Vector2f(4, 4) };
    bool result = doLinesIntersect(line1, line2);
    BOOST_CHECK(!result);
}


// ########################################## TEST CLASSE INIT #################################################

BOOST_AUTO_TEST_CASE(testInitMenu) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Init init;

    int mode = 0;
    // Vérifier que le menu ne lance pas d'exception
    BOOST_CHECK_NO_THROW(init.menu(window, &mode));

    // Simuler un clic de souris sur l'option de jeu solo
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = window.getSize().x / 2 - 50;
    event.mouseButton.y = window.getSize().y / 2 - 100;
    window.pollEvent(event);
    BOOST_CHECK_NO_THROW(init.menu(window, &mode));
    BOOST_CHECK_EQUAL(mode, 2); //Il faut choisir 2 joueurs !!
}

BOOST_AUTO_TEST_CASE(testInitChoose) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Init init;

    int res[2] = {0, 0};
    // Vérifier que choose ne lance pas d'exception
    BOOST_CHECK_NO_THROW(init.choose(window, res));

    // Simuler un clic de souris pour sélectionner le tank pour le joueur 1
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = window.getSize().x / 2 - 150;
    event.mouseButton.y = window.getSize().y / 2;
    window.pollEvent(event);
    BOOST_CHECK_NO_THROW(init.choose(window, res));
    BOOST_CHECK_EQUAL(res[0], 2);
}

/*BOOST_AUTO_TEST_CASE(testInitName) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    Init init;

    char* player1Name = nullptr;
    char* player2Name = nullptr;

    // Vérifier que name ne lance pas d'exception
    BOOST_CHECK_NO_THROW(init.name(window, player1Name, player2Name));

    // Simuler la saisie des noms des joueurs et la pression sur le bouton Go
    sf::Event event;
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    event.mouseButton.x = window.getSize().x / 2;
    event.mouseButton.y = window.getSize().y / 2 + 50;
    window.pollEvent(event);
    BOOST_CHECK_NO_THROW(init.name(window, player1Name, player2Name));

    // Vérifier que les noms des joueurs sont définis
    BOOST_CHECK(player1Name != nullptr);
    BOOST_CHECK(player2Name != nullptr);

    // Nettoyage
    free(player1Name);
    free(player2Name);*
}
*/
// ##################################### TEST CLASSE PROJECTILE #################################################

BOOST_AUTO_TEST_CASE(testProjectileLoadTexture) {
    // Vérifier que la texture est chargée correctement
    BOOST_CHECK(Projectile::loadTexture());
}

BOOST_AUTO_TEST_CASE(testProjectileInitialization) {
    float x = 100.0f;
    float y = 100.0f;
    float speed = 5.0f;
    float orientation = 0.0f; // vers la droite

    Projectile projectile(x, y, speed, orientation);

    // Vérifier la position initiale
    BOOST_CHECK_EQUAL(projectile.getPosition().x, x);
    BOOST_CHECK_EQUAL(projectile.getPosition().y, y);

    // Vérifier les bounds du projectile
    sf::FloatRect bounds = projectile.getBounds();
    BOOST_CHECK(bounds.width > 0);
    BOOST_CHECK(bounds.height > 0);
}

BOOST_AUTO_TEST_CASE(testProjectileUpdate) {
    float x = 100.0f;
    float y = 100.0f;
    float speed = 5.0f;
    float orientation = 0.0f; // vers la droite

    Projectile projectile(x, y, speed, orientation);

    // Mettre à jour la position
    projectile.update();

    // Vérifier la nouvelle position
    BOOST_CHECK_EQUAL(projectile.getPosition().x, x + speed);
    BOOST_CHECK_EQUAL(projectile.getPosition().y, y);
}

BOOST_AUTO_TEST_CASE(testProjectileDraw) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Test Window");
    float x = 100.0f;
    float y = 100.0f;
    float speed = 5.0f;
    float orientation = 0.0f; // vers la droite

    Projectile projectile(x, y, speed, orientation);

    // Vérifier que la méthode draw ne lance pas d'exception
    BOOST_CHECK_NO_THROW(projectile.draw(window));
}


BOOST_AUTO_TEST_SUITE_END()