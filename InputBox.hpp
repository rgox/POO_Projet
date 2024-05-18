#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class InputBox {
public:
    InputBox(float width, float height, sf::Font& font) 
        : isFocused(false), box(sf::Vector2f(width, height)), text("", font, 24) {
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);

        text.setFillColor(sf::Color::Black);
        text.setPosition(box.getPosition());
    }

    void setPosition(float x, float y) {
        box.setPosition(x, y);
        text.setPosition(x + 5, y + 5);  // Ajustez le décalage selon les besoins
    }

    void setFocus(bool focus) {
        isFocused = focus;
        if (focus) {
            box.setOutlineColor(sf::Color::Blue);
        } else {
            box.setOutlineColor(sf::Color::Black);
        }
    }

    bool contains(float x, float y) const {
        return box.getGlobalBounds().contains(x, y);
    }

    void handleEvent(const sf::Event& event) {
        if (isFocused && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {
                if (!textString.empty())
                    textString.pop_back();
            } else {
                textString += event.text.unicode;
            }
            text.setString(textString);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }

    std::string getString() const {
        return textString;
    }

private:
    bool isFocused;
    sf::RectangleShape box;
    sf::Text text;
    std::string textString;
};

#endif // INPUTBOX_HPP
