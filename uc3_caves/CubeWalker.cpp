#include "CubeWalker.h"

void CubeWalker::GenerateDensityCube()
{
	while(!GoalReached())
	{
		UpdatePosition(GenerateRandomStep());
	}

}

CubeWalker::CubeWalker(UberCube* uberCube, Ogre::Vector3 source, Ogre::Vector3 destination, int goalDistance)
{
	_uberCube = uberCube;
	_source = source;
	_currentPosition = source;
	_destination = destination;
	_goalDistance = goalDistance;
}

int CubeWalker::GenerateRandomNumber()
{
      boost::uniform_int<> distribution(-1,1);
	  static unsigned int seed = 0;
	  _rng.seed((++seed) + time(NULL));

      boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice(_rng, distribution);
	  return dice();
}

int CubeWalker::NormalizeCoordinate(int coordinate)
{
	if(coordinate < 0)
	{
		return 0;
	}

	if(coordinate > UBERCUBE_SIZE -1)
	{
		return UBERCUBE_SIZE -1;
	}
	
	return coordinate;
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
		
		_currentPosition.x = NormalizeCoordinate(_currentPosition.x);
		_currentPosition.y = NormalizeCoordinate(_currentPosition.y);
		_currentPosition.z = NormalizeCoordinate(_currentPosition.z);

        UpdateDensityCube((int)_currentPosition.x, (int)_currentPosition.y, (int)_currentPosition.z);
	}
}


void CubeWalker::UpdateDensityCube(int x, int y, int z)
{
    _uberCube->_densityCube[x][y][z] = true;
    _uberCube->_densityCube[NormalizeCoordinate(x+1)][y][z] = true;
    _uberCube->_densityCube[NormalizeCoordinate(x-1)][y][z] = true;
    _uberCube->_densityCube[x][NormalizeCoordinate(y+1)][z] = true;
    _uberCube->_densityCube[x][NormalizeCoordinate(y-1)][z] = true;
    _uberCube->_densityCube[x][y][NormalizeCoordinate(z+1)] = true;
    _uberCube->_densityCube[x][y][NormalizeCoordinate(z-1)] = true;

}


bool CubeWalker::GoalReached()
{
	return (_currentPosition.distance(_destination) < _goalDistance);
}