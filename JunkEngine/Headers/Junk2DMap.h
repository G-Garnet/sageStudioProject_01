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

	int mapX, mapY;
	int MAP_HEIGHT, MAP_WIDTH;

	int tileData[MAP_MAXHEIGHT][MAP_MAXWIDTH] = {0,};
	std::vector<std::pair<Junk2DSprite*, std::string>> ObjectList;

public :
	void MapDataInsert(const char *file);

	void settingMapSprite();
	void settingMapObject();

	void setMapPos(int mapX, int mapY);


	void MapAddObject(Junk2DSprite* p_pObject, std::string objecName);
	void RemoveAllObject();
	void RemoveObject(std::string objecName);

	Junk2DSprite* getCGameObject(std::string ObjectName);
};

#endif
