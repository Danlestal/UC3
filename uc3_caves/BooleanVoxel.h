#ifndef BooleanVoxel_HPP
#define BooleanVoxel_HPP

class BooleanVoxel
{
private:
	bool _vertex0;
	bool _vertex1;
	bool _vertex2;
	bool _vertex3;
	bool _vertex4;
	bool _vertex5;
	bool _vertex6;
	bool _vertex7;

public:	
	BooleanVoxel(bool vertex0, bool vertex1, bool vertex2,	bool vertex3, bool vertex4, bool vertex5, bool vertex6, bool vertex7);
	BooleanVoxel(bool* vertexList);
	int GetEdgeTableIndex();

}

#endif