#include "UberCube.h"

void UberCube::GetNeighbourPoints(int x, int y, int z, bool* outNeighbours)
{
	outNeighbours[0] = mDensityCube[x][y][z + 1];
	outNeighbours[1] = mDensityCube[x + 1][y][z + 1];
	outNeighbours[2] = mDensityCube[x + 1][y][z];
	outNeighbours[3] = mDensityCube[x][y][z];
	outNeighbours[4] = mDensityCube[x][y + 1][z + 1];
	outNeighbours[5] = mDensityCube[x + 1][y + 1][z + 1];
	outNeighbours[6] = mDensityCube[x + 1][y + 1][z];
	outNeighbours[7] = mDensityCube[x][y + 1][z];
}


int UberCube::NormalizeCoordinate(int coordinate)
{
	if(coordinate < 1)
	{
		return 1;
	}

	if(coordinate > UBERCUBE_SIZE -1)
	{
		return UBERCUBE_SIZE -1;
	}
	
	return coordinate;
}


UberCube::UberCube()
{
    for(int i=0;i<UBERCUBE_SIZE;++i)
    {
        for(int j=0;j<UBERCUBE_SIZE;++j)
        {
            for(int k=0;k<UBERCUBE_SIZE;++k)
            {
                mDensityCube[i][j][k] = false;
            }
        }
    }
}


UberCube::~UberCube()
{
    /*
    for ( int r = 0; r < UBERCUBE_SIZE; ++r )
    {
        delete [] mDensityCube[r];
    }
    delete[] mDensityCube;
    */
}