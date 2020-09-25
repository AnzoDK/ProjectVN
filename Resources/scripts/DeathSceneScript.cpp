#include "DeathSceneScript.h"
using namespace rp;
void DeathSceneScript::Update(Scene& currScene, Base& currObj)
{
            std::cout << "Updating Script: " << GetName() << std::endl;
            DeathAnimation& ds = dynamic_cast<DeathAnimation&>(currObj);
            if(ds.IsDone())
            {
                ds.Reverse();
            }
            
}
