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
	textWindow = new TextWindow();

	mop1 = new Monster();
	mop2 = new Monster();
	mop3 = new Monster();
	mop4 = new Monster();
	mop5 = new Monster();

	mop6 = new Monster();
	mop7 = new Monster();
	mop8 = new Monster();
	mop9 = new Monster();

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

	shadows = new Junk2DSprite();
	gameOver = new Junk2DSprite();
}

Room5::~Room5()
{
	SAFE_DELETE(Map);
	objectManager->RemoveAllObject();
	SAFE_DELETE(itemSlot);
	SAFE_DELETE(cursor);
	SAFE_DELETE(font);
	SAFE_DELETE(fade);
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
	cursor->CursorSetting(graphics);
	//font->initialize(graphics, 15, true, false, "THE홍차왕자 소년M");
	fade->fadeSetting(graphics);
	fade->setAlpha(255);

	filter->settingTexture(graphics, "..\\Resources\\Etc\\Lanten.png", 2000, 2000, 1);
	
	player->setXY(64*10,64*4);
	player->p_PosX = 10;
	player->p_PosY = 9;

	filter->setXY(640 - 1000 + 32, 360 - 1000);

	textWindow->TextWindowSetting(graphics);
	textWindow->setActive(false);

	/////////////////////////

	mop1->MonseterSetting(graphics,1);
	mop1->setXY(64 * 37 - 32, 64 * 24 - 32);
	mop1->m_PosX = 37; mop1->m_PosY = 24;

	mop2->MonseterSetting(graphics, 2);
	mop2->setXY(64 * 65, 64 * 22);
	mop2->m_PosX = 65; mop2->m_PosY = 23;

	mop3->MonseterSetting(graphics, 2);
	mop3->setXY(64 * 67, 64 * 23);
	mop3->m_PosX = 67; mop3->m_PosY = 24;

	mop4->MonseterSetting(graphics, 2);
	mop4->setXY(64 * 67, 64 * 19);
	mop4->m_PosX = 67; mop4->m_PosY = 20;

	mop5->MonseterSetting(graphics, 2);
	mop5->setXY(64 * 69, 64 * 21);
	mop5->m_PosX = 69; mop5->m_PosY = 22;


	mop6->MonseterSetting(graphics, 2);
	mop6->setXY(64 * 95, 64 * 14);
	mop6->m_PosX = 95; mop6->m_PosY = 14;

	mop7->MonseterSetting(graphics, 2);
	mop7->setXY(64 * 88, 64 * 20);
	mop7->m_PosX = 88; mop7->m_PosY = 20;

	mop8->MonseterSetting(graphics, 2);
	mop8->setXY(64 * 97, 64 * 17);
	mop8->m_PosX = 97; mop8->m_PosY = 17;

	mop9->MonseterSetting(graphics, 2);
	mop9->setXY(64 * 91, 64 * 22);
	mop9->m_PosX = 91; mop9->m_PosY = 22;

	mop1->setMap(Map);
	mop2->setMap(Map);
	mop3->setMap(Map);
	mop4->setMap(Map);
	mop5->setMap(Map); 
	mop6->setMap(Map);
	mop7->setMap(Map);
	mop8->setMap(Map);
	mop9->setMap(Map);

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
	
	shadows->settingTexture(graphics, "..\\Resources\\Player\\shadow.png", 64 * 1, 64 * 2, 1);
	gameOver->settingTexture(graphics, "..\\Resources\\UI\\gameOver.png", 1280,720, 1);

	Lanten1->setXY(64 * 12, 64 * 11);
	shadows->setXY(64 * 22, 64 * 11);

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

	Lanten2->setXY(64 * 34, 64 * 18);
	Totem1->setXY(64 * 83, 64 * 6);
	Totem2->setXY(64 * 89, 64 * 5);

	sign1->setXY(64 * 102, 64 * 20);
	sign2->setXY(64 * 103, 64 * 21);
	fake1->setXY(64 * 110, 64 * 16);
	fake2->setXY(64 * 112, 64 * 19);
	sign3->setXY(64 * 110, 64 * 22);

	graves->setXY(64 * 111, 64 * 25);

	Lanten3->setXY(64 * 78, 64 * 2);
	Lanten4->setXY(64 * 128, 64 * 12);

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

	//objectManager->AddObject(Monster1, "Monster1");
	//objectManager->AddObject(Monster2, "Monster2");
	//objectManager->AddObject(Monster3, "Monster3");
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

	Map->MapAddObject(Monster1, "Monster1");
	Map->MapAddObject(Monster2, "Monster2");
	Map->MapAddObject(Monster3, "Monster3");
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
	Map->MapAddObject(mop2, "mop2");
	Map->MapAddObject(mop3, "mop3");
	Map->MapAddObject(mop4, "mop4");
	Map->MapAddObject(mop5, "mop5");
	Map->MapAddObject(mop6, "mop6");
	Map->MapAddObject(mop7, "mop7");
	Map->MapAddObject(mop8, "mop8");
	Map->MapAddObject(mop9, "mop9");
	Map->MapAddObject(shadows, "shadows");
	
	std::ifstream in("save.ini", std::ios::in);
	in >> saveX >> saveY;

	player->p_PosX = saveX;
	player->p_PosY = saveY;
	Map->mapMove(-64 * (player->p_PosX - 10), -64 * (player->p_PosY - 5));

	player->setLanten(filter);

	initialized = true;

	//audio->playCue("door close");

	

	return;
}

