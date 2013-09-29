#include "CavePoligonizer.h"


Ogre::MeshPtr CavePoligonizer::Poligonize(CaveRegion region)
{
	char regionName[50];
	region.GetID(regionName);

	Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(regionName, "General");
	mMarchingCubesAlgorithm.Poligonize(region.GetDensityCube(), mesh);
	return mesh;
}