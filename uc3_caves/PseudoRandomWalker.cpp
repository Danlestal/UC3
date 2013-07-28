#include "PseudoRandomWalker.h"


PseudoRandomWalker::PseudoRandomWalker(Ogre::Vector3 source, Ogre::Vector3 destination, int goalDistance, bool keepTravelJournal)
{
	_source = source;
	_currentPosition = source;
	_destination = destination;
	_goalDistance = goalDistance;
	_keepTravelJournal = keepTravelJournal;
	
	if(keepTravelJournal)
	{
		_journal = new std::list<Ogre::Vector3>();
	}
}

int PseudoRandomWalker::GenerateRandomNumber()
{

      boost::uniform_int<> distribution( -10, 10 );
	  static unsigned int seed = 0;
	  _rng.seed((++seed) + time(NULL));

      boost::variate_generator< RNGType, boost::uniform_int<> > dice(_rng, distribution);
	  return dice();
}

Ogre::Vector3 PseudoRandomWalker::GenerateRandomStep()
{
	if(_keepTravelJournal)
	{
		_journal->push_back(_currentPosition);
	}

	Ogre::Vector3 generatedVector(GenerateRandomNumber(), GenerateRandomNumber(), GenerateRandomNumber());
	generatedVector.normalise();
	
 	Ogre::Vector3 desiredDirection = _destination - _currentPosition;
	desiredDirection.normalise();

	if(generatedVector.directionEquals(desiredDirection, Ogre::Radian( 0.20F)))
	{

		generatedVector *= 20;
	}
	else
	{
		generatedVector *= 5;
	}

	_currentPosition += generatedVector;
	return generatedVector;

	
}

void PseudoRandomWalker::SetGoalDistance(int distance)
{
	_goalDistance = distance;
}

std::list<Ogre::Vector3>* PseudoRandomWalker::GetJournal()
{
	return _journal;
}

bool PseudoRandomWalker::GoalReached()
{
	return (_currentPosition.distance(_destination) < _goalDistance);
}