void Room5::Update()
{
	if (!textWindow->getActive() && !gameOverSw) {
		player->playerInput(input, Map);
	}
	cursor->CursorInput(input);

	// 페이드 인 아웃 //
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
		start = true;
	}
	///////////////////

	//// 기본 시스템 ////

	if (start && LantenAlpha <= 250) {
		//LantenAlpha += 0.05f;
	}

	if (gameOverSw && gameOverAl <= 254) {
		gameOverAl+=254;
	}
	

	/////////////////////


	////// 이벤트 발동문 //////
	{
		if (monsterStart == 1) {
			mop1->update((float)1 / 60);
			mop1->findPlayer(player->p_PosX, player->p_PosY);
			MonsterTime += (float)1 / 60;
		}

		if (monsterStart2) {
			mop2->update((float)1 / 60);
			mop2->findPlayer(player->p_PosX, player->p_PosY);

			mop3->update((float)1 / 60);
			mop3->findPlayer(player->p_PosX, player->p_PosY);

			mop4->update((float)1 / 60);
			mop4->findPlayer(player->p_PosX, player->p_PosY);

			mop5->update((float)1 / 60);
			mop5->findPlayer(player->p_PosX, player->p_PosY);

			MonsterTime2 += (float)1 / 60;
		}

		if (monsterStart3 == 2) {
			mop6->update((float)1 / 60);
			mop6->findPlayer(player->p_PosX, player->p_PosY);

			mop7->update((float)1 / 60);
			mop7->findPlayer(player->p_PosX, player->p_PosY);

			mop8->update((float)1 / 60);
			mop8->findPlayer(player->p_PosX, player->p_PosY);

			mop9->update((float)1 / 60);
			mop9->findPlayer(player->p_PosX, player->p_PosY);

			MonsterTime3 += (float)1 / 60;
		}
	}
	
	{
		if (monsterStart3 == 1) {
			MonsterStartTime += (float)1 / 60;
		}
		else if (monsterStart3 == 1) {
			MonsterStartTime += (float)1 / 60;
		}

		if (MonsterTime >= 60) {
			monsterStart = 2;
		}

		if (MonsterTime2 >= 50) {
			monsterStart2 = 2;
		}

		if (MonsterTime3 >= 50) {
			monsterStart3 = 3;
		}

		if (MonsterStartTime >= 5 && monsterStart3 != 3) {
			monsterStart3 = 2;
		}

		if (ShadowEventStart == 1) {
			shadows->setX(player->getX());
		}

		if (TotemEvent == 1) {
			Sleep(2000);
			Totem1->settingTexture(graphics, "..\\Resources\\Object\\totem_l_N.png", 64 * 3, 64 * 7, 1);
			Totem2->settingTexture(graphics, "..\\Resources\\Object\\totem_r_N.png", 64 * 3, 64 * 7, 1);
			TotemEvent = 2;
		}
	}
	
	///////////////////////////

	////// 이벤트 리스트 //////

	// 대화창 넘김&종료
	if (textWindow->getActive() && (input->isKeyUp(VK_RETURN) || input->getMouseLButtonDown())) {

		switch (eventCount) {
		case 3:
			eventCount = 2; // 다음 이벤트로
			textWindow->resetStrLength();
			textWindow->setActive(false);
			break;
		default:
			textWindow->setActive(false);
			eventCount = 0;
			textWindow->resetStrLength();
			break;
		}
	}

	// 상호작용 이벤트
	if (input->isKeyUp(VK_RETURN)) {

		if ((player->p_PosX == 8 && player->p_PosY == 24) || 
			(player->p_PosX == 5 && player->p_PosY == 26) ||
			(player->p_PosX == 10 && player->p_PosY == 26) ||
			(player->p_PosX == 6 && player->p_PosY == 27)) {
			eventCount = 1;
			textWindow->setActive(true);
		}

		// 기름병들
		{
			if (ShadowEventStart == 2 && item[0] != 1 &&
				(player->p_PosX == 27 && player->p_PosY == 13)) {
				item[0] = 1;
				LantenAlpha = 0;
			}
			if (ShadowEventStart == 2 && item[1] != 1 &&
				(player->p_PosX == 62 && player->p_PosY == 14)) {
				item[1] = 1;
				LantenAlpha = 0;
			}
			if (ShadowEventStart == 2 && item[2] != 1 &&
				(player->p_PosX == 118 && player->p_PosY == 27)) {
				item[2] = 1;
				LantenAlpha = 0;
			}
		}

		// 세이브 포인트
		if ((player->p_PosX == 12 && player->p_PosY == 12) ||
			(player->p_PosX == 34 && player->p_PosY == 19) ||
			(player->p_PosX == 78 && player->p_PosY == 4) ||
			(player->p_PosX == 128 && player->p_PosY == 13)) {
			Save();
			eventCount = 4;
			switch (player->p_PosX) {
			case 12:
				Lanten1->settingTexture(graphics, "..\\Resources\\Object\\save_point_Y.png", 64, 128, 1);
				break;
			case 34:
				Lanten2->settingTexture(graphics, "..\\Resources\\Object\\save_point_Y.png", 64, 128, 1);
				break;
			case 78:
				Lanten3->settingTexture(graphics, "..\\Resources\\Object\\save_point_Y.png", 64, 128, 1);
				break;
			case 128:
				Lanten4->settingTexture(graphics, "..\\Resources\\Object\\save_point_Y.png", 64, 128, 1);
				break;
			}
			textWindow->setActive(true);
		}

		// 칼
		if (!KnifeSw && (player->p_PosX == 136 && player->p_PosY == 20)) {
			eventCount = 5;
			objectManager->RemoveObject("knife");
			KnifeSw = true;
			textWindow->setActive(true);
		}

		// 열쇠
		if (!KeySw && (player->p_PosX == 122 && player->p_PosY == 8)) {
			eventCount = 6;
			objectManager->RemoveObject("key");
			KeySw = true;
			textWindow->setActive(true);
		}

		// 게임오버
		if (gameOverAl >= 254) {
			exit(0);
		}
	}
	
	// 위치 기반 이벤트
	{
		if (colEvent == false &&(
			(player->p_PosX == 18 && player->p_PosY == 25) ||
			(player->p_PosX == 19 && player->p_PosY == 25) ||
			(player->p_PosX == 20 && player->p_PosY == 25))) {
			Sleep(500);
			eventCount = 2;
			textWindow->setActive(true);
			colEvent = true;
		}
		
		else if ((player->p_PosX == 18 && player->p_PosY == 24) ||
			(player->p_PosX == 19 && player->p_PosY == 24) ||
			(player->p_PosX == 20 && player->p_PosY == 24)) {
			colEvent = false;
		}

		if ((player->p_PosX == 32 && player->p_PosY == 19) && !monsterStart == 1) {
			monsterStart = 1;
		}

		if ((player->p_PosX == 64 && player->p_PosY == 25) && !monsterStart2) {
			monsterStart2 = 1;
		}

		if (ShadowEventStart == 0 && (
			(player->p_PosX == 22 && player->p_PosY == 13) ||
			(player->p_PosX == 22 && player->p_PosY == 14) ||
			(player->p_PosX == 22 && player->p_PosY == 15))) {
			ShadowEventStart = 1;
		}

		if (ShadowEventStart == 1 && (
			(player->p_PosX == 26 && player->p_PosY == 13) ||
			(player->p_PosX == 26 && player->p_PosY == 14) ||
			(player->p_PosX == 26 && player->p_PosY == 15))) {
			ShadowEventStart = 2;
			eventCount = 7;
			textWindow->setActive(true);
		}

		if (!shadowMonsterEvent && (
			(player->p_PosX == 47 && player->p_PosY == 21) ||
			(player->p_PosX == 48 && player->p_PosY == 21) ||
			(player->p_PosX == 49 && player->p_PosY == 21))) {
			shadowMonsterEvent = true;
		}

		// 사냥꾼 집 이벤트
		if (HouseEvent == false && (
			(player->p_PosX == 74 && player->p_PosY == 18) ||
			(player->p_PosX == 74 && player->p_PosY == 19) ||
			(player->p_PosX == 74 && player->p_PosY == 20))) {
			Sleep(500);
			House1->settingTexture(graphics, "..\\Resources\\Object\\hunter_house_n.png", 64 * 14, 64 * 15, 1);
			HouseEvent = true;
		}

		// 토템 이벤트
		if (TotemEvent == 0 && (
			(player->p_PosX == 86 && player->p_PosY == 11) ||
			(player->p_PosX == 87 && player->p_PosY == 11) ||
			(player->p_PosX == 88 && player->p_PosY == 11))) {
			Totem1->settingTexture(graphics, "..\\Resources\\Object\\totem_l_Y.png", 64 * 3, 64 * 7, 1);
			Totem2->settingTexture(graphics, "..\\Resources\\Object\\totem_r_Y.png", 64 * 3, 64 * 7, 1); 
			TotemEvent = 1;
		}

		// 앞만 보고 가는 길 이벤트
		if (monsterStart3 == 0 && (
			(player->p_PosX == 90 && player->p_PosY == 14) ||
			(player->p_PosX == 89 && player->p_PosY == 15) )) {
			monsterStart3 = 1;
		}
		
		else if (monsterStart3 == 1 && (
			(player->p_PosX == 98 && player->p_PosY == 21) ||
			(player->p_PosX == 98 && player->p_PosY == 22) ||
			(player->p_PosX == 98 && player->p_PosY == 23))) {
			monsterStart3 = 3;
		}

		// 게임 오버
		if ((mop1->m_PosX == player->p_PosX && mop1->m_PosY == player->p_PosY) ||
			(mop2->m_PosX == player->p_PosX && mop2->m_PosY == player->p_PosY) ||
			(mop3->m_PosX == player->p_PosX && mop3->m_PosY == player->p_PosY) ||
			(mop4->m_PosX == player->p_PosX && mop4->m_PosY == player->p_PosY) ||
			(mop5->m_PosX == player->p_PosX && mop5->m_PosY == player->p_PosY) ||
			(mop6->m_PosX == player->p_PosX && mop6->m_PosY == player->p_PosY) ||
			(mop7->m_PosX == player->p_PosX && mop7->m_PosY == player->p_PosY) ||
			(mop8->m_PosX == player->p_PosX && mop8->m_PosY == player->p_PosY) ||
			(mop9->m_PosX == player->p_PosX && mop9->m_PosY == player->p_PosY) ){
			gameOverSw = true;
		}
	}

	///////////////////////////
}

