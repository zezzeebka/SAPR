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
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 400, 400, "data/Back.png");
    sf::Text drawableText;
    std::string str;
    sf::Font* font = new sf::Font();
    sf::Text helpText;
    std::string helpStr = "Other strings [0] = L, [1] = A, [2] = Q, \n[3] = E, [4] = xq, [5] = F(on the end of the rod)\n "
                          "First string [0] = F(first F), [1] = 0/1(left seal), \n[2] = 0/1(right seal)";
public:
    TextBox();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    std::string getString();
    void setString(std::string inFileStr);
};

#endif /* TextBox_cpp */
