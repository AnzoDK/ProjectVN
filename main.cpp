#include <iostream>
#include "../includes/projectvn.h"
int main(int argc, char **argv)
{
    using namespace rp;
    std::cout << "Hello, world!" << std::endl;
    RosenoernEngine* re = new RosenoernEngine(1,10);
    RosenoernAudio& ra = re->GetAudioController();
    re->init();
    re->CreateMainWindow("ProjectVN",0);
    Scene* s = new Scene();
    MainMenu* mm = new MainMenu();
    s->AddObject(mm);
    re->SetScene(s);
    while(re->isRunning)
    {
      re->Update();
    }
    
    delete(re);
    return 0;
}
