#include "const_diagram.h"

Const_Diagram::Const_Diagram()
{

}

Const_Diagram::Const_Diagram(std::shared_ptr<Construction> Constr, std::vector<std::vector<double>> tSx, std::vector<std::vector<double>> tNx, std::vector<std::vector<double>> tUx)
{
    MainConstr = Constr;
    Sx =tSx;
    Ux = tUx;
    Nx = tNx;
}

void Const_Diagram::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    double posX = 42;
    double posY;

    sf::Text text;
    sf::Font font;
    font.loadFromFile("arialmt.ttf");
    text.setFont(font);
    text.setCharacterSize(16);

    lenghtKoef = 0;
    heightKoef = 0;

    std::vector<double> drawableLength = MainConstr->getDrawableL();
    std::vector<double> drawableSquare = MainConstr->getDrawableS();

    for(std::vector<double>::iterator it = drawableLength.begin(); it != drawableLength.end(); ++it)
    {
         lenghtKoef += *it;
    }
    lenghtKoef = (800-84) / lenghtKoef;
    float it = *std::max_element(std::begin(drawableSquare), std::end(drawableSquare));
    it++;
    heightKoef = 250 / it;

    for(int i = 0; i<MainConstr->getL().size(); i++)
    {
        posY = 300 - drawableSquare[i]/2*heightKoef;
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(drawableLength[i]*lenghtKoef, drawableSquare[i]*heightKoef));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition(posX, posY);

        text.setString(("L" + std::to_string(i) + "=" + std::to_string(MainConstr->getL()[i]) + " A" + std::to_string(i) + "=" + std::to_string(MainConstr->getA()[i])));
        text.setPosition(0, 70+30*i);
        text.setColor(sf::Color::Red);
        int littleArrowPosX = posX;
        posX += drawableLength[i]*lenghtKoef;
        window->draw(rectangle);
        window->draw(text);
    }

    posX = 42;
    posY = 300;
    // gets the value of the max element in O(n) time
    std::vector<double> tmpUx;
    for(int i=0;i<Ux.size();i++){
            tmpUx.insert(tmpUx.end(),Ux[i].begin(),Ux[i].end());
        }
    double Uxmax = *max_element(tmpUx.begin(),tmpUx.end());
    double Uxmin = abs(*min_element(tmpUx.begin(),tmpUx.end()));

    std::vector<double> tmpNx;
    for(int i=0;i<Nx.size();i++){
            tmpNx.insert(tmpNx.end(),Nx[i].begin(),Nx[i].end());
        }
    double Nxmax = *max_element(tmpNx.begin(),tmpNx.end());
    double Nxmin = abs(*min_element(tmpNx.begin(),tmpNx.end()));

    std::vector<double> tmpSx;
    for(int i=0;i<Sx.size();i++){
            tmpSx.insert(tmpSx.end(),Sx[i].begin(),Sx[i].end());
        }
    double Sxmax = *max_element(tmpSx.begin(),tmpSx.end());
    double Sxmin = abs(*min_element(tmpSx.begin(),tmpSx.end()));

    auto comp = [](double x, double y)
    {
        if (x < y)
        {
            return y;
        }
        else
        {
            return x;
        }
    };

    for(int i = 0; i < MainConstr->getL().size(); i++)
    {
        for(int j = 0; j < 20; j++)
        {
            sf::CircleShape dotU(3);
            sf::CircleShape dotN(3);
            sf::CircleShape dotS(3);

            dotU.setFillColor(sf::Color::Green);
            dotN.setFillColor(sf::Color::Red);
            dotS.setFillColor(sf::Color::Blue);

            dotU.setPosition(posX+MainConstr->getDrawableL()[i]/20*j*lenghtKoef, posY-Ux[i][j]*200/comp(Uxmax, Uxmin));
            dotS.setPosition(posX+MainConstr->getDrawableL()[i]/20*j*lenghtKoef, posY-Sx[i][j]*200/comp(Sxmax, Sxmin));
            dotN.setPosition(posX+MainConstr->getDrawableL()[i]/20*j*lenghtKoef, posY-Nx[i][j]*200/comp(Nxmax, Nxmin));

            window->draw(dotU);
            window->draw(dotS);
            window->draw(dotN);
        }
        posX += MainConstr->getDrawableL()[i]*lenghtKoef;
    }

    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(42, 300);
    lines[0].color  = sf::Color::Red;
    lines[1].position = sf::Vector2f(800-42, 300);
    lines[1].color = sf::Color::Red;

    window->draw(lines);
    window->draw(*Back);

    sf::CircleShape signU(3);
    sf::CircleShape signN(3);
    sf::CircleShape signS(3);

    signU.setFillColor(sf::Color::Green);
    signN.setFillColor(sf::Color::Red);
    signS.setFillColor(sf::Color::Blue);

    signU.setPosition(780, 50);
    signN.setPosition(780, 75);
    signS.setPosition(780, 100);

    window->draw(signU);
    window->draw(signN);
    window->draw(signS);

    sf::Text textUx;
    sf::Text textSx;
    sf::Text textNx;

    textUx.setFont(font);
    textNx.setFont(font);
    textSx.setFont(font);

    textUx.setString("Ux");
    textNx.setString("Nx");
    textSx.setString("Sx");

    textUx.setCharacterSize(16);
    textNx.setCharacterSize(16);
    textSx.setCharacterSize(16);

    textUx.setPosition(750,50);
    textNx.setPosition(750,75);
    textSx.setPosition(750,100);

    textUx.setColor(sf::Color::Black);
    textNx.setColor(sf::Color::Black);
    textSx.setColor(sf::Color::Black);

    window->draw(textUx);
    window->draw(textNx);
    window->draw(textSx);
}

void Const_Diagram::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event)
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
    }
}
