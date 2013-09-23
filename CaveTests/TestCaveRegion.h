#ifndef TESTCAVEREGION_H
#define TESTCAVEREGION_H

#include "CaveRegion.h"

class TestCaveRegion : public CaveRegion
{
    private:

        void InitTestDensityCube()
        {

        }

    public:
        TestCaveRegion(int globalPosX, int globalPosY, int globalPosZ)
        {
            mGlobalPosX = globalPosX;
            mGlobalPosY = globalPosY;
            mGlobalPosZ = globalPosZ;

            InitTestDensityCube();
        }

};
#endif