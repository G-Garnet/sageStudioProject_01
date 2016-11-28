#include "Scenes.h"

Room5::Room5()
{
	objectManager = new ObjectManager;

	Map = new Junk2DMap();

	player = new Player();
	itemSlot = new ItemSlot();
	cursor = new Cursor();
	font = new Junk2DFont();
	fade = new Fade();

	mop1 = new Monster();

	filter = new Junk2DSprite();

	Lanten1 = new Junk2DSprite();
	Tree1 = new Junk2DSprite();
	animalDeath1 = new Junk2DSprite();
	animalDeath2 = new Junk2DSprite();
	animalDeath3 = new Junk2DSprite();
	animalDeath4 = new Junk2DSprite();

	signPost = new Junk2DSprite();
	Tree2 = new Junk2DSprite();
	Tree3 = new Junk2DSprite();
	Tree4 = new Junk2DSprite();
	Tree5 = new Junk2DSprite();

	Monster1 = new Junk2DSprite();
	Monster2 = new Junk2DSprite();
	Monster3 = new Junk2DSprite();
	Tree6 = new Junk2DSprite();
	House1 = new Junk2DSprite();
	Tree7 = new Junk2DSprite();
	DeadMen = new Junk2DSprite();

	Lanten2 = new Junk2DSprite();
	Totem1 = new Junk2DSprite();
	Totem2 = new Junk2DSprite();


	sign1 = new Junk2DSprite();
	sign2 = new Junk2DSprite();
	fake1 = new Junk2DSprite();
	fake2 = new Junk2DSprite();
	sign3 = new Junk2DSprite();

	graves = new Junk2DSprite();

	Lanten3 = new Junk2DSprite();
	Lanten4 = new Junk2DSprite();

	House2 = new Junk2DSprite();
	House3 = new Junk2DSprite();
	knife = new Junk2DSprite();
}

Room5::~Room5()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
	SAFE_DELETE(fade);
	SAFE_DELETE(videoPlayer);
}

