#pragma once
#include "RPEngine/RPEngine.h"
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
    private:
        
};

class MainMenu : public UIMenu
{
    public:
        MainMenu();
        void Init() override;
        void Draw() override;
        void Update() override;
    private:
        std::vector<Base*> UIElements;
};

