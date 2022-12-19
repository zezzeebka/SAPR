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
    window->draw(*ButtonDraw);
    window->draw(*ButtonDrawWithPressure);
    window->draw(*ButtonProjectFile);
    window->draw(*Back);
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
                    if(ButtonDraw->getGlobalBounds().contains(mousePosF)){
                        isActive++;
                        filename = MainProjectFileManager->getFileName();
                        MainConstruction->setFilename(filename);
                        MainConstruction->isActive = 1;
                        Sleep(1000);
                    }
                    else if(ButtonDrawWithPressure->getGlobalBounds().contains(mousePosF)){

                    }
                    else if(ButtonProjectFile->getGlobalBounds().contains(mousePosF)){
                        isActive++;
                        MainProjectFileManager->isActive = 1;
                        Sleep(1000);
                    }
                    else if(Back->getGlobalBounds().contains(mousePosF))
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

std::shared_ptr<Construction> Preprocessor::getConstruction()
{
    return MainConstruction;
}

std::string Preprocessor::getFileName()
{
    return filename;
}
