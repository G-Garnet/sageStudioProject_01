#include "ObjectManager.h"

void ObjectManager::AddObject(Junk2DSprite* p_pObject, std::string objecName)
{
	ObjectList.push_back(std::make_pair(p_pObject, objecName));
}

void ObjectManager::RenderAllObject()
{
	for (auto &i : ObjectList) {
		i.first->draw();
	}
}

void ObjectManager::RemoveObject(std::string objectName)
{
	std::vector<std::pair<Junk2DSprite*, std::string>>::iterator i;
	for (i = ObjectList.begin(); i != ObjectList.end(); i++) {
		if (i->second == objectName) {
			ObjectList.erase(i);
			return;
		}
	}
}

void ObjectManager::RemoveAllObject()
{
	ObjectList.clear();
}

Junk2DSprite* ObjectManager::getCGameObject(std::string ObjectName)
{
	for (auto &i : ObjectList) {
		if (i.second == ObjectName) {
			//return (Junk2DSprite*)i.first;

			return static_cast<Junk2DSprite*>(i.first);
		}
	}

	return nullptr;
}


