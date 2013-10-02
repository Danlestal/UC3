#include "CubeWalker.h"

void CubeWalker::GenerateDensityCube(UberCube* uberCube, Ogre::Vector3 source, Ogre::Vector3 destination)
{
    Ogre::Vector3 currentPosition = source;
    
    mBrush->UpdateDensityCube(uberCube, (int)currentPosition.x, (int)currentPosition.y, (int)currentPosition.z);

	while(! (currentPosition.distance(destination) <= mGoalDistance))
	{
		currentPosition = UpdatePosition(uberCube, currentPosition, GenerateRandomStep(currentPosition, destination));
	}
    // Prepare ending.
}

CubeWalker::CubeWalker(DensityCubeBrush* brush, int goalDistance) : mBrush(brush), mGoalDistance(goalDistance)
{
}

StepOnCube CubeWalker::GenerateRandomStep(Ogre::Vector3 currentPosition, Ogre::Vector3 destination)
{
    RandomNumberGenerator generator = RandomNumberGenerator();

    Ogre::Vector3 generatedVector(generator.GenerateRandomNumber(-1,1) , generator.GenerateRandomNumber(-1,1), generator.GenerateRandomNumber(-1,1));
	
	StepOnCube step = StepOnCube(generatedVector,0);

 	Ogre::Vector3 desiredDirection = destination - currentPosition;
	desiredDirection.normalise();

    if(generatedVector.directionEquals(desiredDirection, Ogre::Radian(1.00F)))
	{
		step.jump = 1;
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
