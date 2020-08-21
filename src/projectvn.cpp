#include "../includes/projectvn.h"
using namespace rp;
RosenoernEngine* Game::Engine = new RosenoernEngine(1,10);

void Game::Exit()
{
    std::cout << "Exiting.." << std::endl;
    Game::Engine->Quit();
}

Game::Game()
{
    
}

void Game::init()
{
  Game::Engine->init();
  Game::Engine->CreateMainWindow("ProjectVN",0);
  MainMenu* mm = new MainMenu();
  mm->SetName("MainMenu");
  Scene* s = new Scene();
  s->AddObject(mm);
  Game::Engine->SetScene(s);
  Game::Engine->SetFPS(60);
  
  
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
    OptionsButton* optionsBtn = new OptionsButton();
    void (*funPtr)(){&Game::Exit};
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
    optionsBtn->SetName("optionsBtn");
    optionsBtn->GetUIText()->SetFont("Resources/fonts/Requiem.ttf");
    optionsBtn->GetUIText()->SetFontSize(100);
    optionsBtn->GetUIText()->SetTextColor(CommonColor::Black);
    startGameBtn->GetRect()->h = RosenoernEngine::height/10;
    startGameBtn->GetRect()->w = RosenoernEngine::width/5;
    startGameBtn->GetRect()->y = RosenoernEngine::height/10;
    startGameBtn->GetRect()->x = 2*(RosenoernEngine::width/5);
    exitGameBtn->GetRect()->h = RosenoernEngine::height/10;
    exitGameBtn->GetRect()->w = RosenoernEngine::width/5;
    exitGameBtn->GetRect()->y = RosenoernEngine::height-(2*RosenoernEngine::height/10);
    exitGameBtn->GetRect()->x = 2*(RosenoernEngine::width/5);
    optionsBtn->GetRect()->h = RosenoernEngine::height/10;
    optionsBtn->GetRect()->w = optionsBtn->GetRect()->h;
    optionsBtn->GetRect()->x = RosenoernEngine::width-optionsBtn->GetRect()->w;
    optionsBtn->GetRect()->y = RosenoernEngine::height-optionsBtn->GetRect()->w;
    UIElements.push_back(startGameBtn);
    UIElements.push_back(exitGameBtn);
    UIElements.push_back(optionsBtn);
    UIElements.push_back(optionsBtn->GetImg());
    UIElements.push_back(back);
}

void MainMenu::Update()
{
  std::sort(UIElements.begin(),UIElements.end());
  for(int i = 0; i < UIElements.size();i++)
  {
    UIElements.at(i)->Update();
  }
}
void MainMenu::Draw()
{
    std::sort(UIElements.begin(),UIElements.end());
    for(int i = 0; i < UIElements.size();i++)
    {
        std::cout << "Object: " << UIElements.at(i)->GetName() << " Z index: " << UIElements.at(i)->GetZ() << std::endl;
        //std::cout << "Name: " << UIElements.at(i)->GetName() << std::endl;
        UIElements.at(i)->Draw();
    }
}
OptionsButton::OptionsButton()
{
  Init();
}
void OptionsButton::Init()
{
    buttonImg = new ButtonImage("Resources/textures/gear.png");
    buttonImg->SetZ(1);
    buttonImg->SetName("OptionsButtonImage");
    GetRect()->h = RosenoernEngine::height/10;
    GetRect()->w = RosenoernEngine::height/10;
    GetRect()->x = RosenoernEngine::width - GetRect()->h;
    GetRect()->y = RosenoernEngine::height - GetRect()->h;
    SDL_Rect* rr = new SDL_Rect();
    rr->h = GetRect()->h*0.8;
    rr->w = GetRect()->w*0.8;
    rr->x = GetRect()->x + (GetRect()->w/8);
    rr->y = GetRect()->y + (GetRect()->h/8);
    buttonImg->SetRect(rr);
    
}
void OptionsButton::Draw()
{
  if(IsEnabled())
    {
        SDL_Rect* rr = new SDL_Rect();
        rr->h = GetRect()->h*0.8;
        rr->w = GetRect()->w*0.8;
        rr->x = GetRect()->x + (GetRect()->w/8);
        rr->y = GetRect()->y + (GetRect()->h/8);
        buttonImg->SetRect(rr);
        /*std::cout << "Path for resource is: " + GetGraphic()->GetFile()->GetPath() << std::endl;*/
        SDL_Surface* tmpSurf = IMG_Load(GetGraphic()->GetFile()->GetPath().c_str());
        //SDL_Surface* tmpSurf = IMG_Load("testImg.png");
        SDL_Texture* tex = SDL_CreateTextureFromSurface(RosenoernEngine::mainRender,tmpSurf);
        SDL_RenderCopy(RosenoernEngine::mainRender,tex, NULL,GetRect());
        SDL_FreeSurface(tmpSurf);
        SDL_DestroyTexture(tex);
        GetUIText()->SetRect(rr);
        GetUIText()->Draw();
    }  
}
void OptionsButton::SetImg(std::string path)
{
    delete(buttonImg);
    buttonImg = new ButtonImage(path);
    buttonImg->SetZ(1);
    buttonImg->SetName("OptionsButtonImage");
}
ButtonImage* OptionsButton::GetImg()
{
  return buttonImg;  
}


