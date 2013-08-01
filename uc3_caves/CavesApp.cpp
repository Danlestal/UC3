#include "CavesApp.h"
#include "UberCube.h"
#include "CubeWalker.h"
#include "MarchingCubes.h"

void CavesApp::setupScene()
{
	Ogre::SceneManager * ogreManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;
	ogreManager->createLight("Light")->setPosition(0,0,0);

    Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
    ogreManager->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 50, 500);
	// Create the huge cube.
	UberCube *cube = new UberCube();

    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("CustomMesh", "General");

    /*
    CubeWalker *walker = new CubeWalker(cube, Ogre::Vector3(0,0,0),Ogre::Vector3(UBERCUBE_SIZE - 1,UBERCUBE_SIZE - 1,UBERCUBE_SIZE - 1),2);
	walker->GenerateDensityCube();
    */
    
    MarchingCubes algorithm;
    algorithm.Poligonize(cube, mesh);
    

    Ogre::Entity *entity = ogreManager->createEntity("CustomEntity", "CustomMesh", "General");
    entity->setMaterialName("Ogre/Tusks");

    Ogre::SceneNode* node = ogreManager->getRootSceneNode()->createChildSceneNode("caveNode");

    node->scale(10,10,10);
    node->setPosition(0,0,0);
    node->attachObject(entity);

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