void Room5::render()
{
	graphics->spriteBegin();
	Map->getMapBG()->draw();
	Map->getMapBG2()->draw();

	objectManager->RenderAllObject();
	player->draw();
	if (monsterStart != 2) mop1->draw();
	if (monsterStart2 != 2) {
		mop2->draw();
		mop3->draw();
		mop4->draw();
		mop5->draw();
	}
	if (monsterStart3 != 3) {
		mop6->draw();
		mop7->draw();
		mop8->draw();
		mop9->draw();
	}

	// 이벤트 //
	if (ShadowEventStart == 1) {
		shadows->draw();
	}

	if (shadowMonsterEvent) {
		Monster3->draw(D3DCOLOR_ARGB((int)MonsterAlpha[0], 255, 255, 255));
		if (MonsterAlpha[0]<255) MonsterAlpha[0] += 0.5f;
		if (MonsterAlpha[0] >= 27.5f) {
			Monster2->draw(D3DCOLOR_ARGB((int)MonsterAlpha[1], 255, 255, 255));
			if (MonsterAlpha[1]<255) MonsterAlpha[1] += 0.5f;
			if (MonsterAlpha[1] >= 27.5f) {
				Monster1->draw(D3DCOLOR_ARGB((int)MonsterAlpha[2], 255, 255, 255));
				if (MonsterAlpha[1]<255) MonsterAlpha[2] += 0.5f;
			}
		}
	}
	///////////

	cursor->draw();
	filter->draw(D3DCOLOR_ARGB(200, 255, 255, 255));

	switch (eventCount) {
	case 0:
		break;
	case 1:
		textWindow->TextWindowRender("지금은 놀때가 아니야.", 0);
		break;
	case 2:
		textWindow->TextWindowRender("저 못된 사람들은 날 도와주지 않을 거야…", 0);
		break;
	case 3:
		break;
	case 4:
		textWindow->TextWindowRender("불이 켜졌다.", 0);
		break;
	case 5:
		textWindow->TextWindowRender("어딘가에 도움이 될 것 같아.", 0);
		break;
	case 6:
		textWindow->TextWindowRender("찾았다.", 0);
		break;
	case 7:
		if (tmpSw) {
			Sleep(1000);
			tmpSw = false;
		}
		textWindow->TextWindowRender("..? 무언가가 있어", 0);
		break;
	}

	Map->Line1->draw();
	Map->Line2->draw();

	if (start) fade->draw(D3DCOLOR_ARGB((int)LantenAlpha, 255, 255, 255));
	else fade->draw(D3DCOLOR_ARGB((int)fade->getAlpha(), 255, 255, 255));

	gameOver->draw(D3DCOLOR_ARGB(gameOverAl, 255, 255, 255));

	graphics->spriteEnd();
}

void Room5::Save()
{
	std::ofstream out("save.ini");
	out << player->p_PosX << " " << player->p_PosY;
}

