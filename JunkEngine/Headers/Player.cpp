#include "Player.h"

int Player::p_PosScene = 0;
int Player::p_PosX = 0;
int Player::p_PosY = 0;
int Player::Item[10] = {0,};

Player::Player()
{
	motionSW = 255;
}

void Player::playerSetting(Graphics* graphics)
{
	this->initialize(graphics, "..\\Resources\\Player\\player.png", 128, 256, 6);
	this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	this->setActive(true);
	this->setScale(0.5f);

	this->getplayerWidth();

	this->setXY(640,270);
}

void Player::playerInput(Input* input, Junk2DMap* Map1)
{
	// 플레이어 이동 클래스
	// 전부 플레이어 클래스로 만들어서 객체화 시켜서 이동할 예정
	//if (inputSW) {
	//if (input->isKeyDown(VK_UP) ||
	//	input->isKeyDown(VK_DOWN) ||
	//	input->isKeyDown(VK_LEFT) ||
	//	input->isKeyDown(VK_RIGHT) || moveCounter == 0) {

	//	if (motionSW != 1) {
	//		this->initialize(graphics, "..\\Resources\\Player\\player.png", 128, 256, 1);
	//		this->setLoop(true);
	//		this->setActive(true);
	//		this->setCollisionType(Junk2DentityNS::BOX);
	//		//this->setAnimation(0, 3, 0, 0.2f);
	//	}

	//else {
	//	if (motionSW != 0) {
	//		this->initialize(graphics, "..\\Resources\\Player\\player.png", 128, 256, 1);
	//		this->setLoop(true);
	//		this->setActive(true);
	//		this->setCollisionType(Junk2DentityNS::BOX);
	//	}

	//	motionSW = 0;
	//}

	if (moveCounter==0) {
		if (input->isKeyDown(VK_UP) && input->isKeyDown(VK_RIGHT)) {
			if (Map1->MapCollision(p_PosX, p_PosY, 5)) Dir_ = 5;
			nowDir_ = 5;

			this->setLoop(true);
			this->setAnimation(42, 47, 42, 0.2f);
			lanten->setRadians(-45 * D3DX_PI / 180);
		}

		else if (input->isKeyDown(VK_UP) && input->isKeyDown(VK_LEFT) ) {
			if (Map1->MapCollision(p_PosX, p_PosY, 6)) Dir_ = 6;
			nowDir_ = 6;
			
			this->setLoop(true);
			this->setAnimation(36, 41, 36, 0.2f);
			lanten->setRadians(-135 * D3DX_PI / 180);
		}

		else if (input->isKeyDown(VK_DOWN) && input->isKeyDown(VK_RIGHT)) {
			if (Map1->MapCollision(p_PosX, p_PosY, 7)) Dir_ = 7;
			nowDir_ = 7;

			this->setLoop(true);
			this->setAnimation(18, 23, 18, 0.2f);
			lanten->setRadians(45 * D3DX_PI / 180);
		}

		else if (input->isKeyDown(VK_DOWN) && input->isKeyDown(VK_LEFT)) {
			if (Map1->MapCollision(p_PosX, p_PosY, 8)) Dir_ = 8;
			nowDir_ = 8;

			this->setLoop(true);
			this->setAnimation(12, 17, 12, 0.2f);
			lanten->setRadians(135 * D3DX_PI / 180);
		}

		else if (input->isKeyDown(VK_UP)) {
			if (Map1->MapCollision(p_PosX, p_PosY, 1))  Dir_ = 1;
			nowDir_ = 1;

			this->setLoop(true);
			this->setAnimation(24, 29, 24, 0.2f);
			lanten->setRadians(-90 * D3DX_PI/180);
		}

		else if (input->isKeyDown(VK_DOWN)) {
			if (Map1->MapCollision(p_PosX, p_PosY, 2))  Dir_ = 2;
			nowDir_ = 2;

			this->setLoop(true);
			this->setAnimation(30, 35, 30, 0.2f);
			lanten->setRadians(90 * D3DX_PI / 180);
		}

		else if (input->isKeyDown(VK_LEFT) ) {
			if (Map1->MapCollision(p_PosX, p_PosY, 3))  Dir_ = 3;
			nowDir_ = 3;

			this->setLoop(true);
			this->setAnimation(0, 5, 0, 0.2f);
			lanten->setRadians(-180 * D3DX_PI / 180);
		}

		else if (input->isKeyDown(VK_RIGHT) ) {
			if (Map1->MapCollision(p_PosX, p_PosY, 4))  Dir_ = 4;
			nowDir_ = 4;

			this->setLoop(true);
			this->setAnimation(6, 11, 6, 0.2f);
			lanten->setRadians(0 * D3DX_PI / 180);
		}
	}

	switch(Dir_) {
	case 1:
		if (moveCounter >= 64) {
			p_PosY--;
			moveCounter = 0;
			break;
		}
		else Map1->mapMove(0, Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 2:
		if (moveCounter >= 64) {
			p_PosY++;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(0, -Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 3:
		if (moveCounter >= 64) {
			p_PosX--;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(Movespeed, 0);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 4:
		if (moveCounter >= 64) {
			p_PosX++;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(-Movespeed, 0);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 5:
		if (moveCounter >= 64) {
			p_PosY--;
			p_PosX++;
			moveCounter = 0;
			break;
		}
		else Map1->mapMove(-Movespeed, Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 6:
		if (moveCounter >= 64) {
			p_PosY--;
			p_PosX--;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(Movespeed, Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 7:
		if (moveCounter >= 64) {
			p_PosY++;
			p_PosX++;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(-Movespeed, -Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 8:
		if (moveCounter >= 64) {
			p_PosY++;
			p_PosX--;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(Movespeed, -Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	}
	
	if (moveCounter == 0) {
		Dir_ = 0;
	}

	//this->flipHorizontal(Dir_);

	

	if (input->isKeyDown(VK_F4) && input->isKeyDown(VK_MENU)) {
		exit(0);
	}
}

void Player::playerItemIn(int itemCode)
{
	for (int i = 0; i < 10; i++) {
		if (Player::Item[i] == NULL) {
			Player::Item[i] = itemCode;
			break;
		}
	}
}

void Player::playerItemOut(int itemCode)
{
}

void Player::setLanten(Junk2DSprite * lanten)
{
	this->lanten = lanten;
}
