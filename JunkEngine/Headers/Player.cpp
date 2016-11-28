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
		if (input->isKeyDown(VK_UP) && Map1->MapCollision(p_PosX, p_PosY, 1)) {
			Dir_ = 1;

			this->setLoop(true);
			this->setAnimation(24, 29, 24, 0.2f);
		}

		if (input->isKeyDown(VK_DOWN) && Map1->MapCollision(p_PosX, p_PosY, 2)) {
			Dir_ = 2;
			this->setLoop(true);
			this->setAnimation(30, 35, 30, 0.2f);
		}

		if (input->isKeyDown(VK_LEFT) && Map1->MapCollision(p_PosX, p_PosY, 3)) {
			Dir_ = 3;
			this->setLoop(true);
			this->setAnimation(0, 5, 0, 0.2f);
		}

		if (input->isKeyDown(VK_RIGHT) && Map1->MapCollision(p_PosX, p_PosY, 4)) {
			Dir_ = 4;
			this->setLoop(true);
			this->setAnimation(6, 11, 6, 0.2f);
		}
	}

	switch(Dir_) {
	case 1:
		if (moveCounter >= 32) {
			p_PosY--;
			moveCounter = 0;
			break;
		}
		else Map1->mapMove(0, Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 2:
		if (moveCounter >= 32) {
			p_PosY++;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(0, -Movespeed);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 3:
		if (moveCounter >= 32) {
			p_PosX--;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(Movespeed, 0);
		moveCounter++;
		this->update((float)1 / 60);
		break;
	case 4:
		if (moveCounter >= 32) {
			p_PosX++;
			moveCounter = 0;
			break;
		}
		Map1->mapMove(-Movespeed, 0);
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
	int i = 0;
	for (i = 0; i < 10; i++) {
		if (Player::Item[i] == itemCode) {
			Player::Item[i] = NULL;
			break;
		}
	}

	for (; i < 8; i++) {
		if (Player::Item[i] != NULL) {
			Player::Item[i] = Player::Item[i+1];
		}
	}
	Player::Item[9] = NULL;
}