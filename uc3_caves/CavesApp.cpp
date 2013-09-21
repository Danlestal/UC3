#include "CavesApp.h"
#include "UberCube.h"
#include "CubeWalker.h"
#include "MarchingCubes.h"
#include "SquareDensityBrush.h"
#include "CubePolisher.h"

void CavesApp::setupScene()
{
	Ogre::SceneManager *ogreManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;

    
    ogreManager->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    ogreManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);

    
    Ogre::ColourValue fadeColour(0.5, 0.5, 0.9);
    ogreManager->setFog(Ogre::FOG_LINEAR, fadeColour, 5.0, 10, 500);
    
    
	Ogre::SceneNode *cameraNode = OgreFramework::getSingletonPtr()->m_cameraNode;


    Ogre::Light* pointLight = ogreManager->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);
    pointLight->setCastShadows(true);
    cameraNode->attachObject(pointLight);


    /*
	Ogre::Light* spotLight = ogreManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(1.0, 0, 0);
    spotLight->setSpecularColour(1.0, 0, 0);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    spotLight->setCastShadows(true);
    cameraNode->attachObject(spotLight);
    */
	
	// Create the huge cube.
	UberCube *cube = new UberCube();
    CubeWalker walker = CubeWalker(new SquareDensityCubeBrush(12), Ogre::Vector3(0,0,0),Ogre::Vector3(UBERCUBE_SIZE - 1,UBERCUBE_SIZE - 1,UBERCUBE_SIZE - 1),2);
	walker.GenerateDensityCube(cube);
    
    CubePolisher polisher;
    polisher.PolishCube(cube);
    polisher.PolishCube(cube);
    polisher.PolishCube(cube);

    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("CustomMesh", "General");
    MarchingCubes algorithm;
    algorithm.Poligonize(cube, mesh);
    

    Ogre::Entity *entity = ogreManager->createEntity("CustomEntity", "CustomMesh", "General");
    entity->setMaterialName("UC3/RockWall");
    entity->setCastShadows(false);

    
    Ogre::SceneNode* node = ogreManager->getRootSceneNode()->createChildSceneNode("caveNode");

 
    node->setPosition(0,0,0);
    node->attachObject(entity);
	node->scale(6,6,6);
}


void CavesApp::updateLogic()
{
	
}