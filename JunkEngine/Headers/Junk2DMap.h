#ifndef _JUNK2DMAP_H              
#define _JUNK2DMAP_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2DSprite.h"
#include "input.h"

#define MAP_MAXWIDTH  80
#define MAP_MAXHEIGHT 80

class Junk2DMap 
{
private :	
	Junk2DSprite* MapBG;

	// 맵의 위치
	int mapX, mapY;
	// 맵의 크기
	int MAP_HEIGHT, MAP_WIDTH;

	//int mapData[MAP_MAXHEIGHT][MAP_MAXWIDTH] = {0,};
	std::vector<std::pair<Junk2DSprite*, std::string>> MapObjectList;

public :
	// 생성자 소멸자
	Junk2DMap();
	Junk2DMap(const char *file);
	virtual ~Junk2DMap() {
		RemoveAllObject();
	};

	// 맵데이터 불러옴, 받아옴
	void MapDataInsert(const char *file);
	// 맵 배경 스프라이트 설정
	void settingBGSprite(Graphics * g, const char * filename);

	// 맵 이동
	void mapMove(int mapX, int mapY);

	// 맵에 붙어있는 오브젝트 설정
	void MapAddObject(Junk2DSprite* p_pObject, std::string objecName);
	void RemoveAllObject();
	void RemoveObject(std::string objecName);

	int getMapX() { return mapX; };

	Junk2DSprite* getCGameObject(std::string ObjectName);
	Junk2DSprite* getMapBG();
};

#endif
