#include "CavesApp.h"
#include "UberCube.h"
#include "CubeWalker.h"
#include "MarchingCubes.h"

void CavesApp::setupScene()
{
	Ogre::SceneManager * ogreManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;
	ogreManager->createLight("Light")->setPosition(0,0,0);

    Ogre::ColourValue fadeColour(0.6, 0.6, 0.9);
    ogreManager->setFog(Ogre::FOG_LINEAR, fadeColour, 5.0, 20, 500);

	Ogre::SceneNode *cameraNode = OgreFramework::getSingletonPtr()->m_cameraNode;
	
	Ogre::Light* pointLight = ogreManager->createLight("pointLight");
	pointLight->setCastShadows(true);
	pointLight->setPowerScale(100);
	

    pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);
  

	cameraNode->attachObject(pointLight);



	
	// Create the huge cube.
	UberCube *cube = new UberCube();

    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("CustomMesh", "General");

    
    CubeWalker *walker = new CubeWalker(cube, Ogre::Vector3(0,0,0),Ogre::Vector3(UBERCUBE_SIZE - 1,UBERCUBE_SIZE - 1,UBERCUBE_SIZE - 1),2);
	walker->GenerateDensityCube();
    
    
    MarchingCubes algorithm;
    algorithm.Poligonize(cube, mesh);
    

    Ogre::Entity *entity = ogreManager->createEntity("CustomEntity", "CustomMesh", "General");
    entity->setMaterialName("UC3/Basic");
	entity->setCastShadows(true);

    Ogre::SceneNode* node = ogreManager->getRootSceneNode()->createChildSceneNode("caveNode");

 
    node->setPosition(0,0,0);
    node->attachObject(entity);
	node->scale(20,20,20);

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