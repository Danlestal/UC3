#include "CavePoligonizer.h"


 Ogre::ManualObject* CavePoligonizer::Poligonize(CaveRegion region)
{
	char regionName[50];
	region.GetID(regionName);

    Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(regionName);

	mMarchingCubesAlgorithm.Poligonize(region.GetDensityCube(), manual);
	return manual;
}


std::map<CubeFace, Ogre::ManualObject*> CavePoligonizer::PoligonizeNeighbours(CaveRegion region)
{
	std::map<CubeFace, Ogre::ManualObject*> result;
	
	std::map<CubeFace, CaveRegion*>::iterator neighboursMapIterator;
	for (neighboursMapIterator = region.GetNeighbours().begin(); neighboursMapIterator != region.GetNeighbours().end(); ++neighboursMapIterator)
	{
    }
    return result;
}

Ogre::ManualObject* CavePoligonizer::PoligonizeNeighbour(CaveRegion region, CubeFace faceWithNeighbour)
{

	return nullptr;
}