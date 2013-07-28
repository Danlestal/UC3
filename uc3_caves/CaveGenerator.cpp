#include "CaveGenerator.h"



CaveGenerator::CaveGenerator(const Ogre::Vector3 &min, const Ogre::Vector3 &max, const Ogre::Vector3 entrance)
{
	_caveCube = new Ogre::Volume::CSGCubeSource(min,max);
	_walker = new PseudoRandomWalker(entrance,max-50,100,true);
}


Ogre::SceneNode* CaveGenerator::Generate(Ogre::Volume::Chunk *chunk)
{
	while(!_walker->GoalReached())
	{
		_walker->GenerateRandomStep();
	}

	
	Ogre::Real halfWidth = 10;

	std::list<Ogre::Vector3> *walkerJournal = _walker->GetJournal();
	std::list<Ogre::Vector3>::const_iterator iterator = walkerJournal->begin();

	Ogre::Volume::CSGCubeSource *firstCube = new Ogre::Volume::CSGCubeSource(*iterator-10, *iterator+10);
	iterator++;
	Ogre::Volume::CSGUnionSource *caveHole = new Ogre::Volume::CSGUnionSource(firstCube, new Ogre::Volume::CSGCubeSource(*iterator-10, *iterator+10));
	
	for (; iterator != walkerJournal->end(); ++iterator) 
	{
		caveHole = new Ogre::Volume::CSGUnionSource(caveHole, new Ogre::Volume::CSGCubeSource(*iterator-10, *iterator+10));
	}

	

	Ogre::Volume::ChunkParameters parameters;
    parameters.sceneManager = OgreFramework::getSingletonPtr()->m_pSceneMgr;
    parameters.src = caveHole;
    parameters.baseError = (Ogre::Real)1;
	Ogre::SceneNode *caveNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode("CaveVolume");

    chunk->load(caveNode, Ogre::Vector3::ZERO, Ogre::Vector3(100,100,100), 1, &parameters);

	return caveNode;
}
