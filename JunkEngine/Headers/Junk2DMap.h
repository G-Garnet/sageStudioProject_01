#ifndef _JUNK2DMAP_H              
#define _JUNK2DMAP_H
#define WIN32_LEAN_AND_MEAN

#include "Junk2DSprite.h"
#include "input.h"

#define MAP_MAXWIDTH  100
#define MAP_MAXHEIGHT 100

class Junk2DMap 
{
private :	
	Junk2DSprite* MapBG;

	// 맵의 위치
	int mapX, mapY;
	// 맵의 크기
	int MAP_HEIGHT, MAP_WIDTH;

	// 맵의 데이터
	int mapData[MAP_MAXHEIGHT][MAP_MAXWIDTH] = {0,};
	// 맵의 데이터 규격
	// 0 = 이동 가능
	// 1 = 충돌, 이동불가
	// 2 = 몬스터
	// 3 = 플레이어
	// .. = 각 이벤트 코드

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

	// 맵 이미지 불러옴
	void settingBGSprite(Graphics * g, const char * filename);

	// 맵 이동
	void mapMove(int mapX, int mapY);

	// 맵에 붙어있는 오브젝트 설정
	void MapAddObject(Junk2DSprite* p_pObject, std::string objecName);
	void RemoveAllObject();
	void RemoveObject(std::string objecName);

	// 맵 충돌검사
	bool MapCollision(int playerX, int playerY, int dir);

	int getMapX() { return mapX; };
	int getMapY() { return mapY; };

	Junk2DSprite* getCGameObject(std::string ObjectName);
	Junk2DSprite* getMapBG();
};

#endif
