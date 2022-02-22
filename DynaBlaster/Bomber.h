#pragma once
#include "Bitmap.h"
#include <string>
#include <vector>
#include "bomb.h"
#include "map.h"
#include "boost.h";
#include "fire.h"
#include "timeout.h"
#include "memory"



class CScene;

class CBomber
{	
	CBitmap m_Btm; // bitmapa s animacemi (dlazdicemi)
	CScene* m_Game;
	CMap* m_Map;
	std::vector<CBomb*>* m_SceneBombs;
	std::vector<CBoost*>* m_SceneBoosts;
	std::vector<CFire*>* m_SceneFire;
	std::vector<CTimeOut>* m_TimeOuts;
	std::vector<CBlock*>* m_SceneBlocks;

	std::vector<std::pair<int, int>> m_BombIndexes;
	std::vector<std::vector<std::pair<int, int>>> m_FireIndexes;


	int m_AnimPhase; // cislo animacni faze - index faze(dlazdice) v bitmape 
	int m_AnimRow; // cislo radku v bitmape pro animacni fazi
	int m_MaxAnimPhase; // maximalni index animacni faze (dlazdice) v bitmape  
	
	
	DWORD m_TimeFrameInterval; // interval v ms kdy se bude menit animacni faze
	DWORD m_LastTime; // posledni cas, kdy se menila animacni faze

	CRectangle m_CollisionRect;

	double m_X; 
	double m_Y;

	double m_xMove;
	double m_yMove;

	bool m_MovingLeft;
	bool m_MovingRight;
	bool m_MovingUp;
	bool m_MovingDown;

	bool m_isAlive;

	int m_PlantedBombs;

	std::vector<int> m_ExplodingBombsIndexes;
	std::vector<std::vector<CRectangle>> m_Blocks;



	int m_PlayerBombs;
	int m_PlayerFire;
	int m_WalkableBombsNum;

	double m_Increment;


public:
	static int PLAYER_WIDTH;
	static int PLAYER_HEIGHT;

	static int MAXIMUM_BOMBS;
	static int MAXIMUM_FIRE;

	static int DEFAULT_BOMBS;
	static int DEFAULT_FIRE;

	static int BOMB_TIMEOUT;

public:


	void LoadData(HDC dc, const char* sprite_name);
	void Display(HDC dc);
	void Move();
	void Update();
	void SetAnimePhaseToDefault();
	void SetAnimeRow(int animeRow);
	void DeathAnimation();
	
	void SetX(double x);
	void SetY(double y);

	void SetMovingUp(bool isMovingUp);
	void SetMovingDown(bool isMovingDown);
	void SetMovingLeft(bool isMovingLeft);
	void SetMovingRight(bool isMovingRight);

	void SetRectangle(int x, int y, int type, bool walkable);
	void SetRectangle(int x, int y, int type, bool walkable, int special);

	void MoveDown() { m_yMove = m_Increment; }
	void MoveUp() { m_yMove = -m_Increment; }
	void MoveLeft() { m_xMove = -m_Increment; }
	void MoveRight() { m_xMove = m_Increment; }

	void StopY();
	void StopX();
	void Die();

	
	void CheckMovementCollision();
	bool CheckCollisionWithMap(int x1, int y1, int x2, int y2);
	bool CheckCollisionWithBomb();

	void CheckCollisionWithBoost();
	void CheckCollisionWithFire(int x, int y, int bombfire, std::string action);



	void Explode(int x, int y, int bombfire);
	void ExplodeOtherBombs();
	void SetBomb();
	void SetCollisionRect(CRectangle collisionRect);

	bool CanSetBomb();


// ## GETTERS
	int GetX();
	int GetY();
	int GetPlayerBombs();
	int GetPlayerFire();

	bool GetIsAlive();

	bool GetMovingDown();
	bool GetMovingUp();
	bool GetMovingLeft();
	bool GetMovingRight();

	CBomber(CMap* map, std::vector<CBomb*> *sceneBombs, std::vector<CBoost*> *sceneBoosts, std::vector<CTimeOut> *m_TimeOuts, std::vector<CBlock*> *sceneBlocks, std::vector<CFire*>* sceneFire,CScene* game);
	CBomber();
	~CBomber(void);
};


