#include "../includes/projectvn.h"
#include <SDL2/SDL_opengl.h>
using namespace rp;
RosenoernEngine* Game::Engine = new RosenoernEngine(1,10);
//Game
void Game::SwitchScene(int SceneID)
{
    //This is just a lookup table for scenes
    switch(SceneID)
    {
        default:
            Game::Engine->SetScene(new DeathScene());
        break;
    }
}

void Game::Exit()
{
    Game::Engine->Log("Exiting..");
    Game::Engine->Quit();
}

void Game::Start()
{
  Game::Engine->Log("Starting!");
  Game::SwitchScene(0);
  
}

Game::Game()
{
    
}

void Game::init()
{
  Game::Engine->init();
  Game::Engine->CreateMainWindow("ProjectVN",0,1);
  MainMenu* mm = new MainMenu();
  OptionsMenu* om = new OptionsMenu();
  mm->SetName("MainMenu");
  om->SetName("OptionsMenu");
  Scene* s = new Scene();
  s->AddObject(mm);
  s->AddObject(om);
  Game::Engine->SetScene(s);
  Game::Engine->SetFPS(60);
  
  
}

//Menus
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
    /*Don't do this unless you're forced to -->*/void (*funPtr)(){&Game::Exit};
    /*I beg you not to do this*/exitGameBtn->SetFunction(funPtr);
    startGameBtn->SetName("startGameBtn");
    startGameBtn->SetFont("Resources/fonts/Requiem.ttf");
    startGameBtn->GetUIText()->SetTextColor(CommonColor::Black);
    startGameBtn->GetUIText()->SetFontSize(100);
    startGameBtn->SetUIText("Start Game");
    /*There is so many things wrong with this... -->*/ void (*startPtr)(){&Game::Start};
    /*Imagine if the void wasn't static... Then you would be in deep shit -->*/ startGameBtn->SetFunction(startPtr);
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
    UIElements.push_back(back);
}

void MainMenu::ExportObjects(Scene& scene)
{
  std::sort(UIElements.begin(),UIElements.end());
  for(unsigned int i = 0; i < UIElements.size();i++)
  {
    scene.AddObject(UIElements.at(i));
  }
}
void MainMenu::Parse(std::vector<Base*>& vec)
{
    
    if(IsEnabled())
    {
        
        for(unsigned int i = 0; i < UIElements.size();i++)
        {
            //vec.push_back(UIElements.at(i));
            UIElements.at(i)->Parse(vec);
        }
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
        //buttonImg->SetRect(rr);
        /*std::cout << "Path for resource is: " + GetGraphic()->GetFile()->GetPath() << std::endl;*/
        SDL_Surface* tmpSurf = IMG_Load(GetGraphic()->GetFile()->GetPath().c_str());
        //SDL_Surface* tmpSurf = IMG_Load("testImg.png");
        SDL_Texture* tex = SDL_CreateTextureFromSurface(RosenoernEngine::mainRender,tmpSurf);
        SDL_SetTextureColorMod(tex,TexMod.modR,TexMod.modB,TexMod.modG);
        SDL_SetTextureAlphaMod(tex,TexMod.modR);
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
void OptionsButton::Parse(std::vector<Base*>& vec)
{
  if(IsEnabled())
  {
      vec.push_back(GetImg());
      vec.push_back(this);
  }
}



OptionsMenu::OptionsMenu()
{
    Init();
}
OptionsMenu::~OptionsMenu()
{
   /*Dont do this --> for(unsigned int i = 0; i < UIElements.size();i++)
    {
      delete(UIElements.at(i));  
    }*/
   
   /*Do this -->*/ UIElements.clear();
}
void OptionsMenu::Parse(std::vector<Base*>& vec)
{
    if(IsEnabled())
    {
      for(unsigned int i = 0; i < UIElements.size();i++)
      {
          UIElements.at(i)->Parse(vec);
      }
    }
}

void OptionsMenu::Init()
{
    UIElements = std::vector<Base*>();
    Background* bg = new Background("Resources/textures/btnDefault.png");
    bg->SetEnabled(false);
    UIElements.push_back(bg);
}

//Animations
/*DeathAnimation::DeathAnimation()
{
  Init();  
}*/
void DeathAnimation::Init()
{
    a = 0;
    r = 0;
    obj = nullptr;
    SetStatus(RunningState::Running);
}
void DeathAnimation::Update()
{
    if(!IsDone() && GetStatus()==RunningState::Running)
    {
        if(Game::Engine->GetSceneObject("Background01")!= nullptr && obj == nullptr)
        {
            obj = Game::Engine->GetSceneObject("Background01");
            obj->TexMod.modB = 0;
            obj->TexMod.modG = 0;
        }
        else
        {
            obj->TexMod.modR = r;
            obj->TexMod.modA = a;
            if(r < 255)
            {
                r+= 0.5f;
            }
            if(a < 255)
            {
                a+= 0.5f; //This should be converted to an int in a floor like way
            }
            if(r == 255 && a == 255)
            {
                SetDone(1);
                SetStatus(RunningState::Stopped);
            }
        
        }
    }
}



//Scenes
void DeathScene::Init()
{
    UIText* deathTXT = new UIText("Resources/fonts/Requiem.ttf","Is This Your End? Or Will You Rise To Supress Your Destiny?", 125, 0,Game::Engine->height/6*2,Game::Engine->width,Game::Engine->height/5);
    deathTXT->SetZ(1);
    deathTXT->SetName("DeathText");
    DeathAnimation* DA = new DeathAnimation();
    Background* bg = new Background("Resources/textures/bg0.png");
    bg->TexMod.modA = 0;
    bg->TexMod.modB = 0;
    bg->TexMod.modG = 0;
    bg->TexMod.modR = 0;
    bg->SetZ(-1);
    bg->SetName("Background01");
    DA->SetName("BGAnimation");
    AddObject(deathTXT);
    AddObject(DA);
    AddObject(bg);
    
}
//New object Registers
DerivedRegister<OptionsButton> OptionsButton::reg("OptionsButton");
