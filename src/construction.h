#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H
#include "windowactivity.h"
#include "button.h"
#include <vector>
class Construction : public WindowActivity
{
private:
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 10, 10);
    std::vector<int> arrLength{ };
    std::vector<int> Connection{};
    std::vector<int> CentralizedPoints;
    bool activated = 0;
    std::string filename;
public:
    Construction();
    void ToCenter();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    void setFilename(std::string filename);
};

#endif // CONSTRUCTION_H
