#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <memory>
class Button : public sf::Sprite
{
private:
    std::shared_ptr<sf::RectangleShape> buttonRectangle;
    std::shared_ptr<sf::Texture> buttonTexture;
public:
    Button();
    Button(int SizeX, int SizeY, int PosX, int PosY, std::string filename);
    bool Clicked();
    std::shared_ptr<sf::RectangleShape> getRectangle();
};

#endif // BUTTON_H
