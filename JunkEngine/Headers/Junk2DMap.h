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

	// ���� ��ġ
	int mapX, mapY;
	// ���� ũ��
	int MAP_HEIGHT, MAP_WIDTH;

	//int mapData[MAP_MAXHEIGHT][MAP_MAXWIDTH] = {0,};
	std::vector<std::pair<Junk2DSprite*, std::string>> MapObjectList;

public :
	// ������ �Ҹ���
	Junk2DMap();
	Junk2DMap(const char *file);
	virtual ~Junk2DMap() {
		RemoveAllObject();
	};

	// �ʵ����� �ҷ���, �޾ƿ�
	void MapDataInsert(const char *file);
	// �� ��� ��������Ʈ ����
	void settingBGSprite(Graphics * g, const char * filename);

	// �� �̵�
	void mapMove(int mapX, int mapY);

	// �ʿ� �پ��ִ� ������Ʈ ����
	void MapAddObject(Junk2DSprite* p_pObject, std::string objecName);
	void RemoveAllObject();
	void RemoveObject(std::string objecName);

	int getMapX() { return mapX; };

	Junk2DSprite* getCGameObject(std::string ObjectName);
	Junk2DSprite* getMapBG();
};

#endif
