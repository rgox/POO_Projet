#ifndef COURSE_HPP
#define COURSE_HPP

#include "Robot.hpp"

class Course : public Robot {
public:
	Course()
		:Robot(){
			health = 100;
            speed = 15;
			attackPower=25;
			defense=25;
	};;
	Course& operator=( Course* other);
    Course(Hexagone& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {
            // Ajustez les attributs existants ici si nécessaire
            health = 100;
            speed = 15;
			attackPower=25;
			defense=25;
            // Initialisez d'autres nouveaux attributs ici si nécessaire
        }

	void draw(sf::RenderWindow& window)override;
	
private:
    
};

#endif // COURSE_HPP