#pragma once
#include "RPEngine/RPSceneScript.h"
#include "RPEngine/RPScene.h"
#include "projectvn.h"

namespace rp
{
class DeathSceneScript : public SceneScriptBase
{
    public:
        DeathSceneScript(){}
        virtual ~DeathSceneScript(){}
        virtual void Update(Scene& currScene, Base& currObj) override;
    private:
    
};
}


