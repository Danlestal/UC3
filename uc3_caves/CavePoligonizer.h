#ifndef CAVEPOLIGONIZER_H
#define CAVEPOLIGONIZER_H

#include "OgreFramework.h"
#include "CaveRegion.h"
#include "MarchingCubes.h"
#include "CubeFaceUtils.h"

class CavePoligonizer
{
	private:
		MarchingCubes mMarchingCubesAlgorithm;

	public:
		CavePoligonizer() : mMarchingCubesAlgorithm(MarchingCubes())
		{
		}

		Ogre::ManualObject* Poligonize(CaveRegion region);
		std::map<CubeFace, Ogre::ManualObject*> PoligonizeNeighbours(CaveRegion region,  Ogre::ManualObject* mainRegionManualObject);
		Ogre::ManualObject* PoligonizeNeighbour(CaveRegion region, CubeFace faceWithNeighbour);

};
#endif