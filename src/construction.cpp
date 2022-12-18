#include "construction.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "windows.h"
Construction::Construction()
{
    isActive = 0;
}
void Construction::ToCenter()
{
    int centerX = 0;
    int centerY = 0;
    for(int i = 0; i<arrLength.size(); i++)
    {
        centerX+=arrLength[i];
        centerY+=arrLength[i+1];
        i++;
    }
    centerX = 800/2-centerX/arrLength.size();
    centerY = 600/2-centerY/arrLength.size();
    for(int i = 0; i<arrLength.size(); i++)
    {
        CentralizedPoints.push_back(centerX+arrLength[i]);
        CentralizedPoints.push_back(centerY+arrLength[i+1]);
        i++;
    }
}
void Construction::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    window->draw(*Back);
    //сборка из файла
    if(activated == 0)
    {

        arrLength.clear();
        drawableLength.clear();
        drawableSquare.clear();
        Square.clear();
        centralizedPressure.clear();
        decentralizedPressure.clear();
        firstPressure = 0;

        std::ifstream nameFileout;

        nameFileout.open(filename);
        std::string Line;
        std::stringstream posstream;
        std::stringstream secondss;
        posstream << nameFileout.rdbuf();
        std::string segment;
        std::string segment2;
        arrLength.clear();
        Square.clear();
        int firstEl = 1;
        while(std::getline(posstream, segment, '\n'))
        {
           if(firstEl == 1)
           {
               secondss << segment;
               for(int i = 0; i < 3; i++)
               {
                   std::getline(secondss, segment2, ',');
                   if(i == 0)
                   {
                       firstPressure = std::stod(segment2);
                   }
                   else if(i == 1)
                   {
                       leftSeal = std::stoi(segment2);
                   }
                   else if(i == 2)
                   {
                       rightSeal = std::stoi(segment2);
                   }
               }
               firstEl++;
           }
           else
           {
               secondss.str("");
               secondss << segment;
               segment2.clear();
               for(int i = 0; i < 6; i++)
               {
                   std::getline(secondss, segment2, ',');
                   if (i == 0)
                   {
                        arrLength.push_back(std::stod(segment2));
                   }
                   else if (i == 1)
                   {
                       Square.push_back(std::stod(segment2));
                   }
                   else if (i == 2)
                   {
                       E.push_back(std::stod(segment2));
                   }
                   else if (i == 3)
                   {
                       Sigma.push_back(std::stod(segment2));
                   }
                   else if (i == 4)
                   {
                       decentralizedPressure.push_back(std::stod(segment2));
                   }
                   else if (i == 5)
                   {
                       centralizedPressure.push_back(std::stod(segment2));
                   }
               }
            }
         }
        nameFileout.close();

        //ToCenter();
        for (int i=0; i<arrLength.size(); i++)
        {
                drawableLength.push_back(arrLength[i]);
        }
        double itmax = *std::max_element(std::begin(drawableLength), std::end(drawableLength));
        double itmin = *std::min_element(std::begin(drawableLength), std::end(drawableLength));
        int indexMax;
        int indexMin;
        while(itmax/itmin > 15)
        {
            indexMax = std::max_element(drawableLength.begin(), drawableLength.end()) - drawableLength.begin();
            indexMin = std::min_element(drawableLength.begin(), drawableLength.end()) - drawableLength.begin();
            drawableLength[indexMax] -= itmin/2;
            drawableLength[indexMin] += itmin/2;
            itmax = *std::max_element(std::begin(drawableLength), std::end(drawableLength));
            itmin = *std::min_element(std::begin(drawableLength), std::end(drawableLength));
        }

        for (int i=0; i<Square.size(); i++)
        {
                drawableSquare.push_back(Square[i]);
        }

        itmax = *std::max_element(std::begin(drawableSquare), std::end(drawableSquare));
        itmin = *std::min_element(std::begin(drawableSquare), std::end(drawableSquare));
        while(itmax/itmin > 15)
        {
            indexMax = std::max_element(drawableSquare.begin(), drawableSquare.end()) - drawableSquare.begin();
            indexMin = std::min_element(drawableSquare.begin(), drawableSquare.end()) - drawableSquare.begin();
            drawableSquare[indexMax] -= itmin/2;
            drawableSquare[indexMin] += itmin/2;
            itmax = *std::max_element(std::begin(drawableSquare), std::end(drawableSquare));
            itmin = *std::min_element(std::begin(drawableSquare), std::end(drawableSquare));
        }

        lenghtKoef = 0;
        for(std::vector<double>::iterator it = drawableLength.begin(); it != drawableLength.end(); ++it)
        {
             lenghtKoef += *it;
        }
        lenghtKoef = (800-84) / lenghtKoef;
        float it = *std::max_element(std::begin(drawableSquare), std::end(drawableSquare));
        it++;
        heightKoef = 250 / it;



    }

    double posX = 42;
    double posY;
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arialmt.ttf");
    text.setFont(font);
    text.setCharacterSize(16);

    sf::Texture Texture;
    if(leftSeal == true)
    {
        sf::Sprite end1;
        Texture.loadFromFile("data/levo.png");
        end1.setTexture(Texture);
        end1.setPosition(sf::Vector2f(0,230));
        window->draw(end1);
    }

    if(rightSeal == true)
    {
        sf::Sprite end2;
        Texture.loadFromFile("data/pravo.png");
        end2.setTexture(Texture);
        end2.setPosition(sf::Vector2f(760,230));
        window->draw(end2);
    }

    sf::Sprite pressurePic;
    sf::Texture X;
    X.loadFromFile("data/x.png");

    for(int i = 0; i<arrLength.size(); i++)
    {
        posY = 300 - drawableSquare[i]/2*heightKoef;
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(drawableLength[i]*lenghtKoef, drawableSquare[i]*heightKoef));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition(posX, posY);

        text.setString(("L" + std::to_string(i) + "=" + std::to_string(arrLength[i]) + " A" + std::to_string(i) + "=" + std::to_string(Square[i])));
        text.setPosition(0, 70+30*i);
        text.setColor(sf::Color::Red);
        int littleArrowPosX = posX;
        posX += drawableLength[i]*lenghtKoef;
        window->draw(rectangle);
        window->draw(text);

        if(pressureActivity == 1)
        {
            X.loadFromFile("data/V.png");
            if(decentralizedPressure[i] != 0)
            {
                sf::Sprite littleArrow;
                sf::Texture littleArrowTexture;
                if(decentralizedPressure[i] > 0)
                {
                    littleArrowTexture.loadFromFile("data/strelka2.png");
                }
                else
                {
                    littleArrowTexture.loadFromFile("data/strelka.png");
                }
                littleArrow.setTexture(littleArrowTexture);
                while(littleArrowPosX < posX-21)
                {
                    littleArrow.setPosition(littleArrowPosX, 290);
                    window->draw(littleArrow);
                    littleArrowPosX += 30;
                }
            }
            //if(centralizedPressure[i] != 0)
            //{
            //    sf::Sprite BigArrow;
            //    sf::Texture BigArrowTexture;
            //    if(centralizedPressure[i] > 0)
            //    {
            //        BigArrowTexture.loadFromFile("data/strelkabig2.png");
            //    }
            //    if(centralizedPressure[i] < 0)
            //    {
            //        BigArrowTexture.loadFromFile("data/strelkabig1.png");
            //        BigArrow.setOrigin(BigArrowTexture.getSize().x, 0);
            //    }
            //    BigArrow.setTexture(BigArrowTexture);
            //    BigArrow.setPosition(posX, 320);
            //    window->draw(BigArrow);
            //}
        }
    }
    posX = 42;
    if(firstPressure != 0 && pressureActivity == 1)
    {
        sf::Sprite BigArrow;
        sf::Texture BigArrowTexture;
        if(firstPressure > 0)
        {
            BigArrowTexture.loadFromFile("data/strelkabig2.png");
        }
        else
        {
            BigArrowTexture.loadFromFile("data/strelkabig1.png");
            BigArrow.setOrigin(BigArrowTexture.getSize().x, 0);
        }
        BigArrow.setTexture(BigArrowTexture);
        BigArrow.setPosition(posX, 300);
        window->draw(BigArrow);
    }
    for(int i = 0; i<drawableLength.size(); i++)
    {
        posX += drawableLength[i]*lenghtKoef;
        if(pressureActivity == 1)
        {
            if(centralizedPressure[i] != 0)
            {
                sf::Sprite BigArrow;
                sf::Texture BigArrowTexture;
                if(centralizedPressure[i] > 0)
                {
                    BigArrowTexture.loadFromFile("data/strelkabig2.png");
                }
                if(centralizedPressure[i] < 0)
                {
                    BigArrowTexture.loadFromFile("data/strelkabig1.png");
                    BigArrow.setOrigin(BigArrowTexture.getSize().x, 0);
                }
                BigArrow.setTexture(BigArrowTexture);
                BigArrow.setPosition(posX, 300);
                window->draw(BigArrow);
            }
        }
    }

    pressurePic.setTexture(X);
    pressurePic.setPosition(570,110);
    window->draw(pressurePic);
    window->draw(*pressureActivityButton);



    activated = 1;
}

