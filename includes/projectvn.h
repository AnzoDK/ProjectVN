#pragma once
#include "RPEngine/RPEngine.h"
#include "RPEngine/RPIni.h"
using namespace rp;
//Here is where we create all the objects we need for the game

class Game
{
    public:
        Game();
        ~Game(){delete(Game::Engine);};
        void init();
        static RosenoernEngine* Engine;
        static void Exit();
        static void Start();
        static void SwitchScene(int sceneID);
    private:
        
};

class MainMenu : public UIMenu
{
    public:
        MainMenu();
        ~MainMenu()
        {
            UIElements.clear();
          
        }
        void Init() override;
        void Parse(std::vector<Base*>& vec) override;
        void ExportObjects(Scene& scene);
    private:
        std::vector<Base*> UIElements;
};

class OptionsButton : public Button
{
    public:
        OptionsButton();
        ~OptionsButton()
        {
          delete(buttonImg);  
        }
        ButtonImage* GetImg();
        void SetImg(std::string path);
        void Init() override;
        void Draw() override;
        void Parse(std::vector<Base*>& vec) override;
    private:
        ButtonImage* buttonImg;
};
class OptionsMenu : public MainMenu
{
    public:
        OptionsMenu();
        void Init() override;
        void Parse(std::vector<Base*>& vec) override;
        ~OptionsMenu();
    private:
        std::vector<Base*> UIElements;
};

class DeathAnimation : public SimpleAnimationBase
{
    public:
        DeathAnimation(){Init(); _reverse = 0;}
        virtual ~DeathAnimation(){}
        virtual void Init() override;
        virtual void Update() override;
        void Reverse();
    private:
        float r;
        float a;
        Base* obj;
        bool _reverse;
        
};

class DeathScene : public Scene
{
    public:
        DeathScene(){Init();}
        void Init();
        ~DeathScene(){}
    private:
        
};

