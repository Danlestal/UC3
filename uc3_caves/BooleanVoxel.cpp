#include "BooleanVoxel.h";
#include "MarchingCubesTable.h"

BooleanVoxel::BooleanVoxel(Ogre::Vector3 voxelPosition, bool vertex0, bool vertex1, bool vertex2,	bool vertex3, bool vertex4, bool vertex5, bool vertex6, bool vertex7)
{
        _voxelPosition = voxelPosition;
		_vertex0 = vertex0;
		_vertex1 = vertex1;
		_vertex2 = vertex2;
		_vertex3 = vertex3;
		_vertex4 = vertex4;
		_vertex5 = vertex5;
		_vertex6 = vertex6;
		_vertex7 = vertex7;
}

BooleanVoxel::BooleanVoxel(Ogre::Vector3 voxelPosition, bool vertex[])
{
    _voxelPosition = voxelPosition;
	_vertex0 = vertex[0];
	_vertex1 = vertex[1];
    _vertex2 = vertex[2];
	_vertex3 = vertex[3];
	_vertex4 = vertex[4];
	_vertex5 = vertex[5];
	_vertex6 = vertex[6];
	_vertex7 = vertex[7];
}


void BooleanVoxel::GetTriangle()
{
    int cubeIndex = GetEdgeTableIndex();
   
    /* Cube is entirely in/out of the surface */
   if (EdgeTable[cubeIndex] == 0)
      return(0);

   /* Find the vertices where the surface intersects the cube */
   if (EdgeTable[cubeIndex] & 1)
      vertlist[0] =  VertexInterp(grid.p[0],grid.p[1], _vertex0, _vertex1);

   if (EdgeTable[cubeIndex] & 2)
      vertlist[1] = VertexInterp(grid.p[1],grid.p[2],_vertex1, _vertex2 );

   if (EdgeTable[cubeIndex] & 4)
      vertlist[2] = VertexInterp(grid.p[2],grid.p[3], _vertex2, _vertex3);
   
   if (EdgeTable[cubeIndex] & 8)
      vertlist[3] = VertexInterp(grid.p[3],grid.p[0], _vertex3, _vertex0);
   
   if (EdgeTable[cubeIndex] & 16)
      vertlist[4] = VertexInterp(grid.p[4],grid.p[5], _vertex4, _vertex5);
   
   if (EdgeTable[cubeIndex] & 32)
      vertlist[5] = VertexInterp(grid.p[5],grid.p[6], _vertex5, _vertex6);

   if (EdgeTable[cubeIndex] & 64)
      vertlist[6] = VertexInterp(grid.p[6],grid.p[7], _vertex6, _vertex7);

   if (EdgeTable[cubeIndex] & 128)
      vertlist[7] = VertexInterp(grid.p[7],grid.p[4], _vertex7, _vertex4);

   if (EdgeTable[cubeindex] & 256)
      vertlist[8] = VertexInterp(grid.p[0],grid.p[4],_vertex0, _vertex4);

   if (EdgeTable[cubeindex] & 512)
      vertlist[9] = VertexInterp(grid.p[1],grid.p[5],_vertex1, _vertex5);

   if (EdgeTable[cubeindex] & 1024)
      vertlist[10] = VertexInterp(grid.p[2],grid.p[6],_vertex2, _vertex6);

   if (EdgeTable[cubeindex] & 2048)
      vertlist[11] = VertexInterp(grid.p[3],grid.p[7],_vertex3 ,_vertex7);

   /* Create the triangle */

   for (i=0;triTable[cubeindex][i]!=-1;i+=3) 
   {
      triangles[ntriang].p[0] = vertlist[triTable[cubeindex][i  ]];
      triangles[ntriang].p[1] = vertlist[triTable[cubeindex][i+1]];
      triangles[ntriang].p[2] = vertlist[triTable[cubeindex][i+2]];
   }

   return(ntriang);
}


int BooleanVoxel::GetEdgeTableIndex()
{
	// This can be done more elegant just by using displacement and ANDS.
    
   int cubeindex = 0;
   if (_vertex0) cubeindex |= 1;
   if (_vertex1) cubeindex |= 2;
   if (_vertex2) cubeindex |= 4;
   if (_vertex3) cubeindex |= 8;
   if (_vertex4) cubeindex |= 16;
   if (_vertex5) cubeindex |= 32;
   if (_vertex6) cubeindex |= 64;
   if (_vertex7) cubeindex |= 128;
   return cubeindex;
}

