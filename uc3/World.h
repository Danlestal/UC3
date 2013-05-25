#ifndef World_H
#define World_H

/// <summary>
/// 
/// </summary>
class World
{
	//Singleton stuff
	static World* m_instance; 

	//Important variables

	//Constructor
	World();

	public:
		
		World* GetInstance();
};
#endif
