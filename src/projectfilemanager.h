#ifndef PROJECTFILEMANAGER_H
#define PROJECTFILEMANAGER_H
#include "windowactivity.h"
#include "button.h"
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "textbox.h"

class ProjectFileManager: public WindowActivity
{
private:
    std::shared_ptr<Button> CreateButton = std::make_shared<Button>(200, 70, 50, 50, "data/Create_png.png");
    std::shared_ptr<Button> ChooseFile = std::make_shared<Button>(250, 70, 50, 200, "data/choose_file.png");
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 300, 400, "data/Back.png");
    std::shared_ptr<Button> ChangeFile = std::make_shared<Button>(100, 70, 500, 100, "data/redaktor.png");
    std::shared_ptr<Button> RefreshFile = std::make_shared<Button>(100, 70, 500, 350, "data/Refresh.png");
    std::shared_ptr<std::string> FileName = std::make_shared<std::string>();
    std::string usedFileName;
    std::shared_ptr<TextBox> textBox = std::make_shared<TextBox>();
public:

    ProjectFileManager();
    void CreateFile();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    std::string getFileName();
};

#endif // PROJECTFILEMANAGER_H
