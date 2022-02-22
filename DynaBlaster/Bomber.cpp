#include "StdAfx.h"
#include "Bomber.h"
#include "Scene.h"
#include <math.h>  
#include <string>
#include <ctime>

int CBomber::PLAYER_WIDTH = 25;
int CBomber::PLAYER_HEIGHT = 25;

int CBomber::MAXIMUM_BOMBS =6;
int CBomber::MAXIMUM_FIRE= 6 ;

int CBomber::DEFAULT_BOMBS = 1;
int CBomber::DEFAULT_FIRE = 1;

int CBomber::BOMB_TIMEOUT =2;


CBomber::CBomber(CMap* map, std::vector<CBomb*>* sceneBombs, std::vector<CBoost*>* sceneBoosts, std::vector<CTimeOut>* timeouts, std::vector<CBlock*>* sceneBlocks, std::vector<CFire*>* sceneFire,CScene* game)
{
	srand(time(NULL));
	m_SceneBlocks = sceneBlocks;
	m_Game = game;
	m_SceneBombs = sceneBombs;
	m_SceneBoosts = sceneBoosts;
	m_TimeOuts = timeouts;
	m_SceneFire = sceneFire;
	m_Map = map;

	m_BombIndexes = std::vector<std::pair<int, int>>();
	m_FireIndexes = std::vector<std::vector<std::pair<int, int>>>();

	m_AnimRow = 0;
	m_X = m_Y = 0;
	m_xMove = m_yMove = 0;
	m_AnimPhase = 0;
	m_TimeFrameInterval = 100;
	m_MaxAnimPhase = 3;

	m_MovingLeft = false;
	m_MovingRight = false;
	m_MovingUp = false;
	m_MovingDown = false;

	m_isAlive = true;

	m_PlantedBombs = 0;
	m_PlayerBombs = 1;
	m_PlayerFire = 1;
	m_WalkableBombsNum = 0;

	m_CollisionRect.top = -1;


	m_Increment = 3;
	m_LastTime = GetTickCount();

}
CBomber::CBomber(void) {

}

CBomber::~CBomber(void)
{
}

void  CBomber::SetMovingUp(bool isMovingUp) { 
	m_AnimRow = 3;
	m_MovingUp = isMovingUp;
}

void CBomber::SetMovingDown(bool isMovingDown) {
	m_AnimRow = 0;
	m_MovingDown = isMovingDown; 
}

void CBomber::SetMovingLeft(bool isMovingLeft) {
	m_AnimRow = 2;
	m_MovingLeft = isMovingLeft; 

}

void CBomber::SetMovingRight(bool isMovingRight) {
	m_AnimRow = 1;
	m_MovingRight = isMovingRight; 

}

void CBomber::SetRectangle(int x, int y, int type, bool walkable)
{
	if (m_isAlive) {

		if (type >= CFire::FIRE_TYPE_1 && type <= CFire::FIRE_TYPE_7) {
			CFire* l_Fire = new CFire(x * CScene::TILE_WIDTH, y * CScene::TILE_WIDTH, type, false);
			(*l_Fire).SetBitmap((m_Game->GetGUIFire())->GetBitmap());
			m_SceneFire->push_back(l_Fire);
			m_Map->SetRectangle(x,y, CRectangle::FIRE, walkable);
		}
		else if (type == CRectangle::BOMB) {
			CBomb* l_Bomb = new CBomb(x * CScene::TILE_WIDTH, y * CScene::TILE_WIDTH, CRectangle::BOMB, true, BOMB_TIMEOUT, m_PlayerFire, this);
			(*l_Bomb).SetBitmap((m_Game->GetGUIBomb())->GetBitmap());

			m_SceneBombs->push_back(l_Bomb);
			m_PlantedBombs++;

			m_Map->SetRectangle(x,y, type, walkable);

		}
		else {
			m_Map->SetRectangle(x,y, type, walkable);
		}
	}

}

