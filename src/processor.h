#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "windowactivity.h"
#include "preprocessor.h"

class Processor: public WindowActivity
{
private:
    std::shared_ptr<Preprocessor> MainPreproc;
public:
    Processor();
    Processor(std::shared_ptr<Preprocessor> Preproc);
    void Solve();
    void getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event);
};

#endif // PROCESSOR_H
