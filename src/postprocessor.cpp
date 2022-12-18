#include "postprocessor.h"
#include "construction.h"

Postprocessor::Postprocessor()
{

}

Postprocessor::Postprocessor(std::shared_ptr<Processor> Processor)
{
    MainProcessor = Processor;
}

void Postprocessor::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    if(MainConstrDia->isActive == 0 && MainTables->isActive == 0)
    {
        isActive = 1;
    }
    if(isActive == 1)
    {
        window->draw(*B1);
        window->draw(*B2);
        window->draw(*B3);
        window->draw(*Back);
    }
    else if(MainConstrDia->isActive > 0)
    {
        MainConstrDia->Draw(window);
    }
    else if(MainTables->isActive > 0)
    {
        MainTables->Draw(window);
    }
}

void Postprocessor::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event)
{
    if(isActive == 1){
                if (event.type == sf::Event::MouseButtonPressed){
                        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                        sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                        if(B1->getGlobalBounds().contains(mousePosF)){
                            isActive++;

                            //ВОЗМОЖНО ПРИГОДИТСЯ В БУДУЩЕМ

                            std::vector<std::vector<double>> tSx;
                            std::vector<std::vector<double>> tNx;
                            std::vector<std::vector<double>> tUx;
                            for(int i = 0; i < MainProcessor->getPreproc()->getConstruction()->getL().size(); i++)
                            {
                                tUx.push_back(std::vector<double>(0,0));
                                tNx.push_back(std::vector<double>(0,0));
                                tSx.push_back(std::vector<double>(0,0));
                                for(float j = 0; j < MainProcessor->getPreproc()->getConstruction()->getL()[i]; )
                                {
                                    tUx[i].push_back(getUx(i, j));
                                    tNx[i].push_back(getNx(i,j));
                                    tSx[i].push_back(getSx(i, j));
                                    j += MainProcessor->getPreproc()->getConstruction()->getL()[i]/20;
                                }
                            }


                            MainConstrDia = std::make_shared<Const_Diagram>(MainProcessor->getPreproc()->getConstruction(), tSx, tNx, tUx);
                            MainConstrDia->isActive = 1;
                        }
                        else if(B2->getGlobalBounds().contains(mousePosF)){
                            isActive++;

                            std::vector<std::vector<double>> tSx;
                            std::vector<std::vector<double>> tNx;
                            std::vector<std::vector<double>> tUx;
                            for(int i = 0; i < MainProcessor->getPreproc()->getConstruction()->getL().size(); i++)
                            {
                                tUx.push_back(std::vector<double>(0,0));
                                tNx.push_back(std::vector<double>(0,0));
                                tSx.push_back(std::vector<double>(0,0));
                                for(float j = 0; j < MainProcessor->getPreproc()->getConstruction()->getL()[i]; )
                                {
                                    tUx[i].push_back(getUx(i, j));
                                    tNx[i].push_back(getNx(i,j));
                                    tSx[i].push_back(getSx(i, j));
                                    j += MainProcessor->getPreproc()->getConstruction()->getL()[i]/20;
                                }
                            }

                            MainTables = std::make_shared<Tables>(MainProcessor->getPreproc()->getConstruction(), tSx, tNx, tUx);
                            MainTables->isActive++;

                        }
                        else if(B3->getGlobalBounds().contains(mousePosF)){
                            isActive++;
                            //MainProjectFileManager->isActive = 1;
                            //Sleep(1000);
                        }
                        else if(Back->getGlobalBounds().contains(mousePosF))
                        {
                            isActive = 0;
                        }
                }
            }
    if(MainConstrDia->isActive > 0)
    {
        MainConstrDia->getEvent(window, event);
    }
    else if(MainTables->isActive > 0)
    {
        MainTables->getEvent(window, event);
    }
}

double Postprocessor::getNx(int p, double x)
{
    return MainProcessor->getPreproc()->getConstruction()->getA()[p]*
           MainProcessor->getPreproc()->getConstruction()->getE()[p]*
           (MainProcessor->getU()[p+1]-MainProcessor->getU()[p])/
           MainProcessor->getPreproc()->getConstruction()->getL()[p]+
           MainProcessor->getPreproc()->getConstruction()->getDF()[p]*
           MainProcessor->getPreproc()->getConstruction()->getL()[p]*
           (1-2*x/MainProcessor->getPreproc()->getConstruction()->getL()[p])/2;
}

double Postprocessor::getUx(int p, double x)
{
    return MainProcessor->getU()[p]+
           x*(MainProcessor->getU()[p+1]-MainProcessor->getU()[p])/
           MainProcessor->getPreproc()->getConstruction()->getL()[p]+
           MainProcessor->getPreproc()->getConstruction()->getDF()[p]*
           MainProcessor->getPreproc()->getConstruction()->getL()[p]*x*
           (1-x*MainProcessor->getPreproc()->getConstruction()->getL()[p])/
           (2*MainProcessor->getPreproc()->getConstruction()->getE()[p]*
            MainProcessor->getPreproc()->getConstruction()->getA()[p]);
}

double Postprocessor::getSx(int p, double x)
{
    return getNx(p, x)/MainProcessor->getPreproc()->getConstruction()->getA()[p];
}

double Postprocessor::getSumL()
{
    double sum = 0;
    for(int i = 0; i < MainProcessor->getPreproc()->getConstruction()->getL().size(); i++)
    {
        sum += MainProcessor->getPreproc()->getConstruction()->getL()[i];
    }
    return sum;
}

void Postprocessor::a()
{
    float x = 0;
    for(x = 0;x < 1;)
    {
        auto b = getUx(0,x);
        x += 0.05;
    }
}