void CBomber::SetRectangle(int x, int y, int type, bool walkable, int special)
{
	if (m_isAlive) {
 		if (type == CRectangle::BOMB_BOOST|| type== CRectangle::FIRE_BOOST) {
			m_Map->SetRectangle(x, y, type, walkable);
			CBoost* l_Boost = new CBoost(x * CScene::TILE_WIDTH, y * CScene::TILE_WIDTH, type, walkable, special);
			
			(*l_Boost).SetBitmap((m_Game->GetGUIBoost())->GetBitmap());
			m_SceneBoosts->push_back(l_Boost);
		}
	}
}



void CBomber::StopY()
{
	if (!GetMovingUp() && !GetMovingUp()) {
		m_yMove = 0;
	}
	if (!GetMovingUp() && GetMovingUp()) {
		MoveDown();
	}
	if (GetMovingUp() && !GetMovingUp()) {
		MoveUp();
	}
}



void CBomber::StopX()
{
	if (!GetMovingLeft() && !GetMovingRight()) {
		m_xMove = 0;
	}
	if (!GetMovingLeft() && GetMovingRight()) {
		MoveRight();
	}
	if (GetMovingLeft() && !GetMovingRight()) {
		MoveLeft();
	}
}

void CBomber::Die()
{
	m_isAlive = false;
}

void CBomber::Update() {

	if (GetMovingDown() && GetMovingUp()) {
		m_yMove = 0;
		SetMovingDown(false);
		SetMovingUp(false);
	}
	if (GetMovingLeft() && GetMovingRight()) {
		m_xMove = 0;
		SetMovingLeft(false);
		SetMovingRight(false);
	}
	if ((GetMovingLeft() && GetMovingUp()) || (GetMovingLeft() && GetMovingDown())) {
		m_xMove = 0;
		m_yMove = 0;
		SetMovingLeft(false);
		SetMovingDown(false);
		SetMovingUp(false);
	}

	if ((GetMovingRight() && GetMovingUp()) || (GetMovingRight() && GetMovingDown())) {
		m_xMove = 0;
		m_yMove = 0;
		SetMovingRight(false);
		SetMovingDown(false);
		SetMovingUp(false);
	}

	if (m_Game->isRunning()) {
		CheckMovementCollision();
	}

}

void CBomber::CheckMovementCollision()
{

		
	if (m_MovingUp) {
		if (m_Y + m_yMove < CScene::TILE_WIDTH) {
			m_Y = CScene::TILE_WIDTH;
		}
		else if (CheckCollisionWithMap(m_X, m_Y + m_yMove, m_X + PLAYER_WIDTH, m_Y + PLAYER_HEIGHT + m_yMove)) {
			m_yMove = 0;
		}
		else {
			m_Y += m_yMove;
		}
	}
	else if (m_MovingDown) {
		if (m_Y + m_yMove >= m_Map->GetMap().size() * CRectangle::SIDE_LENGTH) {
			m_Y = m_Map->GetMap().size() * CRectangle::SIDE_LENGTH;
		}
		else if (CheckCollisionWithMap(m_X, m_Y + m_yMove, m_X + PLAYER_WIDTH, m_Y + PLAYER_HEIGHT + m_yMove)) {
			m_yMove = 0;
		}
		else {
			m_Y += m_yMove;
		}
	
	}

	else if (m_MovingLeft) {
		
		if (m_X + m_xMove < CScene::TILE_WIDTH) {
			m_X = CScene::TILE_WIDTH;
		}
		else if (CheckCollisionWithMap(m_X + m_xMove, m_Y , m_X + PLAYER_WIDTH + m_xMove, m_Y + PLAYER_HEIGHT)) {
			m_yMove = 0;
		}
		else {
			m_X += m_xMove;
		}

	}
	else if (m_MovingRight) {

		if (m_X + m_xMove >= m_Map->GetMap()[0].size() * CRectangle::SIDE_LENGTH) {
			m_X = m_Map->GetMap()[0].size() * CRectangle::SIDE_LENGTH;
		}
		else if (CheckCollisionWithMap(m_X + m_xMove, m_Y, m_X + PLAYER_WIDTH + m_xMove, m_Y + PLAYER_HEIGHT)) {
			m_yMove = 0;
		}
		else {
			m_X += m_xMove;
		}
	}
	
	CheckCollisionWithBoost();


	if (CheckCollisionWithBomb() && m_WalkableBombsNum >= 1) {
		if (m_CollisionRect.top != -1) {
			std::vector<CBomb*>::iterator iter;
			for (iter = m_SceneBombs->begin(); iter != m_SceneBombs->end(); iter++) {
				if ((*iter)->walkable) {
					(*iter)->walkable = false;
					m_WalkableBombsNum--;
				}
			}
		}
	}

}

