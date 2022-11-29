#include "projectfilemanager.h"
#include <ctime>
#include <fstream>
#include <windows.h>
#include <bits/stdc++.h>
#include <filesystem>
ProjectFileManager::ProjectFileManager()
{

    isActive = 0;
}



//void ProjectFileManager::CreateFile()
//{
//
//}

void ProjectFileManager::Draw(std::shared_ptr<sf::RenderWindow> window)
{
    if (textBox->isActive == 0){
        isActive = 1;
    }
    if(isActive == 1)
    {
        window->draw(*CreateButton->getRectangle());
        window->draw(*ChooseFile->getRectangle());
        window->draw(*Back->getRectangle());
        window->draw(*ChangeFile->getRectangle());
        window->draw(*RefreshFile->getRectangle());
    }
    if(textBox->isActive > 0)
    {
        textBox->Draw(window);
    }
}

void ProjectFileManager::getEvent(std::shared_ptr<sf::RenderWindow> window, sf::Event event){
    if(isActive == 1){
        if (event.type == sf::Event::MouseButtonPressed){
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                sf::Vector2f mousePosF ( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if(CreateButton->getRectangle()->getGlobalBounds().contains(mousePosF)){
                     time_t now = time(0);
                     std::string dt = ctime(&now);
                     dt.erase(dt.size() - 1);
                     dt.erase(remove(dt.begin(),dt.end(),' '),dt.end());
                     dt.erase(remove(dt.begin(),dt.end(),':'),dt.end());
                     std::ofstream outFile;
                     outFile.open(dt + ".txt");
                     outFile.close();

//                   isActive++;
//                   MainConstruction->isActive = 1;
//                   Sleep(1000);
                }
                else if(ChooseFile->getRectangle()->getGlobalBounds().contains(mousePosF)){
                    OPENFILENAME ofn;
                    char filename[ 255 ];
                    while(!GetOpenFileNameA( &ofn ))
                    {
                        ZeroMemory( &filename, sizeof( filename ) );
                        ZeroMemory( &ofn,      sizeof( ofn ) );
                        ofn.lStructSize  = sizeof( ofn );
                        ofn.lpstrFilter  = "TEXT(.txt)\0*.txt\0";
                        ofn.lpstrFile    = filename;
                        ofn.nMaxFile     = MAX_PATH;
                        ofn.lpstrTitle   = "Choose .jpg or .png file";
                        ofn.Flags        = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
                     }
                    usedFileName = std::string(filename);
                }
                else if(ChangeFile->getRectangle()->getGlobalBounds().contains(mousePosF))
                {
                    isActive++;
                    textBox->isActive = 1;
                }
                else if(Back->getRectangle()->getGlobalBounds().contains(mousePosF))
                {
                    isActive = 0;
                }
                else if(RefreshFile->getRectangle()->getGlobalBounds().contains(mousePosF))
                {
                    std::ofstream ofs;
                    ofs.open(usedFileName, std::ios::out);
                    ofs << textBox->getString();
                    ofs.close();
                    isActive = 0;
                }
        }
    }
    if(textBox->isActive > 0){
    textBox->getEvent(window, event);
    }

}

std::string ProjectFileManager::getFileName()
{
    return usedFileName;
}
