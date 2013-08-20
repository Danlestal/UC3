#include "CubeWalker.h"

void CubeWalker::GenerateDensityCube()
{
	while(!GoalReached())
	{
		UpdatePosition(GenerateRandomStep());
	}
}

CubeWalker::CubeWalker(UberCube* uberCube, DensityCubeBrush* brush, Ogre::Vector3 source, Ogre::Vector3 destination, int goalDistance)
{
	_uberCube = uberCube;
	_source = source;
	_currentPosition = source;
	_destination = destination;
	_goalDistance = goalDistance;
    _brush = brush;
}

int CubeWalker::GenerateRandomNumber()
{
      boost::uniform_int<> distribution(-1,1);
	  static unsigned int seed = 0;
	  _rng.seed((++seed) + time(NULL));

      boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice(_rng, distribution);
	  return dice();
}

StepOnCube CubeWalker::GenerateRandomStep()
{
	Ogre::Vector3 generatedVector(GenerateRandomNumber(), GenerateRandomNumber(), GenerateRandomNumber());
	
	StepOnCube step = StepOnCube(generatedVector,1);

 	Ogre::Vector3 desiredDirection = _destination - _currentPosition;
	desiredDirection.normalise();

    if(generatedVector.directionEquals(desiredDirection, Ogre::Radian( 0.20F)))
	{
		step.jump = 2;
	}

	return step;
}

void CubeWalker::UpdatePosition(StepOnCube step)
{
	for(int i = 0 ;i<step.jump; i++)
	{
		_currentPosition += step.direction;
		
		_currentPosition.x = _uberCube->NormalizeCoordinate(_currentPosition.x);
		_currentPosition.y = _uberCube->NormalizeCoordinate(_currentPosition.y);
		_currentPosition.z = _uberCube->NormalizeCoordinate(_currentPosition.z);

        _brush->UpdateDensityCube(_uberCube, (int)_currentPosition.x, (int)_currentPosition.y, (int)_currentPosition.z);
	}
}

bool CubeWalker::GoalReached()
{
	return (_currentPosition.distance(_destination) < _goalDistance);
}