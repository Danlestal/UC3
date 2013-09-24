 
#ifndef BASICAPP_HPP
#define BASICAPP_HPP
 
#include "OgreFramework.h"
 
class BasicApp : public OIS::KeyListener
{
	private:
        bool m_bShutdown;

        virtual void setupScene() = 0;
        virtual void cleanScene() = 0;

		void BasicApp::runDemo()
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
					updateLogic();
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

            cleanScene();
 
	        OgreFramework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
	        OgreFramework::getSingletonPtr()->m_pLog->logMessage("Shutdown OGRE...");
        }

		

public:
		BasicApp()
		{
		};
		~BasicApp()
		{
			delete OgreFramework::getSingletonPtr();
		}
		virtual void updateLogic()
		{}
		void start()
		{
			new OgreFramework();
			if(!OgreFramework::getSingletonPtr()->initOgre("Uc3App v0.1", Ogre::SceneType::ST_GENERIC, this, 0))
			return;

			m_bShutdown = false;
			OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");
			setupScene();
			runDemo();
		}
 		virtual bool keyPressed(const OIS::KeyEvent &keyEventRef)
		{
			OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
 /*
			if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_F))
			{
				 //do something
			}
 */
			return true;
		}
		virtual bool keyReleased(const OIS::KeyEvent &keyEventRef)
		{
			OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
			return true;
		}
};
#endif 
 
