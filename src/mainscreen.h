#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <SFML/Graphics.hpp>
#include "button.h"
#include <memory>
#include "postprocessor.h"
#include "windowactivity.h"
#include "preprocessor.h"
#include "processor.h"
class MainScreen: public WindowActivity
{
private:
    std::shared_ptr<Button> Preproc = std::make_shared<Button>(200, 70, 300, 100, "data/preproc.png");
    std::shared_ptr<Button> Proc = std::make_shared<Button>(200, 70, 300, 250, "data/proc.png");
    std::shared_ptr<Button> Postproc = std::make_shared<Button>(200, 70, 300, 400, "data/postproc.png");
    std::shared_ptr<Preprocessor> MainPreprocessor = std::make_shared<Preprocessor>();
    std::shared_ptr<Processor> MainProcessor = std::make_shared<Processor>(MainPreprocessor);
    std::shared_ptr<Postprocessor> MainPostprocessor = std::make_shared<Postprocessor>(MainProcessor);
    sf::Texture BGTexture;
    sf::Sprite BG;
public:
    MainScreen();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    std::shared_ptr<Preprocessor> getPreproc();
};

#endif // MAINSCREEN_H
