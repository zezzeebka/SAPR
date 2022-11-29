#include "button.h"

Button::Button(int SizeX, int SizeY, int PosX, int PosY)
{
    buttonRectangle = std::make_shared<sf::RectangleShape>();
    buttonRectangle->setSize(sf::Vector2f(SizeX, SizeY));
    buttonRectangle->setOutlineThickness(5);
    buttonRectangle->setOutlineColor(sf::Color::Red);
    buttonRectangle->setPosition(PosX, PosY);
}

bool Button::Clicked(){
    return true;
}

std::shared_ptr<sf::RectangleShape> Button::getRectangle(){
    return buttonRectangle;
}

void WindowChange(){}