bool CBomber::CheckCollisionWithMap(int x1, int y1, int x2, int y2)
{
	
	std::vector<CRectangle> rect;
	std::vector<std::vector<CRectangle>> map = m_Map->GetMap();

	CRectangle player;
	player.top = y1; player.left = x1; player.bottom = y2; player.right = x2;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (!map[i][j].walkable) {

				rect.push_back(map[i][j]);
			}
		}
	}

	for (CRectangle collision : rect) {
		if (collision.Intersect(player.left, player.top, player.right, player.bottom)) {
			return true;
		}
	}
	return false;

}

bool CBomber::CheckCollisionWithBomb()
{
	std::vector<CRectangle> rect;
	std::vector<std::vector<CRectangle>> map = m_Map->GetMap();

	CRectangle player;
	player.top = m_Y; player.left = m_X; player.bottom = m_Y+ PLAYER_HEIGHT; player.right = m_X + PLAYER_WIDTH;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j].walkable && map[i][j].type == CRectangle::BOMB) {

				rect.push_back(map[i][j]);
			}
		}
	}

	for (CRectangle collision : rect) {
		if (collision.Intersect(player.left, player.top, player.right, player.bottom)) {
			SetCollisionRect(collision);
			return true;
		}
	}
	return false;
}



void CBomber::CheckCollisionWithBoost()
{
	std::vector<CRectangle> rect;
	std::vector<std::vector<CRectangle>> map = m_Map->GetMap();

	CRectangle player;
	player.top = m_Y; player.left = m_X; player.bottom = m_Y + PLAYER_HEIGHT; player.right = m_X + PLAYER_WIDTH;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if ((map[i][j].walkable && map[i][j].type == CRectangle::BOMB_BOOST) || (map[i][j].walkable && map[i][j].type == CRectangle::FIRE_BOOST)) {

				rect.push_back(map[i][j]);
			}
		}
	}

 	for (CRectangle collision : rect) {
		if (collision.Intersect(player.left, player.top, player.right, player.bottom)) {
			
			for (int i = 0; i < m_SceneBoosts->size(); i++)
			{
				if ((*m_SceneBoosts)[i]->top== collision.top && (*m_SceneBoosts)[i]->left == collision.left) {
					
					if ((*m_SceneBoosts)[i]->type == CRectangle::FIRE_BOOST) {
						if (m_PlayerFire + 1 <= MAXIMUM_FIRE) {
							m_PlayerFire++;
							SetRectangle((collision.left / CScene::TILE_WIDTH), (collision.top / CScene::TILE_WIDTH), 0, true);;
						}
						
					}
					else if ((*m_SceneBoosts)[i]->type == CBoost::BOMB_BOOST) {
						if (m_PlayerBombs + 1 <= MAXIMUM_BOMBS) {
							m_PlayerBombs++;
							SetRectangle((collision.left / CScene::TILE_WIDTH), (collision.top / CScene::TILE_WIDTH), 0, true);;

						}

					}
					m_SceneBoosts->erase(m_SceneBoosts->begin() + i);

				}
			}
		}
	}

}

