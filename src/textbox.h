#ifndef TextBox_cpp
#define TextBox_cpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "windowactivity.h"
#include "button.h"
class TextBox: public WindowActivity {
private:
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 400, 400);
    sf::Text drawableText;
    std::string str;
    sf::Font* font = new sf::Font();
public:
    TextBox();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    std::string getString();
};

#endif /* TextBox_cpp */
