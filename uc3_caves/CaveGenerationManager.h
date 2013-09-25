#ifndef CaveGenerationManager_h
#define CaveGenerationManager_h

#include "Ogre.h"
#include "CaveRegionGenerator.h"

class CaveGenerationManager
{
    private:
        CaveRegionGenerator mGenerator;
        Ogre::SceneNode mCameraNode;
        CaveRegion mCurrentRegion;
        std::map <int, CaveRegion> mRegions;
   
    public:
        void CreateNewRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance);
};
#endif