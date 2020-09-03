#include <iostream>
#include "../includes/projectvn.h"
int main(int argc, char **argv)
{
    using namespace rp;
    std::cout << "Hello, world!" << std::endl;
    Game* game = new Game();
    game->init();
    RosenoernAudio& ra = Game::Engine->GetAudioController();
    /*ra.AddToQueue("Resources/sound/music/mp3.mp3");
    ra.PlayFromQueue();*/
    Ini ini = Ini("test.ini");
    if(ini.GetKey("Video")->name != "Invalid")
    {
        if(ini.GetKey("Video")->GetSubKey("width") != "-2")
        {
            std::cout << atoi(ini.GetKey("Display")->GetSubKey("width").c_str()) << std::endl;
        }
        
    }
    while(Game::Engine->isRunning)
    {
      Game::Engine->Update();
    }
    
    delete(game);
    return 0;
}