void CBomber::CheckCollisionWithFire(int x, int y, int bombfire, std::string action)
{
	std::vector<std::vector<CRectangle>> map = m_Map->GetMap();

	int bIdx = 0;

	if (action == "fire") {
		m_BombIndexes.push_back(std::pair<int, int>(x, y));
		m_FireIndexes.push_back(std::vector<std::pair<int, int>>());

		m_Blocks.push_back(std::vector<CRectangle>());
		for (int k = 0; k < m_BombIndexes.size(); k++)
		{
			if (m_BombIndexes[k].first == x && m_BombIndexes[k].second == y) {
				bIdx = k;
			}
		}
	}
	else {
		for (int k = 0; k < m_BombIndexes.size(); k++)
		{
			if (m_BombIndexes[k].first == x && m_BombIndexes[k].second == y) {
				bIdx = k;
			}
		}

	}


	int yFrom = 0, xFrom = 0;
	if (y - bombfire >= 0) {
		yFrom = y - bombfire-1;
	}

	if (x - bombfire >= 0) {
		xFrom = x - bombfire-1;
	}

	int yTo, xTo;
	if (y + bombfire <= map.size() - 1) {
		yTo = y + bombfire+1;
	}
	else {
		yTo = map.size() - 1;
	}
	if (x + bombfire <= map[0].size() - 1) {
		xTo = x + bombfire+1;
	}
	else {
		xTo = map[0].size() - 1;
	}


	bool stop = false;


	for (int i = y; i >= yFrom; i--) {
		if(i >=0){
			if (action == "fire") {
				if (map[i][x].type == CRectangle::BOMB) {

					for (int k = 0; k < m_SceneBombs->size(); k++)
					{
						if ((*m_SceneBombs)[k]->top == map[i][x].top && (*m_SceneBombs)[k]->left == map[i][x].left) {

							m_ExplodingBombsIndexes.push_back(k);
						}
					}
				}
				if (map[i][x].type != CRectangle::WALL) {
					if (!stop) {
						if (map[i][x].type == CRectangle::BLOCK) {
							m_Blocks[bIdx].push_back(map[i][x]);
							for (int k = 0; k < m_SceneBlocks->size(); k++)
							{
								if ((*m_SceneBlocks)[k]->top == map[i][x].top && (*m_SceneBlocks)[k]->left == map[i][x].left) {
									(*m_SceneBlocks)[k]->SetBurned(true);
								}
							}
							stop = true;
						}
						if (map[i][x].type == CRectangle::BOMB_BOOST || map[i][x].type == CRectangle::FIRE_BOOST) {

							for (int k = 0; k < m_SceneBoosts->size(); k++)
							{
								if ((*m_SceneBoosts)[k]->top == map[i][x].top && (*m_SceneBoosts)[k]->left == map[i][x].left) {
									SetRectangle(x, i, CRectangle::GRASS, true);
									m_SceneBoosts->erase(m_SceneBoosts->begin() + k);
								}
							}
						}


						if (!stop) {
							if (i == y) {
								SetRectangle(x, y, CFire::FIRE_TYPE_4, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(i,x));
							}
							else if (i == yFrom) {
								SetRectangle(x, i, CFire::FIRE_TYPE_1, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(i,x));

							}
							else {
								SetRectangle(x, i, CFire::FIRE_TYPE_3, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(i,x));

							}
						}
					}
				}
				else {
					stop = true;
				}


			}
			else if (action == "resolve") {
				if (!stop) {
					if (
						map[i][x].type != CRectangle::WALL
						&& map[i][x].type != CRectangle::BLOCK
						) {
					
							for (int l = 0; l < m_Blocks[0].size(); l++)
							{
								for (int k = 0; k < m_SceneBlocks->size(); k++)
								{
									if ((*m_SceneBlocks)[k]->top == m_Blocks[0][l].top && (*m_SceneBlocks)[k]->left == m_Blocks[0][l].left) {
										m_SceneBlocks->erase(m_SceneBlocks->begin() + k);
										SetRectangle(x, i, CRectangle::GRASS, true);

									}
							}
						}
					}
					else {
						stop = true;
					}
				}
			}
	   }
	}
	stop = false;
	
	for (int i = y+1; i <= yTo; i++) {
		if(i <= map.size()-1){
			if (action == "fire") {
				if (map[i][x].type == CRectangle::BOMB) {

					for (int k = 0; k < m_SceneBombs->size(); k++)
					{
						if ((*m_SceneBombs)[k]->top == map[i][x].top && (*m_SceneBombs)[k]->left == map[i][x].left) {
							m_ExplodingBombsIndexes.push_back(k);
						}
					}
				}
				if (map[i][x].type != CRectangle::WALL) {

					if (!stop) {
						if (map[i][x].type == CRectangle::BLOCK) {
							m_Blocks[bIdx].push_back(map[i][x]);
							for (int k = 0; k < m_SceneBlocks->size(); k++)
							{
								if ((*m_SceneBlocks)[k]->top == map[i][x].top && (*m_SceneBlocks)[k]->left == map[i][x].left) {
									(*m_SceneBlocks)[k]->SetBurned(true);
								}
							}
							stop = true;
						}
						if (map[i][x].type == CRectangle::BOMB_BOOST || map[i][x].type == CRectangle::FIRE_BOOST) {

							for (int k = 0; k < m_SceneBoosts->size(); k++)
							{
								if ((*m_SceneBoosts)[k]->top == map[i][x].top && (*m_SceneBoosts)[k]->left == map[i][x].left) {
									SetRectangle(x, i, CRectangle::GRASS, true);
									m_SceneBoosts->erase(m_SceneBoosts->begin() + k);
								}
							}
						}
						if (!stop) {
							if (i == yTo) {
								SetRectangle(x, i, CFire::FIRE_TYPE_2, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(i, x));

							}
							else {
								SetRectangle(x, i, CFire::FIRE_TYPE_3, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(i, x));

							}
						}
					}
				}
				else {
				
					stop = true;
				}
			}
			else if (action == "resolve") {
					if (!stop) {
						if (
							map[i][x].type != CRectangle::WALL
							&& map[i][x].type != CRectangle::BLOCK
							) {
							
								for (int l = 0; l < m_Blocks[0].size(); l++)
								{
									for (int k = 0; k < m_SceneBlocks->size(); k++)
									{
										if ((*m_SceneBlocks)[k]->top == m_Blocks[0][l].top && (*m_SceneBlocks)[k]->left == m_Blocks[0][l].left) {
											m_SceneBlocks->erase(m_SceneBlocks->begin() + k);
											SetRectangle(x, i, CRectangle::GRASS, true);

										}
								}
							}
						}
						else {
							stop = true;
						}
					}
			}
	  }
	}
	stop = false;

	for (int j = x-1; j >= xFrom; j--) {
		if (j >= 0) {
			if (action == "fire") {
				if (map[y][j].type == CRectangle::BOMB) {

					for (int k = 0; k < m_SceneBombs->size(); k++)
					{
						if ((*m_SceneBombs)[k]->top == map[y][j].top && (*m_SceneBombs)[k]->left == map[y][j].left) {
							m_ExplodingBombsIndexes.push_back(k);
						}
					}

				}

				if (map[y][j].type == CRectangle::BOMB_BOOST || map[y][j].type == CRectangle::FIRE_BOOST) {

					for (int k = 0; k < m_SceneBoosts->size(); k++)
					{
						if ((*m_SceneBoosts)[k]->top == map[y][j].top && (*m_SceneBoosts)[k]->left == map[y][j].left) {
							SetRectangle(j, y, CRectangle::GRASS, true);
							m_SceneBoosts->erase(m_SceneBoosts->begin() + k);
						}
					}
				}

				if (map[y][j].type != CRectangle::WALL) {


					if (!stop) {
						if (map[y][j].type == CRectangle::BLOCK) {
							m_Blocks[bIdx].push_back(map[y][j]);
							for (int k = 0; k < m_SceneBlocks->size(); k++)
							{
								if ((*m_SceneBlocks)[k]->top == map[y][j].top && (*m_SceneBlocks)[k]->left == map[y][j].left) {
									(*m_SceneBlocks)[k]->SetBurned(true);
								}
							}
							stop = true;
						}
						if (!stop) {
							if (j == xFrom) {
								SetRectangle(j, y, CFire::FIRE_TYPE_5, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(y, j));
							}
							else {
								SetRectangle(j, y, CFire::FIRE_TYPE_7, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(y, j));
							}
						}
						
					}
				}
				else {
					stop = true;
				}


			}
			else if (action == "resolve") {
				if (!stop) {
					if (
						map[y][j].type != CRectangle::WALL
						&& map[y][j].type != CRectangle::BLOCK
						) {

							for (int l = 0; l < m_Blocks[0].size(); l++)
							{
								for (int k = 0; k < m_SceneBlocks->size(); k++)
								{
								if ((*m_SceneBlocks)[k]->top == m_Blocks[0][l].top && (*m_SceneBlocks)[k]->left == m_Blocks[0][l].left) {
									m_SceneBlocks->erase(m_SceneBlocks->begin() + k);
									SetRectangle(j, y, CRectangle::GRASS, true);
								}
							}
						}
					}
					else {
						stop = true;
					}
				}
			}
		}
	}
	stop = false;

	for (int j = x+1; j <= xTo; j++) {
		if (j <= map[0].size() - 1) {
			if (action == "fire") {
				if (map[y][j].type == CRectangle::BOMB) {

					for (int k = 0; k < m_SceneBombs->size(); k++)
					{
						if ((*m_SceneBombs)[k]->top == map[y][j].top && (*m_SceneBombs)[k]->left == map[y][j].left) {
							m_ExplodingBombsIndexes.push_back(k);
						}
					}
				}
				if (map[y][j].type == CRectangle::BOMB_BOOST || map[y][j].type == CRectangle::FIRE_BOOST) {

					for (int k = 0; k < m_SceneBoosts->size(); k++)
					{
						if ((*m_SceneBoosts)[k]->top == map[y][j].top && (*m_SceneBoosts)[k]->left == map[y][j].left) {
							SetRectangle(j, y, CRectangle::GRASS, true);
							m_SceneBoosts->erase(m_SceneBoosts->begin() + k);
						}
					}
				}

				if (map[y][j].type != CRectangle::WALL) {

					if (!stop) {
						if (map[y][j].type == CRectangle::BLOCK) {
							m_Blocks[bIdx].push_back(map[y][j]);
							for (int k = 0; k < m_SceneBlocks->size(); k++)
							{
								if ((*m_SceneBlocks)[k]->top == map[y][j].top && (*m_SceneBlocks)[k]->left == map[y][j].left) {
									(*m_SceneBlocks)[k]->SetBurned(true);
								}
							}
							stop = true;
						}
						if (!stop) {
							if (j == xTo) {
								SetRectangle(j, y, CFire::FIRE_TYPE_6, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(y, j));
							}
							else {
								SetRectangle(j, y, CFire::FIRE_TYPE_7, false);
								m_FireIndexes[bIdx].push_back(std::pair<int, int>(y, j));
							}
						}

					}
				}
				else {
					stop = true;
				}

			}
			else if (action == "resolve") {
				if (!stop) {
					if (
						map[y][j].type != CRectangle::WALL
						&& map[y][j].type != CRectangle::BLOCK
						) {
						
							for (int l = 0; l < m_Blocks[0].size(); l++)
							{
								for (int k = 0; k < m_SceneBlocks->size(); k++)
								{
								if ((*m_SceneBlocks)[k]->top == m_Blocks[0][l].top && (*m_SceneBlocks)[k]->left == m_Blocks[0][l].left) {
									m_SceneBlocks->erase(m_SceneBlocks->begin() + k);
									SetRectangle(j, y, CRectangle::GRASS, true);

								}
							}

						}
					}
					else {
						stop = true;
					}
				}
			}
		}
	}


	if (action == "resolve") {
		for (int b = 0; b < m_Blocks[0].size(); b++) {
			if (map[m_Blocks[0][b].top / CScene::TILE_WIDTH][m_Blocks[0][b].left / CScene::TILE_WIDTH].type != CRectangle::BOMB_BOOST && map[m_Blocks[0][b].top / CScene::TILE_WIDTH][m_Blocks[0][b].left / CScene::TILE_WIDTH].type != CRectangle::FIRE_BOOST) {
				int random = 2;
				int special = rand() % 2;
				if (special == 1) {
					int item = rand() % 2;
					
						if (item == CBoost::BOMB) {
							SetRectangle(
								(m_Blocks[0][b].left / CScene::TILE_WIDTH), (m_Blocks[0][b].top / CScene::TILE_WIDTH),
								CRectangle::BOMB_BOOST, true, CBoost::BOMB
							);
						}
						else if (item == CBoost::FIRE) {
							SetRectangle(
								(m_Blocks[0][b].left / CScene::TILE_WIDTH), (m_Blocks[0][b].top / CScene::TILE_WIDTH),
								CRectangle::FIRE_BOOST, true, CBoost::FIRE
							);

						}
					}

				else {
					SetRectangle(m_Blocks[0][b].left/ CScene::TILE_WIDTH, m_Blocks[0][b].top/ CScene::TILE_WIDTH,CRectangle::GRASS, true);
				}
			}
		}

				for (int i = 0; i < m_FireIndexes[0].size(); i++)
				{
					for (int k = 0; k < m_SceneFire->size(); k++)
					{
						if ((*m_SceneFire)[k]->top == (m_FireIndexes[0][i].first * m_Game->TILE_WIDTH) && (*m_SceneFire)[k]->left == (m_FireIndexes[0][i].second * m_Game->TILE_WIDTH)) {

							m_SceneFire->erase(m_SceneFire->begin() + k);
							SetRectangle(m_FireIndexes[0][i].second, m_FireIndexes[0][i].first, CRectangle::GRASS, true);

						}

				}
			
		}
	
	m_FireIndexes.erase(m_FireIndexes.begin());
	m_BombIndexes.erase(m_BombIndexes.begin());
	m_Blocks.erase(m_Blocks.begin());

	}
}






