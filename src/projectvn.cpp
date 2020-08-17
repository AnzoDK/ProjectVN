#include "../includes/projectvn.h"
using namespace rp;

MainMenu::MainMenu()
{
    Init();
}

void MainMenu::Init()
{
    UIElements = std::vector<UIBase*>();
    Button* startGameBtn = new Button();
    Button* exitGameBtn = new Button();
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
}
void MainMenu::Draw()
{
    for(int i = 0; i < UIElements.size();i++)
    {
        UIElements.at(i)->Draw();
    }
}

