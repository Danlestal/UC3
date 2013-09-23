#include "CubeWalker.h"

void CubeWalker::GenerateDensityCube(UberCube* uberCube, Ogre::Vector3 source, Ogre::Vector3 destination)
{
    Ogre::Vector3 currentPosition = source;

	while(! (currentPosition.distance(destination) < mGoalDistance))
	{
		currentPosition = UpdatePosition(uberCube, currentPosition, GenerateRandomStep(currentPosition, destination));
	}
}

CubeWalker::CubeWalker(DensityCubeBrush* brush, int goalDistance) : mBrush(brush), mGoalDistance(goalDistance)
{
}

int CubeWalker::GenerateRandomNumber()
{
      boost::uniform_int<> distribution(-1,1);
	  static unsigned int seed = 0;
	  _rng.seed((++seed) + time(NULL));

      boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice(_rng, distribution);
	  return dice();
}

StepOnCube CubeWalker::GenerateRandomStep(Ogre::Vector3 currentPosition, Ogre::Vector3 destination)
{
	Ogre::Vector3 generatedVector(GenerateRandomNumber(), GenerateRandomNumber(), GenerateRandomNumber());
	
	StepOnCube step = StepOnCube(generatedVector,0);

 	Ogre::Vector3 desiredDirection = destination - currentPosition;
	desiredDirection.normalise();

    if(generatedVector.directionEquals(desiredDirection, Ogre::Radian(1.00F)))
	{
		step.jump = 3;
	}

	return step;
}

Ogre::Vector3 CubeWalker::UpdatePosition(UberCube* uberCube, Ogre::Vector3 currentPosition, StepOnCube step)
{
    if(step.jump!=0)
    {
        Ogre::Vector3 newPosition;

	    for(int i = 0 ;i<step.jump; i++)
	    {
		    newPosition =  currentPosition + step.direction;
		
		    newPosition.x = uberCube->NormalizeCoordinate(newPosition.x);
		    newPosition.y = uberCube->NormalizeCoordinate(newPosition.y);
		    newPosition.z = uberCube->NormalizeCoordinate(newPosition.z);

            mBrush->UpdateDensityCube(uberCube, (int)newPosition.x, (int)newPosition.y, (int)newPosition.z);
	    }

        return newPosition;
    }

    return currentPosition;
}
