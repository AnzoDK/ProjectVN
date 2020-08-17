#include "../includes/projectvn.h"
using namespace rp;
void Exit()
{
    std::cout << "Exiting.." << std::endl;
}

Game::Game()
{
    
}

void Game::init(RosenoernEngine* re)
{
  re->init();
  re->CreateMainWindow("ProjectVN",0);
  MainMenu* mm = new MainMenu();
  mm->SetName("MainMenu");
  Scene* s = new Scene();
  s->AddObject(mm);
  re->SetScene(s);
  
  
}


MainMenu::MainMenu()
{
    Init();
}

void MainMenu::Init()
{
    UIElements = std::vector<Base*>();
    Background* back = new Background("Resources/textures/btnDefault.png");
    back->SetName("Background01");
    Button* startGameBtn = new Button();
    Button* exitGameBtn = new Button();
    void (*funPtr)(){&Exit};
    exitGameBtn->SetFunction(funPtr);
    startGameBtn->SetName("startGameBtn");
    startGameBtn->SetFont("Resources/fonts/Requiem.ttf");
    startGameBtn->GetUIText()->SetTextColor(CommonColor::Black);
    startGameBtn->GetUIText()->SetFontSize(100);
    startGameBtn->SetUIText("Start Game");
    exitGameBtn->SetName("exitGameBtn");
    exitGameBtn->SetFont("Resources/fonts/Requiem.ttf");
    exitGameBtn->GetUIText()->SetTextColor(CommonColor::Black);
    exitGameBtn->GetUIText()->SetFontSize(100);
    exitGameBtn->SetUIText("Exit Game");
    startGameBtn->GetRect()->h = RosenoernEngine::height/10;
    startGameBtn->GetRect()->w = RosenoernEngine::width/5;
    startGameBtn->GetRect()->y = RosenoernEngine::height/10;
    startGameBtn->GetRect()->x = 2*(RosenoernEngine::width/5);
    exitGameBtn->GetRect()->h = RosenoernEngine::height/10;
    exitGameBtn->GetRect()->w = RosenoernEngine::width/5;
    exitGameBtn->GetRect()->y = RosenoernEngine::height-(2*RosenoernEngine::height/10);
    exitGameBtn->GetRect()->x = 2*(RosenoernEngine::width/5);
    UIElements.push_back(startGameBtn);
    UIElements.push_back(exitGameBtn);
    UIElements.push_back(back);
}
void MainMenu::Draw()
{
    std::sort(UIElements.begin(),UIElements.end());
    for(int i = 0; i < UIElements.size();i++)
    {
        //std::cout << "Name: " << UIElements.at(i)->GetName() << std::endl;
        UIElements.at(i)->Update();
        UIElements.at(i)->Draw();
    }
}

