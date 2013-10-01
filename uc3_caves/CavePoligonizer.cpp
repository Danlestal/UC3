#include "CavePoligonizer.h"


 Ogre::ManualObject* CavePoligonizer::Poligonize(CaveRegion region)
{
	char regionName[50];
	region.GetID(regionName);

    Ogre::ManualObject *manual = OgreFramework::getSingletonPtr()->m_pSceneMgr->createManualObject(regionName);

	mMarchingCubesAlgorithm.Poligonize(region.GetDensityCube(), manual);
	return manual;
}