#include "BooleanVoxel.h";

BooleanVoxel::BooleanVoxel(bool vertex0, bool vertex1, bool vertex2,	bool vertex3, bool vertex4, bool vertex5, bool vertex6, bool vertex7)
{
		_vertex0 = vertex0;
		_vertex1 = vertex1;
		_vertex2 = vertex2;
		_vertex3 = vertex3;
		_vertex4 = vertex4;
		_vertex5 = vertex5;
		_vertex6 = vertex6;
		_vertex7 = vertex7;
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

