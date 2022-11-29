#include "preprocessor.h"
#include "windows.h"

Preprocessor::Preprocessor()
{
    isActive = 0;
}

void Preprocessor::Draw(std::shared_ptr<sf::RenderWindow> window){
    if (MainConstruction->isActive == 0 && MainProjectFileManager->isActive == 0){
        isActive = 1;
    }
    if(isActive == 1)
    {
    window->draw(*ButtonDraw->getRectangle());
    window->draw(*ButtonDrawWithPressure->getRectangle());
    window->draw(*ButtonProjectFile->getRectangle());
    window->draw(*Back->getRectangle());
    }
    else if(MainConstruction->isActive > 0)
    {
    MainConstruction->Draw(window);
    }
    else if(MainProjectFileManager->isActive > 0)
    {
    MainProjectFileManager->Draw(window);
    }
}

void Preprocessor::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event){
        if(isActive == 1){
            if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if(ButtonDraw->getRectangle()->getGlobalBounds().contains(mousePosF)){
                        isActive++;
                        filename = MainProjectFileManager->getFileName();
                        MainConstruction->setFilename(filename);
                        MainConstruction->isActive = 1;
                        Sleep(1000);
                    }
                    else if(ButtonDrawWithPressure->getRectangle()->getGlobalBounds().contains(mousePosF)){

                    }
                    else if(ButtonProjectFile->getRectangle()->getGlobalBounds().contains(mousePosF)){
                        isActive++;
                        MainProjectFileManager->isActive = 1;
                        Sleep(1000);
                    }
                    else if(Back->getRectangle()->getGlobalBounds().contains(mousePosF))
                    {
                        isActive = 0;
                    }
            }
        }
        if(MainConstruction->isActive > 0){
            MainConstruction->getEvent(window, event);
        }
        else if(MainProjectFileManager->isActive > 0){
            MainProjectFileManager->getEvent(window, event);
        }
    }
