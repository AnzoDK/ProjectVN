#include <iostream>
#include "../includes/projectvn.h"
int main(int argc, char **argv)
{
    using namespace rp;
    std::cout << "Hello, world!" << std::endl;
    RosenoernEngine* re = new RosenoernEngine(1,10);
    RosenoernAudio& ra = re->GetAudioController();
    Game* game = new Game();
    game->init(re);
    while(re->isRunning)
    {
      re->Update();
    }
    
    delete(re);
    return 0;
}
