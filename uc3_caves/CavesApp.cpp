#include "CavesApp.h"
#include "UberCube.h"
#include "CubeWalker.h"

void CavesApp::setupScene()
{
	Ogre::SceneManager * ogreManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;
	ogreManager->createLight("Light")->setPosition(75,75,75);

	// Create the huge cube.
	UberCube *cube = new UberCube();
	CubeWalker *walker = new CubeWalker(cube, Ogre::Vector3(0,0,0),Ogre::Vector3(999,999,999),10);
	walker->GenerateDensityCube();

	/*
	CaveGenerator *caveGenerator = new CaveGenerator(Ogre::Vector3::ZERO,
												     Ogre::Vector3::ZERO + 1000,
													 Ogre::Vector3(30,30,30)
													 );

	

	caveChunk = new Ogre::Volume::Chunk();
	Ogre::SceneNode *caveNode = caveGenerator->Generate(caveChunk);

	caveChunk->setMaterial("UC3/WaterStream");*/
}


void CavesApp::updateLogic()
{
	
}