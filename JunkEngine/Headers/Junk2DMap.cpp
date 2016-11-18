#include "Junk2DMap.h"

Junk2DMap::Junk2DMap()
{
	MapBG1 = new Junk2DSprite;
	MapBG2 = new Junk2DSprite;
	//MapDataInsert("");
}

Junk2DMap::Junk2DMap(Graphics * g, const char *file)
{
	MapBG1 = new Junk2DSprite;
	MapBG2 = new Junk2DSprite;
}

void Junk2DMap::MapDataInsert(Graphics * g, const char * file)
{
	// 파일 입력 받을 부분

	// 맵 데이터 예시
	// 첫줄에 맵의 크기, 위치, 이름등 맵의 정보
	// 둘째줄에 맵의 기본 배경 정보
	// 오브젝트1 이름 / X위치 / Y위치 / 텍스쳐 설정 항목
	// 오브젝트2 이름 / X위치 / Y위치 / 텍스쳐 설정 항목
	// ...

	MapBG1->settingTexture(g, "..\\Resources\\Map1\\Map3.jpg", 6400, 6400, 1);
	MapBG1->setScale(0.5f);
	//MapBG2->settingTexture(g, "..\\Resources\\Map1\\Map1.jpg", 4345, 4345, 1);
	/*MapBG3->settingTexture(g, "..\\Resources\\Map1\\Map1.jpg", 4000, 4200, 1);
	MapBG4->settingTexture(g, "..\\Resources\\Map1\\Map1.jpg", 4000, 4200, 1);*/
	//MapBG->setDegrees(45);
	
	MainMapBG = MapBG1;
}

void Junk2DMap::settingBGSprite(Graphics * g, const char * filename)
{
	MapBG1->settingTexture(g,filename);
}

void Junk2DMap::mapMove(int X, int Y)
{
	mapX = MapBG1->getX() + X;
	mapY = MapBG1->getY() + Y;

	MapBG1->setXY(mapX, mapY);
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

bool Junk2DMap::MapCollision(int playerX, int playerY, int dir)
{
	if (playerX == 0 && dir == 1) {
		return false;
	}

	else if (playerY == 0 && dir == 3) {
		return false;
	}

	else if (playerX >= 100 && dir == 2) {
		return false;
	}

	else if (playerY >= 100 && dir == 4) {
		return false;
	}

	return true;
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
	return MainMapBG;
}

void Junk2DMap::setMapChange(int tag)
{
	switch (tag) {
	case 1:
		MainMapBG = MapBG1;
		break;
	case 2:
		MainMapBG = MapBG2;
		break;
	}
}
