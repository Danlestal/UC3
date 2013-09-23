#ifndef CubeWalker_HPP
#define CubeWalker_HPP
 
#include "OgreFramework.h"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include "UberCube.h"
#include "DensityCubeBrush.h"
#include "IDensityCubeGenerator.h"


struct StepOnCube
{
	Ogre::Vector3 direction;
	int jump;

	StepOnCube(Ogre::Vector3 newDirection, int newJump)
	{
		direction = newDirection;
		jump = newJump;
	}
};

class CubeWalker : public IDensityCubeGenerator
{
	private:	
        DensityCubeBrush *mBrush;
	    int mGoalDistance;
	    boost::mt19937 _rng;

	    int GenerateRandomNumber();
        void UpdateDensityCube(int x, int y, int z);

	public:
		CubeWalker(DensityCubeBrush* brush, int goalDistance);
		void SetGoalDistance(int distance);
		StepOnCube GenerateRandomStep(Ogre::Vector3 currentPosition, Ogre::Vector3 destination);
		UberCube* GetDensityCube();
		Ogre::Vector3 UpdatePosition(UberCube* uberCube, Ogre::Vector3 currentPosition, StepOnCube step);
		void GenerateDensityCube(UberCube* uberCube, Ogre::Vector3 source, Ogre::Vector3 destination);
};

#endif 
 
