#include "RandomTerrain.h"

void RandomTerrain::DefineTerrain(int x, int y)
{
	Ogre::String filename = m_terrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(m_terrainGroup->getResourceGroup(), filename))
    {
        m_terrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        GetTerrainImage(x % 2 != 0, y % 2 != 0, img);
		

		float heights[3] = {1,2,3};

        m_terrainGroup->defineTerrain(x, y, heights);
    }

}