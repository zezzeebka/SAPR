#include "tables.h"
#include <iostream>
#include "windows.h"

Tables::Tables()
{

}

Tables::Tables(std::shared_ptr<Construction> Constr, std::vector<std::vector<double>> tSx, std::vector<std::vector<double>> tNx, std::vector<std::vector<double>> tUx)
{
    MainConstr = Constr;
    Sx =tSx;
    Ux = tUx;
    Nx = tNx;
}

void Tables::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    if(isActive == 1)
    {
        sf::VertexArray lines1(sf::LinesStrip, 2);
        sf::VertexArray lines2(sf::LinesStrip, 2);
        sf::VertexArray lines3(sf::LinesStrip, 2);
        sf::VertexArray lines4(sf::LinesStrip, 2);
        for(int j = 0; j < 3; j++){
        for(int i = 0; i < 4; i++)
        {

            lines1[0].position = sf::Vector2f(30+200*i, 100+150*j);
            lines1[0].color  = sf::Color::Red;
            lines1[1].position = sf::Vector2f(30+200*i, 200+150*j);
            lines1[1].color = sf::Color::Red;


            lines2[0].position = sf::Vector2f(30+200*i, 100+150*j);
            lines2[0].color  = sf::Color::Red;
            lines2[1].position = sf::Vector2f(190+200*i, 100+150*j);
            lines2[1].color = sf::Color::Red;


            lines3[0].position = sf::Vector2f(190+200*i, 100+150*j);
            lines3[0].color  = sf::Color::Red;
            lines3[1].position = sf::Vector2f(190+200*i, 200+150*j);
            lines3[1].color = sf::Color::Red;


            lines4[0].position = sf::Vector2f(190+200*i, 200+150*j);
            lines4[0].color  = sf::Color::Red;
            lines4[1].position = sf::Vector2f(30+200*i, 200+150*j);
            lines4[1].color = sf::Color::Red;



        window->draw(lines1);
        window->draw(lines2);
        window->draw(lines3);
        window->draw(lines4);
        }

    }

        sf::Font font;
        font.loadFromFile("arialmt.ttf");
        sf::Text textUx;
        sf::Text textSx;
        sf::Text textNx;

        textUx.setFont(font);
        textSx.setFont(font);
        textNx.setFont(font);

        textUx.setString("Ux=");
        textSx.setString("Sx=");
        textNx.setString("Nx=");

        textUx.setCharacterSize(16);
        textSx.setCharacterSize(16);
        textNx.setCharacterSize(16);

        sf::Text number1;
        sf::Text number2;
        sf::Text number3;
        sf::Text number4;

        number1.setFont(font);
        number2.setFont(font);
        number3.setFont(font);
        number4.setFont(font);


        number1.setCharacterSize(16);
        number2.setCharacterSize(16);
        number3.setCharacterSize(16);
        number4.setCharacterSize(16);

        number1.setPosition(40, 70);
        number2.setPosition(240, 70);
        number3.setPosition(440, 70);
        number4.setPosition(640, 70);

        number1.setString(std::to_string(1 + page*4));
        number2.setString(std::to_string(2 + page*4));
        number3.setString(std::to_string(3 + page*4));
        number4.setString(std::to_string(4 + page*4));

        window->draw(number1);
        window->draw(number2);
        window->draw(number3);
        window->draw(number4);


        sf::Text textUxD;
        sf::Text textSxD;
        sf::Text textNxD;

        textUxD.setFont(font);
        textSxD.setFont(font);
        textNxD.setFont(font);

        textUxD.setCharacterSize(16);
        textSxD.setCharacterSize(16);
        textNxD.setCharacterSize(16);



        for(int i = 0; i < 4; i++){
            textUx.setPosition(40+200*i, 100);
            textNx.setPosition(40+200*i, 250);
            textSx.setPosition(40+200*i, 400);
            window->draw(textUx);
            window->draw(textSx);
            window->draw(textNx);

            textSxD.setPosition(90+200*i, 400);
            textNxD.setPosition(90+200*i, 250);
            textUxD.setPosition(90+200*i, 100);
            textUxD.setString(std::to_string(Ux[bar][i+page*4]));
            textSxD.setString(std::to_string(Sx[bar][i+page*4]));
            textNxD.setString(std::to_string(Nx[bar][i+page*4]));

            window->draw(textUxD);
            window->draw(textSxD);
            window->draw(textNxD);

        }

        window->draw(*Back);
    }
}

void Tables::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event)
{
    if(isActive == 1){
        if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if(Back->getGlobalBounds().contains(mousePosF))
                {
                    isActive = 0;
                }
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Right)
            {
                if(page < 4)
                {
                    page++;
                    Sleep(30);
                }
            }
            if(event.key.code == sf::Keyboard::Left)
            {
                if(page > 0)
                page--;
                Sleep(30);
            }
            if(event.key.code == sf::Keyboard::Up)
            {
                if(bar < Ux.size()-1)
                {
                    bar++;
                    Sleep(30);
                }
            }
            if(event.key.code == sf::Keyboard::Down)
            {
                if(bar > 0)
                {
                    bar--;
                    Sleep(30);
                }
            }
        }
    }
}
