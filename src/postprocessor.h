#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H
#include "processor.h"
#include "tables.h"
#include "windowactivity.h"
#include "button.h"
#include "const_diagram.h"
class Postprocessor : public WindowActivity
{
private:
    std::shared_ptr<Processor> MainProcessor;
    std::shared_ptr<Button> B1 = std::make_shared<Button>(200, 70, 300, 100, "data/work_with_files.png");
    std::shared_ptr<Button> B2 = std::make_shared<Button>(200, 70, 300, 250, "data/draw.png");
    std::shared_ptr<Button> B3 = std::make_shared<Button>(200, 70, 300, 400, "data/postproc.png");
    std::shared_ptr<Button> Back = std::make_shared<Button>(70, 70, 0, 0, "data/back.png");
    std::shared_ptr<Const_Diagram> MainConstrDia = std::make_shared<Const_Diagram>();
    std::shared_ptr<Tables> MainTables = std::make_shared<Tables>();
    float step = 0;
public:
    Postprocessor();
    Postprocessor(std::shared_ptr<Processor> Processor);
    double getNx(int p, double x);
    double getUx(int p, double x);
    double getSx(int p, double x);
    void Draw(std::shared_ptr<sf::RenderWindow> window);
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    void a();
    double getSumL();
};

#endif // POSTPROCESSOR_H
