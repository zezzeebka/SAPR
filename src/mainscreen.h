#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <SFML/Graphics.hpp>
#include "button.h"
#include <memory>
#include "windowactivity.h"
#include "preprocessor.h"
class MainScreen: public WindowActivity
{
private:
    std::shared_ptr<Button> Preproc = std::make_shared<Button>(200, 70, 300, 100);
    std::shared_ptr<Button> Proc = std::make_shared<Button>(200, 70, 300, 250);
    std::shared_ptr<Button> Postproc = std::make_shared<Button>(200, 70, 300, 400);
    std::shared_ptr<Preprocessor> MainPreprocessor = std::make_shared<Preprocessor>();
public:
    MainScreen();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
};

#endif // MAINSCREEN_H
