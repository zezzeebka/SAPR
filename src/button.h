#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <memory>
class Button
{
private:
    std::shared_ptr<sf::RectangleShape> buttonRectangle;
public:
    Button();
    Button(int SizeX, int SizeY, int PosX, int PosY);
    bool Clicked();
    std::shared_ptr<sf::RectangleShape> getRectangle();
};

#endif // BUTTON_H
