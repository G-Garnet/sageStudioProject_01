#ifndef _ITEMSLOT_H             
#define _ITEMSLOT_H             
#define WIN32_LEAN_AND_MEAN

#define ITEM_MAX 10
#define ITEMSLOT_MAX 10

#include "..\\Headers\Game.h"

class ItemSlot {
private :

	Junk2DSprite* ItemSlotBg;
	Junk2DSprite* ItemSlotSprite;

	Junk2DSprite* Item[ITEM_MAX];

	int Slotarr[ITEMSLOT_MAX] = { 0, };

public :

	ItemSlot();
	virtual ~ItemSlot();

};


#endif