#include "button.h"

Button::Button(int SizeX, int SizeY, int PosX, int PosY, std::string filename)
{
    buttonTexture = std::make_shared<sf::Texture>();
    buttonTexture->loadFromFile(filename);
    setTexture(*buttonTexture);
    buttonRectangle = std::make_shared<sf::RectangleShape>();

    buttonRectangle->setPosition(PosX, PosY);
    setPosition(PosX, PosY);
}

bool Button::Clicked(){
    return true;
}

std::shared_ptr<sf::RectangleShape> Button::getRectangle(){
    return buttonRectangle;
}

void WindowChange(){}
