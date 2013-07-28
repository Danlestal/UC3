 
#ifndef UC3APP_HPP
#define UC3APP_HPP
 
 
#include "OgreFramework.h"
#include "BasicApp.h"
 
class Uc3App : public BasicApp
{
	private:
		Ogre::SceneNode*			m_pOgreHeadNode;
		Ogre::Entity*				m_pOgreHeadEntity;
		
		virtual void setupScene();
};

#endif 
 
