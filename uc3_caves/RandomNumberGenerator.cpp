#include "RandomNumberGenerator.h"

int RandomNumberGenerator::GenerateRandomNumber(int bottonLimit, int upLimit)
{
      boost::uniform_int<> distribution(bottonLimit, upLimit);
	  static unsigned int seed = 0;
	  _rng.seed((++seed) + time(NULL));

      boost::variate_generator< boost::mt19937, boost::uniform_int<> > dice(_rng, distribution);
	  return dice();
}