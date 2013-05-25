#include "World.h"

World* World::m_instance = 0;

World::World()
{
}

/// <summary>
/// Gets the instance.
/// </summary>
/// <returns></returns>
World* World::GetInstance()
{
	if(m_instance==0)
	{
		m_instance = new World();
	}
	return m_instance;
}
