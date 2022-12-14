#include "textbox.h"

/********** -------------- **********/
/********** Public Methods **********/
/********** -------------- **********/


TextBox::TextBox() {
    isActive = 0;
    font->loadFromFile("arialmt.ttf");
    drawableText.setFont(*font);
    helpText.setFont(*font);
    helpText.setPosition(0,450);
}

void TextBox::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    if(isActive)
    {
        drawableText.setString(str);
        drawableText.setCharacterSize(30);
        drawableText.setStyle(sf::Text::Bold);
        drawableText.setFillColor(sf::Color::Red);

        helpText.setString(helpStr);
        helpText.setCharacterSize(30);
        helpText.setStyle(sf::Text::Bold);
        helpText.setFillColor(sf::Color::Green);

        window->draw(drawableText);
        window->draw(helpText);
        window->draw(*Back);
    }

}

void TextBox::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event)
{
    if(isActive == 1){
        if (event.type == sf::Event::TextEntered){
                std::cout << event.key.code << std::endl;
                if(event.key.code == 8)
                {
                    str = str.substr(0, str.size()-1);
                }
                else if(event.key.code == 13)
                {
                    str+="\n";
                }
                else
                {
                str+=static_cast<char>(event.text.unicode);
                }
        }
        if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if(Back->getGlobalBounds().contains(mousePosF))
                {
                    isActive = 0;

                }
        }
    }
}

std::string TextBox::getString()
{
    return str;
}

void TextBox::setString(std::string inFileStr)
{
    str = inFileStr;
}
