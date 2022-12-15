#include "mainscreen.h"
#include "windows.h"
MainScreen::MainScreen()
{
    isActive = 1;
    BGTexture.loadFromFile("data/fon.jpg");
    BG.setTexture(BGTexture);
}

void MainScreen::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(BG);
    if (MainPreprocessor->isActive == 0){
        isActive = 1;
    }
    if(isActive == 1){
    window->draw(*Preproc);
    window->draw(*Proc);
    window->draw(*Postproc);
    }
    if(MainPreprocessor->isActive > 0){
    MainPreprocessor->Draw(window);
    }
    if(MainProcessor->isActive > 0)
    {
    }
}

void MainScreen::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event){
        if(isActive == 1){
            if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if(Preproc->getGlobalBounds().contains(mousePosF)){
                        isActive++;
                        MainPreprocessor->isActive = 1;
                        Sleep(1000);
                    }
                    if(Proc->getGlobalBounds().contains(mousePosF)){
                        MainProcessor->Solve();
                        Sleep(1000);
                    }
                    if(Postproc->getGlobalBounds().contains(mousePosF)){

                }
            }
        }
        if(MainPreprocessor->isActive > 0){
        MainPreprocessor->getEvent(window, event);
        }
        if(MainProcessor->isActive > 0)
        {
            MainProcessor->getEvent(window, event);
        }
    }

std::shared_ptr<Preprocessor> MainScreen::getPreproc()
{
    return MainPreprocessor;
}
