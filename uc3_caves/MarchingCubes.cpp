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
                bool neighbours[8];
                neighbours[0]= cube->GetNeighbourPoints(i,j,z);
				BooleanVoxel *voxel = new BooleanVoxel( Ogre::Vector3(i,j,z), neighbours);
                voxel->GetTriangle();
			}
		}
	}

}