#include "MarchingCubes.h"
#include "BooleanVoxel.h"

 int MarchingCubes::CreateRawTrianglesVector(UberCube* cube, std::vector<RawTriangle> *trianglesVector, Ogre::Vector3 cubeOffset)
{
	int numberOfTriangles = 0;

	for(int i = 1; i < UBERCUBE_SIZE - 1; i++)
	{
		for(int j = 1; j< UBERCUBE_SIZE - 1; j++)
		{
			for(int z = 1; z< UBERCUBE_SIZE - 1; z++)
			{
                bool neighbours[8];
                cube->GetNeighbourPoints(i,j,z, neighbours);
				BooleanVoxel voxel = BooleanVoxel( Ogre::Vector3(i,j,z) + cubeOffset, neighbours);
                
                RawTriangle triangles[8];
                int voxelTriangles = voxel.GetTriangle(triangles);
                
                for(int v=0; v<voxelTriangles; v++)
                {
                    trianglesVector->push_back(triangles[v]);
                }

                numberOfTriangles += voxelTriangles;
			}
		}
	}

	return numberOfTriangles;
}

void MarchingCubes::Poligonize(UberCube* cube, Ogre::MeshPtr mesh)
{
	std::vector<RawTriangle> trianglesVector;

    int numberOfTriangles = CreateRawTrianglesVector(cube, &trianglesVector);

    // Now that I have the raw vertex list, I can call Ogre to generate the mesh.
    Ogre::SubMesh *subMesh = mesh->createSubMesh();

    /* create the vertex data structure */
    mesh->sharedVertexData = new Ogre::VertexData;
    mesh->sharedVertexData->vertexCount = numberOfTriangles * 3;
    

    /* declare how the vertices will be represented */
    Ogre::VertexDeclaration *decl = mesh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;

    /* the first three floats of each vertex represent the position */
    decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
    decl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);

   

    /* create the vertex buffer */
    Ogre::HardwareVertexBufferSharedPtr vertexBuffer = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(offset, mesh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC);
    
    /* lock the buffer so we can get exclusive access to its data */
    float *vertices = static_cast<float *>(vertexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

    int bufferIndex = 0;
    for (std::vector<RawTriangle>::iterator it = trianglesVector.begin() ; it != trianglesVector.end(); ++it)
    {
        // First point
        vertices[bufferIndex] = it->p[0].x;
        bufferIndex++;
        vertices[bufferIndex] = it->p[0].y;
        bufferIndex++;
        vertices[bufferIndex] = it->p[0].z;
        bufferIndex++;
        // First Texture UV
        vertices[bufferIndex] = 0;
        bufferIndex++;
        vertices[bufferIndex] = 0;
        bufferIndex++;


        // Second point
        vertices[bufferIndex] = it->p[1].x;
        bufferIndex++;
        vertices[bufferIndex] = it->p[1].y;
        bufferIndex++;
        vertices[bufferIndex] = it->p[1].z;
        bufferIndex++;
        // Second Texture UV
        vertices[bufferIndex] = 0;
        bufferIndex++;
        vertices[bufferIndex] = 1;
        bufferIndex++;


        // Third point
        vertices[bufferIndex] = it->p[2].x;
        bufferIndex++;
        vertices[bufferIndex] = it->p[2].y;
        bufferIndex++;
        vertices[bufferIndex] = it->p[2].z;
        bufferIndex++;

        // Third Texture UV
        vertices[bufferIndex] = 1;
        bufferIndex++;
        vertices[bufferIndex] = 1;
        bufferIndex++;

    }
    vertexBuffer->unlock();

    /* create the index buffer */
    Ogre::HardwareIndexBufferSharedPtr indexBuffer = Ogre::HardwareBufferManager::getSingleton().
		createIndexBuffer(Ogre::HardwareIndexBuffer::IT_32BIT, numberOfTriangles * 3 * 2, Ogre::HardwareBuffer::HBU_STATIC);

    /* lock the buffer so we can get exclusive access to its data */
    Ogre::uint32 *indices = static_cast<Ogre::uint32 *>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

    /* define our triangle */
    for(int i=0; i<numberOfTriangles * 3; i++)
    {
        indices[i] = i ;
    }

      /* define our triangle */
    int j = 0;
    for(int i = numberOfTriangles * 3; i<numberOfTriangles * 3 * 2; i = i +3)
    {
        indices[i] = j + 2;
        indices[i] = j + 1;
        indices[i] = j;
        j = j +3;
    }
    
  
    /* unlock the buffer */
    indexBuffer->unlock();


    /* attach the buffers to the mesh */
    mesh->sharedVertexData->vertexBufferBinding->setBinding(0, vertexBuffer);
    
    subMesh->useSharedVertices = true;
    subMesh->indexData->indexBuffer = indexBuffer;
    subMesh->indexData->indexCount = mesh->sharedVertexData->vertexCount;
    subMesh->indexData->indexStart = 0;

/*  set the bounds of the mesh*/
    mesh->_setBounds(Ogre::AxisAlignedBox(0, 0, 0, UBERCUBE_SIZE, UBERCUBE_SIZE, UBERCUBE_SIZE),true);

    /* notify the mesh that we're all ready */
    mesh->load();
 
}


void MarchingCubes::Poligonize(UberCube* cube, Ogre::ManualObject* manualObject)
{
	std::vector<RawTriangle> trianglesVector;

    int numberOfTriangles = CreateRawTrianglesVector(cube, &trianglesVector);
    manualObject->begin("lol", Ogre::RenderOperation::OT_TRIANGLE_LIST);

    int offset = 0;

	bool firstTriangle = true;
    for (std::vector<RawTriangle>::iterator it = trianglesVector.begin()  ; it != trianglesVector.end(); ++it)
    {

        manualObject->position(it->p[0].x, it->p[0].y, it->p[0].z);
        manualObject->textureCoord(0, 0);

        manualObject->position(it->p[1].x, it->p[1].y, it->p[1].z);
        manualObject->textureCoord(0, 1);

        manualObject->position(it->p[2].x, it->p[2].y, it->p[2].z);
        manualObject->textureCoord(0, 1);

				
        manualObject->triangle(offset, offset + 1, offset + 2);
        manualObject->triangle(offset, offset + 2, offset + 1);
        offset = offset + 3;

    }

    manualObject->end();
    manualObject->setBoundingBox(Ogre::AxisAlignedBox(0, 0, 0, UBERCUBE_SIZE, UBERCUBE_SIZE, UBERCUBE_SIZE));
}