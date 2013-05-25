 
#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP
 
 
#include "OgreFramework.h"
 
class Uc3App : public OIS::KeyListener
{
	private:
        void setupScene();
		void runDemo();
		Ogre::SceneNode*			m_pOgreHeadNode;
		Ogre::Entity*				m_pOgreHeadEntity;
		bool m_bShutdown;

	public:
		Uc3App();
		~Uc3App();
 
		void start();
 		bool keyPressed(const OIS::KeyEvent &keyEventRef);
		bool keyReleased(const OIS::KeyEvent &keyEventRef);
};

#endif 
 
