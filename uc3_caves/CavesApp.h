#ifndef CavesApp_HPP
#define CavesApp_HPP

#include "OgreFramework.h"
#include "BasicApp.h"
#include "PerlinNoiseGenerator.h"
#include "PseudoRandomWalker.h"
 
class CavesApp : public BasicApp
{
	private:
		Ogre::SceneNode *_cubeNode;
		Ogre::SceneNode *_randomWalkerNode;
		Ogre::SceneNode *_goal;
		PseudoRandomWalker *_walker;
		Ogre::Vector3 _sourcePosition;
		Ogre::Vector3 _destinationPosition;

		/// Holds the volume root.
		// Ogre::Volume::Chunk *_caveChunkHole;
		// Ogre::Volume::CSGUnionSource *_unionBuffer;

		Ogre::Volume::Chunk* caveChunk;

		virtual void setupScene();
	public:
		virtual void updateLogic();
};

#endif 
 
