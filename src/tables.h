#ifndef TABLES_H
#define TABLES_H
#include "button.h"
#include "windowactivity.h"
#include "construction.h"
class Tables : public WindowActivity
{
private:
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 0, 0, "data/back.png");
    std::shared_ptr<Construction> MainConstr;
    float step;
    float sumL;
    std::vector<std::vector<double>> Sx;
    std::vector<std::vector<double>> Ux;
    std::vector<std::vector<double>> Nx;
    float lenghtKoef = 0;
    float heightKoef = 0;
    int page = 0;
    int bar = 0;
    int N = 0;
    int Part = 0;
public:
    Tables();
    Tables(std::shared_ptr<Construction> Constr, std::vector<std::vector<double>> tSx, std::vector<std::vector<double>> tNx, std::vector<std::vector<double>> tUx);
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
};

#endif // TABLES_H
