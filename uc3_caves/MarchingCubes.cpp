#include "MarchingCubes.h"
#include "BooleanVoxel.h"

void MarchingCubes::Poligonize(UberCube* cube, Ogre::MeshPtr mesh)
{
    int numberOfTriangles = 0;
    std::vector<RawTriangle> trianglesVector;

	for(int i = 0; i < UBERCUBE_SIZE - 1; i++)
	{
		for(int j = 0; j< UBERCUBE_SIZE - 1; j++)
		{
			for(int z = 0; z< UBERCUBE_SIZE - 1; z++)
			{
                
                bool neighbours[8];
                cube->GetNeighbourPoints(i,j,z, neighbours);
				BooleanVoxel *voxel = new BooleanVoxel( Ogre::Vector3(i,j,z), neighbours);
                
                RawTriangle triangles[8];
                int voxelTriangles = voxel->GetTriangle(triangles);
                
                for(int v=0; v<voxelTriangles; v++)
                {
                    trianglesVector.push_back(triangles[v]);
                }

                numberOfTriangles += voxelTriangles;
                
			}
		}
	}

    // Now that I have the triangle list, I can call Ogre to generate the mesh.

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

        // Second point
        vertices[bufferIndex] = it->p[1].x;
        bufferIndex++;
        vertices[bufferIndex] = it->p[1].y;
        bufferIndex++;
        vertices[bufferIndex] = it->p[1].z;
        bufferIndex++;
        // Third point
        vertices[bufferIndex] = it->p[2].x;
        bufferIndex++;
        vertices[bufferIndex] = it->p[2].y;
        bufferIndex++;
        vertices[bufferIndex] = it->p[2].z;
        bufferIndex++;
    }
    vertexBuffer->unlock();

    /* create the index buffer */
    Ogre::HardwareIndexBufferSharedPtr indexBuffer = Ogre::HardwareBufferManager::getSingleton().
    createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, numberOfTriangles * 3 * 2, Ogre::HardwareBuffer::HBU_STATIC);

    /* lock the buffer so we can get exclusive access to its data */
    Ogre::uint16 *indices = static_cast<Ogre::uint16 *>(indexBuffer->lock(Ogre::HardwareBuffer::HBL_NORMAL));

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