#include "DeathSceneScript.h"
using namespace rp;
void DeathSceneScript::Update(Scene& currScene, Base& currObj)
{
            DeathAnimation& ds = dynamic_cast<DeathAnimation&>(currObj);
            std::cout << "Not done " << std::endl;
            if(ds.IsDone())
            {
                ds.Reverse();
            }
            
}
