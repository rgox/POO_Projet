#ifndef COURSE_HPP
#define COURSE_HPP

#include "Robot.hpp"

class Course : public Robot {
public:
    Course(Arene& hex, float x, float y, char controlScheme, sf::Color color) :
        Robot(hex, x, y, controlScheme, color) {

            // Nouveaux attributs

            health = 100;
            speed = 15;
			attackPower=25;
			defense=25;
            
        }

	//Définition de la fonction virtuelle draw

	void draw(sf::RenderWindow& window)override;
	
private:
    
};

#endif // COURSE_HPP