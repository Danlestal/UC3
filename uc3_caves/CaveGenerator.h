#ifndef CaveGenerator_HPP
#define CaveGenerator_HPP

#include "OgreFramework.h"
#include "PseudoRandomWalker.h"

class CaveGenerator
{
	private:

		Ogre::Volume::CSGCubeSource *_caveCube;
		const Ogre::Vector3 _entrance;
		PseudoRandomWalker *_walker;

	public:
		  /** Constructor.
        @param min
            The lower back left corner of the cave.
        @param max
            The upper front right corner of the cave.
		@param entrance
			The entrance to the cave.
        */
		CaveGenerator(const Ogre::Vector3 &min, const Ogre::Vector3 &max, const Ogre::Vector3 entrance);
		Ogre::SceneNode* Generate(Ogre::Volume::Chunk *chunk);
};

#endif