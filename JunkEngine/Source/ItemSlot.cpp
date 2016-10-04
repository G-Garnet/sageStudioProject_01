#include "..\Headers\ItemSlot.h"

ItemSlot::ItemSlot()
{
	ItemSlotBG = new Junk2DSprite;

	for (int i = 0; i < ITEM_MAX; i++) {
		Item[i] = new Junk2DSprite;
	}

	Effect = new Junk2DSprite;

	stage = new Junk2DSprite;
	menu = new Junk2DSprite;
	upButton = new Junk2DSprite;
	downButton = new Junk2DSprite;
}

ItemSlot::~ItemSlot()
{
	SAFE_DELETE(ItemSlotBG);

	for (int i = 0; i < ITEM_MAX; i++) {
		SAFE_DELETE(Item[i]);
	}

	SAFE_DELETE(stage);
	SAFE_DELETE(menu);
	SAFE_DELETE(upButton);
	SAFE_DELETE(downButton);

	SAFE_DELETE(Effect);
}

void ItemSlot::ItemSlotSetting(Graphics * graphics)
{
	ItemSlotBG->settingTexture(graphics, "..\\Resources\\UI\\UI_BG.png", 1280, 720, 1);
	ItemSlotBG->setXY(0,0);

	for (int i = 0; i < ITEM_MAX; i++) {
		Item[i]->settingTexture(graphics, "..\\Resources\\UI\\Item123.png", 629, 92, 1);
		Item[i]->setXY(451,239+i*137);
	}

	stage->settingTexture(graphics, "..\\Resources\\UI\\stage.png", 287, 75, 1);
	stage->setXY(76, 96);

	menu->settingTexture(graphics, "..\\Resources\\UI\\item.png", 419, 38, 1);
	menu->setXY(556, 162);

	upButton->settingTexture(graphics, "..\\Resources\\UI\\icon.png", 56, 51, 1);
	upButton->setXY(1163, 352);

	downButton->settingTexture(graphics, "..\\Resources\\UI\\icon.png", 56, 51, 1);
	downButton->setXY(1163, 487);
}

void ItemSlot::ItemSlotInput(Input * input)
{
	if (input->isKeyUp(VK_ESCAPE)) {
		ItemSlotvisible = !ItemSlotvisible;
	}
}

void ItemSlot::ItemSlotRender()
{
	if (ItemSlotvisible){
		ItemSlotBG->draw();

		stage->draw();
		menu->draw(); 
		upButton->draw();
		downButton->draw();

		for (int i = 0; i < 3; i++) {
			Item[i]->draw();
		}
	}
}
