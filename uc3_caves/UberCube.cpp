#include "UberCube.h"

bool* UberCube::GetNeighbourPoints(int x, int y, int z)
{
	bool pointList[8];

	pointList[0] = _densityCube[x][y][z];
	pointList[1] = _densityCube[x + 1][y][z];
	pointList[2] = _densityCube[x + 1][y + 1][z];
	pointList[3] = _densityCube[x + 1][y + 1][z + 1];
	pointList[4] = _densityCube[x][y + 1][z];
	pointList[5] = _densityCube[x][y + 1][z + 1];
	pointList[6] = _densityCube[x][y][z + 1];
	pointList[7] = _densityCube[x][y + 1][z + 1];

	return &pointList[0];

}