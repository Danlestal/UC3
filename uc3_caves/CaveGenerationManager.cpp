#include "CaveGenerationManager.h"

void CaveGenerationManager::CreateNewRegion(Ogre::Vector3 cubePosition, Ogre::Vector3 cubeEntrance)
{
}


CaveRegion CaveGenerationManager::CreateNextRegion(CaveRegion previousRegion, int exitNumberWhereAttachNewRegion)
{
    Ogre::Vector3  exitPosition = previousRegion.GetLocalPositionExit(exitNumberWhereAttachNewRegion);
    UberCube *previousCube = previousRegion.GetDensityCube();

    UberCube fethCube = *previousCube;

    

}