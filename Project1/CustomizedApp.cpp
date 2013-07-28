#include "CustomizedApp.h"

void CustomizedApp::setupScene()
{
	Ogre::SceneManager * ogreManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;
	ogreManager->createLight("Light")->setPosition(75,75,75);
	Ogre::Plane floorPlane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
													floorPlane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	
	Ogre::SceneNode *floorNode = ogreManager->getRootSceneNode()->createChildSceneNode("floorNode");
	Ogre::Entity* entGround = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("GroundEntity", "ground");
	entGround->setMaterialName("UC3/Basic");
	entGround->setCastShadows(true);
	ogreManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

}
