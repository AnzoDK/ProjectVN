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
    while(Game::Engine->isRunning)
    {
      Game::Engine->Update();
    }
    
    delete(game);
    return 0;
}
