#include "Uc3App.h"
#include "Terrain.h"
#include "RandomTerrain.h"

Uc3App::Uc3App()
{
	m_pOgreHeadNode = 0;
	m_pOgreHeadEntity = 0;
}

Uc3App::~Uc3App()
{
       delete OgreFramework::getSingletonPtr();
}
 
void Uc3App::start()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre("Uc3App v0.1", Ogre::SceneType::ST_GENERIC, this, 0))
		return;

	m_bShutdown = false;
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");
	setupScene();
	runDemo();
}
 
void Uc3App::setupScene()
{
	/*
	Ogre::Plane plane;
	plane.d = 100;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setSkyPlane(true, plane, "Examples/SpaceSkyPlane", 1500, 75);
	OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("Light")->setPosition(75,75,75);
	m_pOgreHeadEntity = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("OgreHeadEntity", "ogrehead.mesh");
	m_pOgreHeadNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
	m_pOgreHeadNode->attachObject(m_pOgreHeadEntity);
	*/

}
  
void Uc3App::runDemo()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Start main loop...");
 
	double timeSinceLastFrame = 0;
	double startTime = 0;
 
      OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
 
	while(!m_bShutdown && !OgreFramework::getSingletonPtr()->isOgreToBeShutDown()) 
	{
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isClosed())m_bShutdown = true;
 
		Ogre::WindowEventUtilities::messagePump();
 
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isActive())
		{
			startTime = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();
 
			OgreFramework::getSingletonPtr()->m_pKeyboard->capture();
			OgreFramework::getSingletonPtr()->m_pMouse->capture();
 
			OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);
			OgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();
 
			timeSinceLastFrame = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}
 
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Shutdown OGRE...");
}
 
bool Uc3App::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
 
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_F))
	{
		 //do something
	}
 
	return true;
}
 
bool Uc3App::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
 
	return true;
}
