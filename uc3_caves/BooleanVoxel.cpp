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
      

   Ogre::Vector3 vector0Position = _voxelPosition + Ogre::Vector3(0,0,1);
   Ogre::Vector3 vector1Position = _voxelPosition + Ogre::Vector3(1,0,1);
   Ogre::Vector3 vector2Position = _voxelPosition + Ogre::Vector3(1,0,0);
   Ogre::Vector3 vector3Position = _voxelPosition;
   Ogre::Vector3 vector4Position = _voxelPosition + Ogre::Vector3(0,1,1);
   Ogre::Vector3 vector5Position = _voxelPosition + Ogre::Vector3(1,1,1);
   Ogre::Vector3 vector6Position = _voxelPosition + Ogre::Vector3(1,1,0);
   Ogre::Vector3 vector7Position = _voxelPosition + Ogre::Vector3(0,1,0);

   Ogre::Vector3 vertList[8];
   

   /* Find the vertices where the surface intersects the cube */
   if (EdgeTable[cubeIndex] & 1)
      vertList[0] =  VertexInterp(vector0Position, vector1Position, _vertex0, _vertex1);

   if (EdgeTable[cubeIndex] & 2)
       vertList[1] = VertexInterp(vector1Position, vector2Position, _vertex1, _vertex2 );

   if (EdgeTable[cubeIndex] & 4)
      vertList[2] = VertexInterp(vector2Position, vector3Position, _vertex2, _vertex3);
   
   if (EdgeTable[cubeIndex] & 8)
      vertList[3] = VertexInterp(vector3Position, vector0Position, _vertex3, _vertex0);
   
   if (EdgeTable[cubeIndex] & 16)
      vertList[4] = VertexInterp(vector4Position, vector5Position, _vertex4, _vertex5);
   
   if (EdgeTable[cubeIndex] & 32)
      vertList[5] = VertexInterp(vector5Position, vector6Position, _vertex5, _vertex6);

   if (EdgeTable[cubeIndex] & 64)
      vertList[6] = VertexInterp(vector6Position, vector7Position, _vertex6, _vertex7);

   if (EdgeTable[cubeIndex] & 128)
      vertList[7] = VertexInterp(vector7Position, vector4Position, _vertex7, _vertex4);

   if (EdgeTable[cubeIndex] & 256)
      vertList[8] = VertexInterp(vector0Position, vector4Position,_vertex0, _vertex4);

   if (EdgeTable[cubeIndex] & 512)
      vertList[9] = VertexInterp(vector1Position, vector5Position, _vertex1, _vertex5);

   if (EdgeTable[cubeIndex] & 1024)
      vertList[10] = VertexInterp(vector2Position, vector6Position,_vertex2, _vertex6);

   if (EdgeTable[cubeIndex] & 2048)
      vertList[11] = VertexInterp(vector3Position, vector7Position ,_vertex3 ,_vertex7);

   /* Create the triangle */

   for (int i=0;triTable[cubeindex][i]!=-1;i+=3) 
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

