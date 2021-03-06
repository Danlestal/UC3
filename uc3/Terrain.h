#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "OgreFramework.h"

class Terrain
{

	protected:
		Ogre::TerrainGroup *m_terrainGroup;

	private:
	
	Ogre::TerrainGlobalOptions *m_terrainGlobals;

	bool m_terrainsImported;





	public:

	void ConfigureGlobals();
	void ConfigureGroup();
	void ConfigureTerrainDefaults(Ogre::Light *light);
	virtual void DefineTerrain(int x, int y);
	void Terrain::GetTerrainImage(bool flipX, bool flipY, Ogre::Image& img);
	void Terrain::InitBlendMaps(Ogre::Terrain* terrain);

};

#endif