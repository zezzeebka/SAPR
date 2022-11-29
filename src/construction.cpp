#include "construction.h"
#include <iostream>
#include <sstream>
#include <fstream>
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
    window->draw(*Back->getRectangle());

    //сборка из файла
    if(activated == 0)
    {
        std::ifstream nameFileout;

        nameFileout.open(filename);
        std::string positions;
        std::string hooks;
        std::getline(nameFileout, positions);
        std::getline(nameFileout, hooks);
        nameFileout.close();

        std::stringstream posstream(positions);
        std::string segment;
        std::vector<int> poslist;
        std::vector<int> hookslist;

        while(std::getline(posstream, segment, ','))
        {
           arrLength.push_back(std::stoi(segment));
        }

        std::stringstream hooksstream(hooks);
        while(std::getline(hooksstream, segment, ','))
        {
           Connection.push_back(std::stoi(segment));
        }
        ToCenter();
    }


    for(int i = 0; i<Connection.size()/2; i++)
    {
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(CentralizedPoints[2*Connection[2*i]], CentralizedPoints[2*Connection[2*i]+1]);
        line[0].color  = sf::Color::Red;
        line[1].position = sf::Vector2f(CentralizedPoints[2*Connection[2*i+1]], CentralizedPoints[2*Connection[2*i+1]+1]);
        line[1].color = sf::Color::Red;
        window->draw(line, 2, sf::Lines);
    }
    activated = 1;
}

void Construction::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event){
        if(isActive == 1){
            if (event.type == sf::Event::MouseButtonPressed){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if(Back->getRectangle()->getGlobalBounds().contains(mousePosF))
                    {
                        isActive = 0;
                        activated = 0;
                    }
            }
        }
    }

void Construction::setFilename(std::string takenFilename)
{
    filename = takenFilename;
}