void CBomber::Explode(int x, int y, int bombfire)
{
	SetRectangle(x, y, 0, true);
	CheckCollisionWithFire(x, y, bombfire, "fire");

	m_TimeOuts->push_back(CTimeOut(x, y, bombfire, "resolve" ,this));
	std::vector<bool> collisions = m_Game->CheckMultiCollision();

	
	if ((collisions[0] || collisions[1])&& !m_Game->isResultAssess()) {
		m_Game->SetAssessGameResult(true);
		m_Game->GetWinnerAssesment()->push_back(CWinnerAssesmentTimeOut());
	}
	for (int i = 0; i <collisions.size(); i++) {
		if (collisions[i]) {
			m_Game->GetPlayers()[i].Die();	
		}
	 }
	if (m_ExplodingBombsIndexes.size() >= 1) {
		 ExplodeOtherBombs();
	}

	int index = -1;

	for (int i = 0; i < m_SceneBombs->size(); i++)
	{
   		if ((*m_SceneBombs)[i]->top == y * CScene::TILE_WIDTH && (*m_SceneBombs)[i]->left == x * CScene::TILE_WIDTH) {
			m_SceneBombs->erase(m_SceneBombs->begin() + i);
			m_PlantedBombs--;
		}
	}

}

void CBomber::ExplodeOtherBombs()
{
		for (int i = 0; i < 1; i++) {
			CBomb* b = (*m_SceneBombs)[m_ExplodingBombsIndexes[i]];
			(*m_SceneBombs)[m_ExplodingBombsIndexes[i]]->SetBombed(true);
		    m_ExplodingBombsIndexes.erase(m_ExplodingBombsIndexes.begin());
			Explode((b->left/32), (b->top/32), b->GetBombFire());
		}
}




