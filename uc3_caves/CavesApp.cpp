#include "CavesApp.h"
#include "UberCube.h"
#include "CubeWalker.h"
#include "MarchingCubes.h"
#include "SquareDensityBrush.h"
#include "CubePolisher.h"
#include "CaveRegion.h"

#include "CaveRegionGenerator.h"
#include "ICubeSmoother.h"
#include "StandardCubeSmoother.h"

void CavesApp::setupScene()
{
	Ogre::SceneManager *ogreManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;
    ogreManager->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    ogreManager->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);

    
    Ogre::ColourValue fadeColour(0.5, 0.5, 0.9);
    ogreManager->setFog(Ogre::FOG_LINEAR, fadeColour, 5.0, 10, 500);
    
    
	Ogre::SceneNode *cameraNode = OgreFramework::getSingletonPtr()->m_cameraNode;
    
	Ogre::Light* spotLight = ogreManager->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(1.0, 0, 0);
    spotLight->setSpecularColour(1.0, 0, 0);
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
    spotLight->setCastShadows(true);
    cameraNode->attachObject(spotLight);
    

    // All the cave generation stuff.
    mBrush = new SquareDensityCubeBrush(10);
    mWalker = new CubeWalker(mBrush, 10);
    mSmoother = new StandardCubeSmoother(2);
    CaveRegionGenerator generator = CaveRegionGenerator(mWalker, mSmoother);
    mRegion = generator.GenerateCaveRegion(Ogre::Vector3::ZERO, Ogre::Vector3::ZERO, Ogre::Vector3(UBERCUBE_SIZE,UBERCUBE_SIZE,UBERCUBE_SIZE));


    // Cave Poligonization.
    Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual("CustomMesh", "General");
    MarchingCubes algorithm;
    algorithm.Poligonize(mRegion->GetDensityCube(), mesh);
    

    Ogre::Entity *entity = ogreManager->createEntity("CustomEntity", "CustomMesh", "General");
    entity->setMaterialName("UC3/RockWall");
    entity->setCastShadows(false);

    
    Ogre::SceneNode* node = ogreManager->getRootSceneNode()->createChildSceneNode("caveNode");

 
    node->setPosition(0,0,0);
    node->attachObject(entity);
	node->scale(6,6,6);
}

void CavesApp::cleanScene()
{
    delete mBrush;
    delete mSmoother;
    delete mWalker;
    delete mRegion;
}


void CavesApp::updateLogic()
{
}