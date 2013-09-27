#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

class RandomNumberGenerator
{
    private:
        boost::mt19937 _rng;
    public:
        int GenerateRandomNumber(int bottonLimit, int upLimit);
};
#endif