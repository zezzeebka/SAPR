#include <SFML/Graphics.hpp>
#include <memory>
#include "mainscreen.h"

int main()
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "My window");
    std::shared_ptr<MainScreen> mainScreen = std::make_shared<MainScreen>();
    // run the program as long as the window is open
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch ( event.type )
            {
            case sf::Event::Closed:
                {
                window->close();
                break;
                }
            }
            mainScreen->getEvent(window, event);

        }


        // clear the window with black color
        window->clear(sf::Color::Black);
        mainScreen->Draw(window);
        // draw everything here...
        // window.draw(...);
        // end the current frame
        window->display();
    }

    return 0;
}
