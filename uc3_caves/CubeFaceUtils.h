#ifndef CUBEFACEUTILS_H
#define CUBEFACEUTILS_H

#include "OgreFramework.h"

enum CubeFace
{
    TOP,
    BOTTON,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

inline CubeFace GetOpossiteFace(CubeFace nextRegionExit)
{
	switch(nextRegionExit)
	{
		case TOP:
			return CubeFace::BOTTON;
        
        case BOTTON:
			return CubeFace::TOP;
        
        case LEFT:
			return CubeFace::RIGHT;
        
        case RIGHT:
			return CubeFace::LEFT;
        
        case FRONT:
			return CubeFace::BACK;
        
        case BACK:
			return CubeFace::FRONT;
	}
}

inline Ogre::Vector3 GetIncrementVector(CubeFace currentRegionExit)
{
	switch(currentRegionExit)
	{
		case TOP:
			return Ogre::Vector3(0, 1, 0);
        
        case BOTTON:
			return Ogre::Vector3(0, -1, 0);
        
        case LEFT:
			return Ogre::Vector3(-1, 0, 0);
        
        case RIGHT:
			return Ogre::Vector3(1, 0, 0);
        
        case FRONT:
			return Ogre::Vector3(0, 0, -1);
        
        case BACK:
			return Ogre::Vector3(0, 0, 1);
	}
}
#endif
