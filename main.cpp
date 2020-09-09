#include <iostream>
#include <cstring>
#include "includes/projectvn.h"
int main(int argc, char *argv[])
{
    bool test = 0;
    int tstCount = 0;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i],"--test") == 0)
        {
            test = 1;
            tstCount = 1000;
        }
    }
    using namespace rp;
    std::cout << "Hello, world!" << std::endl;
    Game* game = new Game();
    game->init();
    RosenoernAudio& ra = Game::Engine->GetAudioController();
    /*ra.AddToQueue("Resources/sound/music/mp3.mp3");
    ra.PlayFromQueue();*/
    Ini ini = Ini("test.ini");
    std::cout << atoi(ini.GetKey("Game Settings")->GetSubKey("playerHeight").c_str()) << std::endl;
    while(Game::Engine->isRunning)
    {
      if(test)
      {
          tstCount--;
          std::cout << tstCount << std::endl;
      }
      Game::Engine->Update();
      if(tstCount <= 0 && test)
      {
          Game::Engine->isRunning = false;
      }
    }
    
    delete(game);
    return 0;
}
