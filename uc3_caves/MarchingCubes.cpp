#include "MarchingCubes.h"
#include "BooleanVoxel.h"


void MarchingCubes::Poligonize(UberCube* cube)
{
	for(int i = 0; i < 999; i++)
	{
		for(int j = 0; j< 999; j++)
		{
			for(int z = 0; z< 999; j++)
			{
				BooleanVoxel *voxel = new BooleanVoxel(cube->GetNeighbourPoints(i,j,z));
			}
		}
	}

}