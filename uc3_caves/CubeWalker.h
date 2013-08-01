#ifndef CubeWalker_HPP
#define CubeWalker_HPP
 
#include "OgreFramework.h"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include "UberCube.h"


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
	UberCube* _uberCube;
	Ogre::Vector3 _source;
	Ogre::Vector3 _currentPosition;
	Ogre::Vector3 _destination;
	int _goalDistance;
	boost::mt19937 _rng;

	int GenerateRandomNumber();
	int NormalizeCoordinate(int coordinate);
    void UpdateDensityCube(int x, int y, int z);

	public:


		CubeWalker(UberCube* _uberCube, Ogre::Vector3 source, Ogre::Vector3 destination, int goalDistance);
		void SetGoalDistance(int distance);
		bool GoalReached();
		StepOnCube GenerateRandomStep();
		UberCube* GetDensityCube();
		void UpdatePosition(StepOnCube step);
		void GenerateDensityCube();
};

#endif 
 
