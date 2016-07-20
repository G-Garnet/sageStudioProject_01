#ifndef _OBJECTMANAGER_H           
#define _OBJECTMANAGER_H            
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "Junk2DSprite.h"
#include "Junk2Dentity.h"

class ObjectManager {
	
private :
	std::vector<std::pair<Junk2DSprite*, std::string>> ObjectList;

public :
	ObjectManager() {};
	virtual ~ObjectManager() {
		RemoveAllObject();
	};
	void AddObject(Junk2DSprite* p_pObject, std::string objecName);

	void RenderAllObject();
	void RemoveAllObject();
	void RemoveObject(std::string objecName);

	Junk2DSprite* getCGameObject(std::string ObjectName);
};

#endif