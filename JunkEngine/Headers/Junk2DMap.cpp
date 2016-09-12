#include "Junk2DMap.h"

Junk2DMap::Junk2DMap()
{
	MapBG = new Junk2DSprite;
}

Junk2DMap::Junk2DMap(const char *file)
{
	MapBG = new Junk2DSprite;
	MapDataInsert(file);
}

void Junk2DMap::MapDataInsert(const char * file)
{
	// 파일 입력 받을 부분

	// 맵 데이터 예시
	// 첫줄에 맵의 크기, 위치, 이름등 맵의 정보
	// 둘째줄에 맵의 기본 배경 정보
	// 오브젝트1 이름 / X위치 / Y위치 / 텍스쳐 설정 항목
	// 오브젝트2 이름 / X위치 / Y위치 / 텍스쳐 설정 항목
	// ...
}

void Junk2DMap::settingBGSprite(Graphics * g, const char * filename)
{
	MapBG->settingTexture(g,filename);
}

void Junk2DMap::mapMove(int X, int Y)
{
	mapX = MapBG->getX() + X;
	mapY = MapBG->getY() + Y;

	MapBG->setXY(mapX, mapY);
	for (auto i : MapObjectList) {
		i.first->setXY(i.first->getX() + X, i.first->getY() + Y);
	}
}

void Junk2DMap::MapAddObject(Junk2DSprite * p_pObject, std::string objecName)
{
	MapObjectList.push_back(std::make_pair(p_pObject, objecName));
}

void Junk2DMap::RemoveAllObject()
{
	MapObjectList.clear();
}

void Junk2DMap::RemoveObject(std::string objectName)
{
	std::vector<std::pair<Junk2DSprite*, std::string>>::iterator i;
	for (i = MapObjectList.begin(); i != MapObjectList.end(); i++) {
		if (i->second == objectName) {
			MapObjectList.erase(i);
			return;
		}
	}
}

Junk2DSprite * Junk2DMap::getCGameObject(std::string ObjectName)
{
	for (auto &i : MapObjectList) {
		if (i.second == ObjectName) {

			return static_cast<Junk2DSprite*>(i.first);
		}
	}

	return nullptr;
}

Junk2DSprite * Junk2DMap::getMapBG()
{
	return MapBG;
}
