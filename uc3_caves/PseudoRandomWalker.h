#ifndef PseudoRandomWalker_HPP
#define PseudoRandomWalker_HPP

#include "OgreFramework.h"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

class PseudoRandomWalker
{
	private:
		Ogre::Vector3 _source;
		Ogre::Vector3 _currentPosition;
		Ogre::Vector3 _destination;
		typedef boost::mt19937 RNGType;
		RNGType _rng;
		int _goalDistance;
		bool _keepTravelJournal;
		std::list<Ogre::Vector3> * _journal;


		int GenerateRandomNumber();

	public:
		PseudoRandomWalker(Ogre::Vector3 source, Ogre::Vector3 destination, int goalDistance, bool keepTravelJournal);
		void SetGoalDistance(int distance);
		bool GoalReached();
		Ogre::Vector3 GenerateRandomStep();
		std::list<Ogre::Vector3>* GetJournal();
};

#endif