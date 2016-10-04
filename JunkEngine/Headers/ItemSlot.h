#ifndef _ITEMSLOT_H             
#define _ITEMSLOT_H             
#define WIN32_LEAN_AND_MEAN

#define ITEM_MAX 10
#define ITEMSLOT_MAX 10

#include "..\\Headers\Game.h"

class ItemSlot {
private:

	Junk2DSprite* ItemSlotBG;
	Junk2DSprite* Item[ITEM_MAX];

	Junk2DSprite* stage;
	Junk2DSprite* menu;

	Junk2DSprite* upButton;
	Junk2DSprite* downButton;

	Junk2DSprite* Effect;

	int Slotarr[ITEMSLOT_MAX] = { 0, };

	bool ItemSlotvisible = false;

public:

	ItemSlot();
	virtual ~ItemSlot();

	void ItemSlotSetting(Graphics* graphics);
	void ItemSlotInput(Input* input);

	void ItemSlotRender();
};


#endif