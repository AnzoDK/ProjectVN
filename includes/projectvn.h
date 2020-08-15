#pragma once
#include "RPEngine/RPEngine.h"
using namespace rp;
//Here is where we create all the objects we need for the game



class MainMenu : public UIMenu
{
    public:
        MainMenu();
        void Init() override;
        void Draw() override;
    private:
        std::vector<UIBase*> UIElements;
};

