#ifndef CubeWalker_HPP
#define CubeWalker_HPP
 
#include "OgreFramework.h"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include "UberCube.h"
#include "DensityCubeBrush.h"


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

class CubeWalker
{
	private:	
	    Ogre::Vector3 _source;
	    Ogre::Vector3 _currentPosition;
	    Ogre::Vector3 _destination;
        DensityCubeBrush *_brush;
	    int _goalDistance;
	    boost::mt19937 _rng;

	    int GenerateRandomNumber();
        void UpdateDensityCube(int x, int y, int z);

	public:
		CubeWalker(DensityCubeBrush* brush, Ogre::Vector3 source, Ogre::Vector3 destination, int goalDistance);
		void SetGoalDistance(int distance);
		bool GoalReached();
		StepOnCube GenerateRandomStep();
		UberCube* GetDensityCube();
		void UpdatePosition(UberCube* uberCube, StepOnCube step);
		void GenerateDensityCube(UberCube* uberCube);
};

#endif 
 