void CBomber::SetAnimePhaseToDefault()
{
	m_AnimPhase = 0;
}

void CBomber::SetAnimeRow(int animeRow)
{
	m_AnimRow = animeRow;
}

void CBomber::DeathAnimation()
{
	if (m_AnimRow <6) {
		if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) {
			m_AnimPhase++;
			if (m_AnimPhase >= m_MaxAnimPhase) { 
				m_AnimPhase = 0;
				m_AnimRow++; }
		}
	}
}



bool CBomber::CanSetBomb()
{
	return (m_PlantedBombs < m_PlayerBombs);
}

void CBomber::SetBomb()
{
	std::vector<std::vector<CRectangle>> map = m_Map->GetMap();
	if (CanSetBomb()) {
		int tileY = (int)round(m_Y / CScene::TILE_WIDTH);
		int tileX = (int)round(m_X / CScene::TILE_WIDTH);

		if (map[tileY][tileX].type != CRectangle::BOMB) {
			SetRectangle(tileX, tileY, CRectangle::BOMB, true);

			m_WalkableBombsNum++;
		}
	}
}

void CBomber::SetCollisionRect(CRectangle collisionRect)
{
	m_CollisionRect = collisionRect;
}

int CBomber::GetX() {
	return m_X;
}
int CBomber::GetY() {
	return m_Y;
}