void Construction::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event){
        if(isActive == 1){
            if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if(Back->getGlobalBounds().contains(mousePosF))
                    {
                        isActive = 0;
                        activated = 0;
                        pressureActivity = 0;
                    }
                    else if(pressureActivityButton->getGlobalBounds().contains(mousePosF))
                    {
                        if(pressureActivity == 0)
                        {
                           pressureActivity = 1;
                           Sleep(200);
                        }
                        else
                        {
                            pressureActivity = 0;
                            Sleep(200);
                        }
                    }
            }
        }
    }

void Construction::setFilename(std::string takenFilename)
{
    filename = takenFilename;
}

std::vector<double> Construction::getL()
{
    return arrLength;
}

std::vector<double> Construction::getA()
{
    return Square;
}

std::vector<double> Construction::getE()
{
    return E;
}

std::vector<double> Construction::getSigma()
{
    return Sigma;
}

std::vector<double> Construction::getDF()
{
    return decentralizedPressure;
}

std::vector<double> Construction::getCF()
{
    return centralizedPressure;
}

bool Construction::getLeftSeal()
{
    return leftSeal;
}

bool Construction::getRightSeal()
{
    return rightSeal;
}

double Construction::getFirstPressure()
{
    return firstPressure;
}
std::vector<double> Construction::getDrawableL()
{
    return drawableLength;
}

std::vector<double> Construction::getDrawableS()
{
    return drawableSquare;
}
