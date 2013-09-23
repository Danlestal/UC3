#ifndef IDENSITYCUBEGENERATOR_H
#define IDENSITYCUBEGENERATOR_H

#include "UberCube.h"
#include "Ogre.h"

class IDensityCubeGenerator
{
    public:
    virtual void GenerateDensityCube(UberCube* uberCube, Ogre::Vector3 source, Ogre::Vector3 destination) = 0;
};
#endif