void Room5::initialize(HWND hwnd)
{
	//Game::initialize(hwnd);

	// Input객체 초기화
	input->initialize(hwnd, false);
	// 타이머 사용
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	// 이미지 정보름 미리 선언
	//Map->settingBGSprite(graphics, "..\\Resources\\\Floor1\\Room5\\Room5_bg.png");

	// Scene의 기본 요소들 //
	Map->MapDataInsert(graphics,"");
	Map->mapMove(0,0);

	player->playerSetting(graphics);
	itemSlot->ItemSlotSetting(graphics);
	cursor->CursorSetting(graphics);
	font->initialize(graphics, 15, true, false, "굴림체");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);
	
	player->setXY(64*10,64*4);
	player->p_PosX = 10;
	player->p_PosY = 5;
	/////////////////////////

	mop1->MonseterSetting(graphics);
	mop1->setXY(64 * 4, 64 * 7);
	mop1->m_PosX = 4;
	mop1->m_PosY = 8;

	Map->mapMove(0, 0);
	mop1->setMap(Map);

	player->setMapszie(1);

	// 오브젝트 //

	Lanten1->settingTexture(graphics, "..\\Resources\\Object\\save_point_N.png", 64, 128, 1);
	Tree1->settingTexture(graphics, "..\\Resources\\Object\\lot_tree.png", 64*5, 128*3, 1);
	animalDeath1->settingTexture(graphics, "..\\Resources\\Object\\lot_bird carcass.png", 64, 64, 1);
	animalDeath2->settingTexture(graphics, "..\\Resources\\Object\\lot_cat carcass.png", 64, 64, 1);
	animalDeath3->settingTexture(graphics, "..\\Resources\\Object\\lot_pile.png", 64, 64, 1);
	animalDeath4->settingTexture(graphics, "..\\Resources\\Object\\lot_cat carcass.png", 64, 64, 1);

	signPost->settingTexture(graphics, "..\\Resources\\Object\\signpost.png", 64, 128, 1);
	
	Tree2->settingTexture(graphics, "..\\Resources\\Object\\shadow_tree.png", 64 * 3, 64 * 5, 1);
	Tree3->settingTexture(graphics, "..\\Resources\\Object\\shadow_tree2.png", 64 * 3, 64 * 5, 1);
	Tree4->settingTexture(graphics, "..\\Resources\\Object\\Shadow_tree3.png", 64 * 3, 64 * 5, 1);
	
	Tree5->settingTexture(graphics, "..\\Resources\\Object\\suicide_tree.png", 64 * 4, 64 * 6, 1);

	Monster1->settingTexture(graphics, "..\\Resources\\Object\\wolfshadow_l.png", 64 * 4, 64 * 2, 1);
	Monster2->settingTexture(graphics, "..\\Resources\\Object\\wolfshadow_r.png", 64 * 4, 64 * 2, 1);
	Monster3->settingTexture(graphics, "..\\Resources\\Object\\wolfshadow_l.png", 64 * 4, 64 * 2, 1);
	Tree6->settingTexture(graphics, "..\\Resources\\Object\\dog_tree.png", 64 * 3, 64 * 4, 1);
	House1->settingTexture(graphics, "..\\Resources\\Object\\hunter_house.png", 64 * 14, 64 * 15, 1);

	Tree7->settingTexture(graphics, "..\\Resources\\Object\\bamboo spear_tree.png", 64 * 3, 64 * 4, 1);
	DeadMen->settingTexture(graphics, "..\\Resources\\Object\\corpse.png", 64 * 3, 64 * 3, 1);

	Lanten2->settingTexture(graphics, "..\\Resources\\Object\\save_point_N.png", 64 * 1, 64 * 2, 1);
	Totem1->settingTexture(graphics, "..\\Resources\\Object\\totem_l_N.png", 64 * 3, 64 * 7, 1);
	Totem2->settingTexture(graphics, "..\\Resources\\Object\\totem_r_N.png", 64 * 3, 64 * 7, 1);

	sign1->settingTexture(graphics, "..\\Resources\\Object\\forbid_sign.png", 64 * 1, 64 * 2, 1);
	sign2->settingTexture(graphics, "..\\Resources\\Object\\caution_sign.png", 64 * 1, 64 * 3, 1);
	fake1->settingTexture(graphics, "..\\Resources\\Object\\lot_bird carcass.png", 64 * 1, 64 * 1, 1);
	fake2->settingTexture(graphics, "..\\Resources\\Object\\fake_1.png", 64 * 1, 64 * 1, 1);
	sign3->settingTexture(graphics, "..\\Resources\\Object\\caution_sign.png", 64 * 1, 64 * 2, 1);

	graves->settingTexture(graphics, "..\\Resources\\Object\\headstone party.png", 64 * 10, 64 * 3, 1);
	
	Lanten3->settingTexture(graphics, "..\\Resources\\Object\\save_point_N.png", 64 * 1, 64 * 2, 1);
	Lanten4->settingTexture(graphics, "..\\Resources\\Object\\save_point_N.png", 64 * 1, 64 * 2, 1);

	House2->settingTexture(graphics, "..\\Resources\\Object\\gm_housefence.png", 576, 576, 1);
	House3->settingTexture(graphics, "..\\Resources\\Object\\gm_storage.png", 64 * 4, 64 * 6, 1);
	
	knife->settingTexture(graphics, "..\\Resources\\Object\\knife.png", 64 * 1, 64 * 1, 1);

	Lanten1->setXY(64 * 12, 64 * 11);
	Tree1->setXY(64 * 3, 64 * 19);
	animalDeath1->setXY(64 * 8, 64 * 24);
	animalDeath2->setXY(64 * 5, 64 * 26);
	animalDeath3->setXY(64 * 10, 64 * 26);
	animalDeath4->setXY(64 * 6, 64 * 27);

	signPost->setXY(64 * 19, 64 * 17);

	Tree2->setXY(64 * 20, 64 * 8);
	Tree3->setXY(64 * 23, 64 * 8);
	Tree4->setXY(64 * 26, 64 * 8);

	Tree5->setXY(64 * 27, 64 * 24);

	Monster1->setXY(64 * 45, 64 * 18);
	Monster2->setXY(64 * 48, 64 * 20);
	Monster3->setXY(64 * 45, 64 * 22);

	Tree6->setXY(64 * 50, 64 * 10);
	House1->setXY(64 * 54, 64 * 4);
	Tree7->setXY(64 * 69, 64 * 9);

	DeadMen->setXY(64 * 66, 64 * 21);

	Lanten2->setXY(64 * 78, 64 * 2);
	Totem1->setXY(64 * 83, 64 * 6);
	Totem2->setXY(64 * 89, 64 * 5);

	sign1->setXY(64 * 102, 64 * 20);
	sign2->setXY(64 * 103, 64 * 21);
	fake1->setXY(64 * 110, 64 * 16);
	fake2->setXY(64 * 112, 64 * 19);
	sign3->setXY(64 * 110, 64 * 22);

	graves->setXY(64 * 111, 64 * 25);

	Lanten3->setXY(64 * 128, 64 * 12);
	Lanten4->setXY(64 * 127, 64 * 17);

	House2->setXY(64 * 129, 64 * 5);
	House3->setXY(64 * 134, 64 * 14);

	knife->setXY(64 * 136, 64 * 20);


	objectManager->AddObject(Lanten1, "Lanten1");
	objectManager->AddObject(Tree1, "Tree1");
	objectManager->AddObject(animalDeath1, "animalDeath1");
	objectManager->AddObject(animalDeath2, "animalDeath2");
	objectManager->AddObject(animalDeath3, "animalDeath3");
	objectManager->AddObject(animalDeath4, "animalDeath4");

	objectManager->AddObject(player, "player");

	objectManager->AddObject(signPost, "signPost");
	objectManager->AddObject(Tree2, "Tree2");
	objectManager->AddObject(Tree3, "Tree3");
	objectManager->AddObject(Tree4, "Tree4");
	objectManager->AddObject(Tree5, "Tree5");

	objectManager->AddObject(Monster1, "Monster1");
	objectManager->AddObject(Monster2, "Monster2");
	objectManager->AddObject(Monster3, "Monster3");
	objectManager->AddObject(Tree6, "Tree6");
	objectManager->AddObject(House1, "House1");
	objectManager->AddObject(Tree7, "Tree7");
	objectManager->AddObject(DeadMen, "DeadMen");

	objectManager->AddObject(Lanten2, "Lanten2");
	objectManager->AddObject(Totem1, "Totem1");
	objectManager->AddObject(Totem2, "Totem2");

	objectManager->AddObject(sign1, "sign1");
	objectManager->AddObject(sign2, "sign2");
	objectManager->AddObject(fake1, "fake1");
	objectManager->AddObject(fake2, "fake2");
	objectManager->AddObject(sign3, "sign3");
	objectManager->AddObject(graves, "graves");
	objectManager->AddObject(Lanten3, "Lanten3");
	objectManager->AddObject(Lanten4, "Lanten4");
	objectManager->AddObject(House2, "House2");
	objectManager->AddObject(House3, "House3");
	objectManager->AddObject(knife, "knife");


	Map->MapAddObject(objectManager->getCGameObject("Lanten1"), "Lanten1");
	Map->MapAddObject(objectManager->getCGameObject("Tree1"), "Tree1");
	Map->MapAddObject(objectManager->getCGameObject("animalDeath1"), "animalDeath1");
	Map->MapAddObject(objectManager->getCGameObject("animalDeath2"), "animalDeath2");
	Map->MapAddObject(objectManager->getCGameObject("animalDeath3"), "animalDeath3");
	Map->MapAddObject(objectManager->getCGameObject("animalDeath4"), "animalDeath4");

	//Map->MapAddObject(objectManager->getCGameObject("player"), "player");

	Map->MapAddObject(objectManager->getCGameObject("signPost"), "signPost");
	Map->MapAddObject(objectManager->getCGameObject("Tree2"), "Tree2");
	Map->MapAddObject(objectManager->getCGameObject("Tree3"), "Tree3");
	Map->MapAddObject(objectManager->getCGameObject("Tree4"), "Tree4");
	Map->MapAddObject(objectManager->getCGameObject("Tree5"), "Tree5");

	Map->MapAddObject(objectManager->getCGameObject("Monster1"), "Monster1");
	Map->MapAddObject(objectManager->getCGameObject("Monster2"), "Monster2");
	Map->MapAddObject(objectManager->getCGameObject("Monster3"), "Monster3");
	Map->MapAddObject(objectManager->getCGameObject("Tree6"), "Tree6");
	Map->MapAddObject(objectManager->getCGameObject("House1"), "House1");
	Map->MapAddObject(objectManager->getCGameObject("Tree7"), "Tree7");
	Map->MapAddObject(objectManager->getCGameObject("DeadMen"), "DeadMen");

	Map->MapAddObject(objectManager->getCGameObject("Lanten2"), "Lanten2");
	Map->MapAddObject(objectManager->getCGameObject("Totem1"), "Totem1");
	Map->MapAddObject(objectManager->getCGameObject("Totem2"), "Totem2");

	Map->MapAddObject(objectManager->getCGameObject("sign1"), "sign1");
	Map->MapAddObject(objectManager->getCGameObject("sign2"), "sign2");
	Map->MapAddObject(objectManager->getCGameObject("fake1"), "fake1");
	Map->MapAddObject(objectManager->getCGameObject("fake2"), "fake2");
	Map->MapAddObject(objectManager->getCGameObject("sign3"), "sign3");

	Map->MapAddObject(objectManager->getCGameObject("graves"), "graves");

	Map->MapAddObject(objectManager->getCGameObject("Lanten3"), "Lanten3");
	Map->MapAddObject(objectManager->getCGameObject("Lanten4"), "Lanten4");

	Map->MapAddObject(objectManager->getCGameObject("House2"), "House2");
	Map->MapAddObject(objectManager->getCGameObject("House3"), "House3");

	Map->MapAddObject(objectManager->getCGameObject("knife"), "knife");

	//////////////

	Map->MapAddObject(mop1,"mop1");

	initialized = true;

	//audio->playCue("door close");

	return;
}

