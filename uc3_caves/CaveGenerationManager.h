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
        CaveRegion CreateNextRegion(CaveRegion previousRegion);
        CaveRegion CreateNextRegion(CaveRegion previousRegion, int exitNumberWhereAttachNewRegion);

        void CreateNewRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance);
};
#endif