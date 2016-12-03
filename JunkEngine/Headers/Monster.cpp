#include "Monster.h"

Monster::Monster()
{
}

bool operator <(const node & a, const node & b) {
	return a.getPriority() > b.getPriority();
};

int Monster::FindPath(int xStart, int yStart, int xEnd, int yEnd) {

	int cNodeMap[MAP_MAXHEIGHT][MAP_MAXWIDTH] = { 0, };
	int oNodeMap[MAP_MAXHEIGHT][MAP_MAXWIDTH] = { 0, };
	// 방향들을 그려놓은 배열
	int dirMap[MAP_MAXHEIGHT][MAP_MAXWIDTH];
	int dx[dir] = { 1, 0, -1, 0 };
	int dy[dir] = { 0, 1, 0, -1 };

	std::priority_queue<node> nodeList[2];
	int Index;
	node* n;
	node* m;
	int i, j, x = 0, y = 0;
	// 다음 이동할 좌표
	int xdx, ydy;
	char c;
	Index = 0;

	m = new node(xStart, yStart, 0, 0);
	m->updatePriority();
	nodeList[Index].push(*m);
	oNodeMap[x][y] = m->getPriority();

	// 검색
	while (!nodeList[Index].empty()) {
		// 새 노드 생성
		m = new node(nodeList[Index].top().getxPos(),
			nodeList[Index].top().getyPos(),
			nodeList[Index].top().getLevel(),
			nodeList[Index].top().getPriority());

		x = m->getxPos();
		y = m->getyPos();

		nodeList[Index].pop();
		oNodeMap[x][y] = 0;
		cNodeMap[x][y] = 1;

		// 종료. 결과출력
		if (x == yEnd && y == xEnd) {
			i = 0;
			
			while (!(x == xStart && y == yStart)) {
				j = dirMap[x][y];

				moveRoute[i] = dirMap[x][y];

				x += dx[j];
				y += dy[j];

				i++;
			}

			delete m;
			while (!nodeList[Index].empty()) nodeList[Index].pop();

			return moveRoute[i-1];
		}

		// 이동
		for (i = 0; i<dir; i++) {
			
			xdx = x + dx[i]; ydy = y + dy[i];
			
			if (!(xdx<0 || xdx>MAP_MAXHEIGHT - 1 || ydy<0 || ydy>MAP_MAXWIDTH - 1 || 
				map->mapData[xdx][ydy] == 1 || cNodeMap[xdx][ydy] == 1  )) {
				// 자식 노드 생성
				n = new node(xdx, ydy, m->getLevel(), m->getPriority());
				n->nextLevel();
				n->updatePriority();

				if (oNodeMap[xdx][ydy] == 0) {
					oNodeMap[xdx][ydy] = n->getPriority();
					nodeList[Index].push(*n);
					dirMap[xdx][ydy] = (i + dir / 2) % dir;
				}

				else if (oNodeMap[xdx][ydy] > n->getPriority()) {
					oNodeMap[xdx][ydy] = n->getPriority();
					dirMap[xdx][ydy] = (i + dir / 2) % dir;
					nodeList[Index].push(*n);

					while (!(nodeList[Index].top().getxPos() == xdx &&
						nodeList[Index].top().getyPos() == ydy)) {
						nodeList[1 - Index].push(nodeList[Index].top());
						nodeList[Index].pop();
					}
					nodeList[Index].pop();

					if (nodeList[Index].size() > nodeList[1 - Index].size())
						Index = 1 - Index;

					while (!nodeList[Index].empty()) {
						nodeList[1 - Index].push(nodeList[Index].top());
						nodeList[Index].pop();
					}

					Index = 1 - Index;
					nodeList[Index].push(*n); // 더 좋은경로의 노드를 추가
				}
				else delete n;
			}
		}
		delete m;
	}
	return 0; // 경로 없음
}

void Monster::findPlayer(int playerX, int playerY)
{
	if (moveCounter == 0) {
		if (m_PosY == playerY && m_PosX == playerX) {
			return;
		}

		int falseDir_ = this->FindPath(m_PosY, m_PosX, playerX, playerY);

		switch (falseDir_) {
		case 1: Dir_ = 3;  break;
		case 2: Dir_ = 2;  break;
		case 3: Dir_ = 4;  break;
		case 0: Dir_ = 1; break;
		}
	}
	
	this->map->getMapX();
	switch (Dir_) {
	case 1:
		if (moveCounter >= 64) {
			m_PosY--;
			moveCounter = 0;
			break;
		}
		setXY(this->getX(), this->getY() - Movespeed);
		moveCounter++;
		break;
	case 2:
		if (moveCounter >= 64) {
			m_PosY++;
			moveCounter = 0;
			break;
		}
		setXY(this->getX(), this->getY() + Movespeed);
		moveCounter++;
		break;
	case 3:
		if (moveCounter >= 64) {
			m_PosX--;
			moveCounter = 0;
			break;
		}
		setXY(this->getX() - Movespeed, this->getY());
		moveCounter++;
		break;
	case 4:
		if (moveCounter >= 64) {
			m_PosX++;
			moveCounter = 0;
			break;
		}
		setXY(this->getX() + Movespeed, this->getY());
		moveCounter++;
		break;
	}

	if (moveCounter == 0) {
		Dir_ = 0;
	}
	
}

void Monster::MonseterSetting(Graphics * graphics, int tag)
{
	this->tag = tag;
	if (tag == 1) {
		this->initialize(graphics, "..\\Resources\\char\\enemy1.jpg", 256, 256, 8);
		this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
		this->setLoop(true);
		this->setActive(true);
		this->setScale(0.5f);
		this->setCollisionType(Junk2DentityNS::BOX);
		this->setAnimation(8, 15, 0, 0.2f);
	}
	else if (tag == 2) {
		this->initialize(graphics, "..\\Resources\\char\\enemy2.png", 64, 64, 9);
		this->setXY(GAME_WIDTH / 2, GAME_HEIGHT / 2);
		this->setLoop(true);
		this->setActive(true);
		this->setScale(2);
		this->setCollisionType(Junk2DentityNS::BOX);
		this->setAnimation(0, 9, 0, 0.2f);
	}

	//this->getplayerWidth();

	this->setXY(0, 0);
}
