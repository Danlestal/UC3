#include "CavesApp.h"
#include "UberCube.h"
#include "CubeWalker.h"
#include "MarchingCubes.h"
#include "SquareDensityBrush.h"
#include "CubePolisher.h"
#include "CaveRegion.h"

#include "CaveGenerationManager.h"
#include "CaveRegionGenerator.h"
#include "ICubeSmoother.h"
#include "StandardCubeSmoother.h"
#include "CavePoligonizer.h"

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
    mWalker = new CubeWalker(mBrush, 1);
    mSmoother = new StandardCubeSmoother(6);
    CaveRegionGenerator generator = CaveRegionGenerator(mWalker, mSmoother);

    CaveGenerationManager manager = CaveGenerationManager(generator);
    mRegion = manager.CreateFirstRegion(CubeFace::TOP);

    // Cave Poligonization.
	CavePoligonizer poligonizer = CavePoligonizer();
	Ogre::MeshPtr mesh =poligonizer.Poligonize(*mRegion);


	char regionName[50];
	mRegion->GetID(regionName);


    Ogre::Entity *entity = ogreManager->createEntity(regionName, regionName, "General");
    entity->setMaterialName("UC3/RockWall");
    entity->setCastShadows(false);
    
    Ogre::SceneNode* node = ogreManager->getRootSceneNode()->createChildSceneNode("caveNode");
    node->setPosition(0,0,0);
    node->attachObject(entity);


	
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