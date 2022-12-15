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
        window->draw(*CreateButton);
        window->draw(*ChooseFile);
        window->draw(*Back);
        window->draw(*ChangeFile);
        window->draw(*RefreshFile);
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
            if(CreateButton->getGlobalBounds().contains(mousePosF)){
                 time_t now = time(0);
                 std::string dt = ctime(&now);
                 dt.erase(dt.size() - 1);
                 dt.erase(remove(dt.begin(),dt.end(),' '),dt.end());
                 dt.erase(remove(dt.begin(),dt.end(),':'),dt.end());
                 std::ofstream outFile;
                 outFile.open(dt + ".txt");
                 outFile.close();

//               isActive++;
//               MainConstruction->isActive = 1;
//               Sleep(1000);
            }
            else if(ChooseFile->getGlobalBounds().contains(mousePosF)){
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
            else if(ChangeFile->getGlobalBounds().contains(mousePosF))
            {
                std::string item_name;
                std::ifstream nameFileout;
                nameFileout.open(usedFileName, std::ios_base::binary);
                std::stringstream buffer;
                buffer << nameFileout.rdbuf();
                item_name = buffer.str();
                item_name.erase(remove(item_name.begin(),item_name.end(),'\r'),item_name.end());
                nameFileout.close();
                textBox->setString(item_name);
                isActive++;
                textBox->isActive = 1;
            }
            else if(Back->getGlobalBounds().contains(mousePosF))
            {
                isActive = 0;
            }
            else if(RefreshFile->getGlobalBounds().contains(mousePosF))
            {
                bool Error = 0;
                std::ofstream ofs;
                ofs.open(usedFileName, std::ios::out);
                ofs << textBox->getString();
                ofs.close();

                std::ifstream nameFileout;

                nameFileout.open(usedFileName);
                std::stringstream posstream;
                std::stringstream secondss;
                posstream << nameFileout.rdbuf();
                std::string segment;
                std::string segment2;
                int firstEl = 1;
                while(std::getline(posstream, segment, '\n'))
                {
                   if(firstEl == 1)
                   {
                       secondss << segment;
                       bool ls = 0;
                       bool rs = 0;
                       for(int i = 0; i < 3; i++)
                       {
                           std::getline(secondss, segment2, ',');
                           if(segment2 == "")
                           {
                               MessageBox(NULL, "Entered too few values1", "Error", MB_OK);
                               Error = true;
                               break;
                           }
                           else if(i == 1)
                           {
                               ls = std::stoi(segment2);
                           }
                           else if(i == 2)
                           {
                               rs = std::stoi(segment2);
                           }

                       }
                       if((rs | ls) == 0)
                       {
                           MessageBox(NULL, "Construction unstable", "Error", MB_OK);
                           Error = true;
                           break;
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
                           if(segment2 == "")
                           {
                               MessageBox(NULL, "Entered too few values2", "Error", MB_OK);
                               Error = true;
                               break;
                           }
                           if(i < 4)
                           {
                               if(std::stod(segment2)<=0)
                               {
                                    MessageBox(NULL, "Entered non-positive L/A/E/Q", "Error", MB_OK);
                                    Error = true;
                                    break;
                               }
                           }
                       }
                    }
                 }
                nameFileout.close();
                if(Error == false)
                {
                    isActive = 0;
                    std::ofstream ofs;
                    ofs.open(usedFileName, std::ios::out);
                    ofs << textBox->getString();
                    ofs.close();
                }
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

