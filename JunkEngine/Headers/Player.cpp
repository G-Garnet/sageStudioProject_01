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
	this->initialize(graphics, "..\\Resources\\Player\\player.png", 32, 48, 4);
	this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	this->setLoop(true);
	this->setActive(true);
	this->setCollisionType(Junk2DentityNS::BOX);
	this->setAnimation(0, 3, 0, 0.2f);

	this->getplayerWidth();

	this->setXY(640,270);
}

void Player::playerInput(Input* input, Junk2DMap* Map1)
{
	// 플레이어 이동 클래스
	// 전부 플레이어 클래스로 만들어서 객체화 시켜서 이동할 예정
	//if (inputSW) {
	if (input->isKeyDown(VK_UP) ||
		input->isKeyDown(VK_DOWN) ||
		input->isKeyDown(VK_LEFT) ||
		input->isKeyDown(VK_RIGHT)) {

		if (motionSW != 1) {
			this->initialize(graphics, "..\\Resources\\Player\\player.png", 32, 48, 4);
			this->setLoop(true);
			this->setActive(true);
			this->setCollisionType(Junk2DentityNS::BOX);
			this->setAnimation(0, 3, 0, 0.2f);
		}

		motionSW = 1;

		if (moveCounter >= 5) {
			if (input->isKeyDown(VK_UP) && Map1->MapCollision(p_PosX, p_PosY, 1)) {

				Map1->mapMove(-Movespeed, -Movespeed);
				p_PosX--;
			}

			if (input->isKeyDown(VK_DOWN) && Map1->MapCollision(p_PosX, p_PosY, 2)) {

				Map1->mapMove(Movespeed, Movespeed);
				p_PosX++;
			}

			if (input->isKeyDown(VK_LEFT) && Map1->MapCollision(p_PosX, p_PosY, 3)) {

				Map1->mapMove(-Movespeed, Movespeed);
				p_PosY--;
			}

			if (input->isKeyDown(VK_RIGHT) && Map1->MapCollision(p_PosX, p_PosY, 4)) {

				Map1->mapMove(Movespeed, -Movespeed);
				p_PosY++;
			}

			moveCounter = 0;
		}

		else {
			moveCounter++;
		}
	}
	else {
		if (motionSW != 0) {
			this->initialize(graphics, "..\\Resources\\Player\\player.png", 32, 48, 4);
			this->setLoop(true);
			this->setActive(true);
			this->setCollisionType(Junk2DentityNS::BOX);
			this->setAnimation(0, 3, 0, 0.2f);
		}

		motionSW = 0;
	}
	//}
	
	this->flipHorizontal(Dir_);

	this->update((float)1 / 60);
	

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