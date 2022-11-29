#include "mainscreen.h"
#include "windows.h"
MainScreen::MainScreen()
{
    isActive = 1;
}

void MainScreen::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    if (MainPreprocessor->isActive == 0){
        isActive = 1;
    }
    if(isActive == 1){
    window->draw(*Preproc->getRectangle());
    window->draw(*Proc->getRectangle());
    window->draw(*Postproc->getRectangle());
    }
    if(MainPreprocessor->isActive > 0){
    MainPreprocessor->Draw(window);
    }
}

void MainScreen::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event){
        if(isActive == 1){
            if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if(Preproc->getRectangle()->getGlobalBounds().contains(mousePosF)){
                        isActive++;
                        MainPreprocessor->isActive = 1;
                        Sleep(1000);
                    }
                    if(Proc->getRectangle()->getGlobalBounds().contains(mousePosF)){
                    }
                    if(Postproc->getRectangle()->getGlobalBounds().contains(mousePosF)){

                }
            }
        }
        if(MainPreprocessor->isActive > 0){
        MainPreprocessor->getEvent(window, event);
        }
    }
