#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H
#include "windowactivity.h"
#include "button.h"
#include <vector>
#include <map>
#include <utility>
class Construction : public WindowActivity
{
private:
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 10, 10, "data/Back.png");
    std::shared_ptr<Button> pressureActivityButton = std::make_shared<Button>(250, 100, 500, 10, "data/pressure_draw.png");
    std::vector<double> arrLength{};
    std::vector<double> drawableLength{};
    std::vector<double> Square{};
    std::vector<double> drawableSquare{};
    std::vector<double> centralizedPressure;
    std::vector<double> decentralizedPressure;
    std::vector<double> E;
    std::vector<double> Sigma;
    std::vector<int> CentralizedPoints;
    double firstPressure;
    bool activated = 0;
    std::string filename;
    float lenghtKoef;
    float heightKoef;
    bool pressureActivity = 0;
    bool leftSeal = 0;
    bool rightSeal = 0;
public:
    Construction();
    void ToCenter();
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    void setFilename(std::string filename);
    std::vector<double> getL();
    std::vector<double> getA();
    std::vector<double> getSigma();
    std::vector<double> getE();
    std::vector<double> getDF();
    std::vector<double> getCF();
    std::vector<double> getDrawableL();
    std::vector<double> getDrawableS();
    bool getLeftSeal();
    bool getRightSeal();
    double getFirstPressure();
};

#endif // CONSTRUCTION_H
