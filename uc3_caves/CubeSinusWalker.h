#ifndef CUBESINUSWALKER_H
#define CUBESINUSWALKER_H

#include "IDensityCubeGenerator.h"

class CubeSinusWalker : public IDensityCubeGenerator
{
    private:
    
    public:
    void GenerateDensityCube(UberCube* uberCube, Ogre::Vector3 source, Ogre::Vector3 destination);
};
#endif