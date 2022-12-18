#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "windowactivity.h"
#include "preprocessor.h"
#include <vector>

class Processor: public WindowActivity
{
private:
    std::shared_ptr<Preprocessor> MainPreproc;
    std::vector<double> U;
public:
    Processor();
    Processor(std::shared_ptr<Preprocessor> Preproc);
    void Solve();
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
    std::shared_ptr<Preprocessor> getPreproc();
    std::vector<double> getU();
};

#endif // PROCESSOR_H
