#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include "button.h"
#include "windowactivity.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "construction.h"
#include "projectfilemanager.h"
class Preprocessor : public WindowActivity
{
private:
    std::shared_ptr<Button> ButtonDraw = std::make_shared<Button>(200, 70, 300, 100, "data/draw.png");
    std::shared_ptr<Button> ButtonDrawWithPressure = std::make_shared<Button>(250, 70, 300, 250, "data/draw_with_pres.png");
    std::shared_ptr<Button> ButtonProjectFile = std::make_shared<Button>(270, 70, 300, 400, "data/work_with_files.png");
    std::shared_ptr<Construction> MainConstruction = std::make_shared<Construction>();
    std::shared_ptr<ProjectFileManager> MainProjectFileManager = std::make_shared<ProjectFileManager>();
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 0, 0, "data/back.png");
    std::string filename;
public:
    Preprocessor();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    std::shared_ptr<Construction> getConstruction();

};

#endif // PREPROCESSOR_H
