#include "Player.h"

int Player::p_PosScene = 0;
int Player::p_PosX = 0;
int Player::Item[10] = {0,};

Player::Player()
{
	motionSW = 255;
}

void Player::playerSetting(Graphics* graphics)
{
	this->initialize(graphics, "..\\Resources\\Player\\Ch_01_standing.png", 250, 400, 7);
	this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	this->setLoop(true);
	//this->flipVertical(Dir_);
	this->setActive(true);
	this->setCollisionType(Junk2DentityNS::BOX);
	this->setAnimation(0, 19, 0, 0.2f);

	this->getplayerWidth();
	this->setEdge(0, 150, 218, 398);

	this->setXY(640,270);
}

void Player::playerInput(Input* input, Junk2DMap* Map1)
{
	// 플레이어 이동 클래스
	// 전부 플레이어 클래스로 만들어서 객체화 시켜서 이동할 예정
	//if (inputSW) {

		if (input->isKeyDown(VK_DOWN) ||
			input->isKeyDown(VK_UP) ||
			input->isKeyDown(VK_RIGHT) ||
			input->isKeyDown(VK_LEFT)) {

			if (motionSW != 1) {
				this->initialize(graphics, "..\\Resources\\Player\\Ch_01_walking.png", 250, 400, 7);
				this->setLoop(true);
				this->setActive(true);
				this->setAnimation(0, 19, 0, 0.2f);
				this->setEdge(0, 150, 218, 398);
			}

			motionSW = 1;

			if (input->isKeyDown(VK_DOWN)) {
				this->setY(this->getY() + Movespeed / 2);
				if (this->getY() >= GAME_HEIGHT - 390) {
					this->setY(this->getY() - Movespeed / 2);
				}
			}
			if (input->isKeyDown(VK_UP)) {
				this->setY(this->getY() - Movespeed / 2);
				if (this->getY() <= GAME_HEIGHT / 2 - 200) {
					this->setY(this->getY() + Movespeed / 2);
				}

				if (this->getX() - Movespeed <
					(GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
					this->setX(0 + (GAME_HEIGHT - 188 - this->getY() * 1.6f));
				}

				else if (this->getX() + playerSize + Movespeed >
					GAME_WIDTH - (GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
					this->setX((GAME_WIDTH - playerSize) - (GAME_HEIGHT - 188 - this->getY() * 1.6f));
				}
			}

			if (input->isKeyDown(VK_RIGHT)) {
				if (Map1->getMapX() < -mapSize || this->getX() < GAME_WIDTH / 2) {
					if (this->getX() + playerSize + Movespeed <
						GAME_WIDTH - (GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
						this->setX(this->getX() + Movespeed);
					}
				}
				else {
					Map1->mapMove(-Movespeed, 0);
				}

				Dir_ = true;
			}
			if (input->isKeyDown(VK_LEFT)) {
				if ((Map1->getMapX() >= 0 || this->getX() > GAME_WIDTH / 2)) {
					if (this->getX() - Movespeed >
						0 + (GAME_HEIGHT - 188 - this->getY() * 1.6f)) {
						this->setX(this->getX() - Movespeed);
					}
				}
				else {
					Map1->mapMove(Movespeed, 0);
				}

				Dir_ = false;
			}
		}

		else {
			if (motionSW != 0) {
				this->initialize(graphics, "..\\Resources\\Player\\Ch_01_standing.png", 250, 400, 7);
				this->setLoop(true);
				this->setActive(true);
				this->setAnimation(0, 19, 0, 0.2f);
				this->setEdge(0, 150, 218, 398);
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