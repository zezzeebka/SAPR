#ifndef CONST_DIAGRAM_H
#define CONST_DIAGRAM_H
#include "windowactivity.h"
#include "construction.h"
#include "button.h"
class Const_Diagram : public WindowActivity
{
private:
    std::shared_ptr<Construction> MainConstr;
    float step;
    float sumL;
    std::vector<std::vector<double>> Sx;
    std::vector<std::vector<double>> Ux;
    std::vector<std::vector<double>> Nx;
    float lenghtKoef = 0;
    float heightKoef = 0;
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 0, 0, "data/back.png");
public:
    Const_Diagram();
    Const_Diagram(std::shared_ptr<Construction> Constr, std::vector<std::vector<double>> tSx, std::vector<std::vector<double>> tNx, std::vector<std::vector<double>> tUx);
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
};

#endif // CONST_DIAGRAM_H