void Room5::Update()
{
	player->playerInput(input, Map);
	itemSlot->ItemSlotInput(input);
	cursor->CursorInput(input);

	if (fade->getalphaStart()) {
		player->setInputSW(false);
		fade->setAlpha(fade->getAlpha() + 0.8f);
	}
	else if (fade->getAlpha() <= 255 && fade->getAlpha() >= 1.5f) {
		player->setInputSW(false);
		fade->setAlpha(fade->getAlpha() - 1.5f);
	}
	else if (fade->getAlpha() <= 1.5f) {
		player->setInputSW(true);
	}

	mop1->update((float)1 / 60);
	mop1->findPlayer(player->p_PosX,player->p_PosY);

	/*if (input->isKeyUp(VK_RETURN)) {

		fade->setalphaStart(true);
	}*/

	//exitGame();
}

void Room5::render()
{
	graphics->spriteBegin();
	Map->getMapBG()->draw();
	Map->getMapBG2()->draw();

	for (int i = 0;i<=142;i++) {
		Map->Line1->draw();
		Map->Line1->setXY(Map->getMapBG()->getX() + i * 64,0);
	}
	for (int i = 0; i<=35; i++) {
		Map->Line2->draw();
		Map->Line2->setXY(0, Map->getMapBG()->getY() + i * 64);
	}

	objectManager->RenderAllObject();
	player->draw();
	//mop1->draw();

	itemSlot->ItemSlotRender();
	cursor->draw();
	fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	graphics->spriteEnd();
}