int CBomber::GetPlayerBombs()
{
	return m_PlayerBombs;
}

int CBomber::GetPlayerFire()
{
	return m_PlayerFire;
}


bool CBomber::GetIsAlive()
{
	return m_isAlive;
}

bool CBomber::GetMovingDown()
{
	return m_MovingDown;
}

bool CBomber::GetMovingUp()
{
	return m_MovingUp;
}

bool CBomber::GetMovingLeft()
{
	return m_MovingLeft;
}

bool CBomber::GetMovingRight()
{
	return m_MovingRight;
}



void CBomber::SetX(double x) {
	m_X = x;
}

void CBomber::SetY(double y) {
	m_Y = y;
}
  
void CBomber::LoadData(HDC dc, const char* sprite_name) {
	
	char path[50];
	strcpy_s(path, sprite_name);
	m_Btm.LoadBitmap((char *)path, dc);
    m_Btm.SetAnim(36, 41);

}

void CBomber::Display(HDC dc) {
	m_Btm.DisplayTransparentAnim(dc, m_X-4, m_Y-9, m_AnimPhase, m_AnimRow);
}

void CBomber::Move() {

		if (m_MovingRight) {
			if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) {
				m_AnimPhase++;
				m_LastTime = GetTickCount();
				if (m_AnimPhase >= m_MaxAnimPhase) { m_AnimPhase = 0; }
			}
			    MoveRight();
			
		}
		if (m_MovingLeft) {
			
			if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) {
				m_AnimPhase++;
				m_LastTime = GetTickCount();
				if (m_AnimPhase >= m_MaxAnimPhase) { m_AnimPhase = 0; }
			}
				MoveLeft();
			
		}
		if (m_MovingUp) {
			
			if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) {
				m_AnimPhase++;
				m_LastTime = GetTickCount();
				if (m_AnimPhase >= m_MaxAnimPhase) { m_AnimPhase = 0; }
			}
				MoveUp();
		}
		if (m_MovingDown) {
			
			if ((GetTickCount() - m_LastTime) > m_TimeFrameInterval) {
				m_AnimPhase++;
				m_LastTime = GetTickCount();
				if (m_AnimPhase >= m_MaxAnimPhase) { m_AnimPhase = 0; }
			}
				MoveDown();
		}


	}
