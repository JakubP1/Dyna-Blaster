#pragma once

#include "bomber.h"
#include "bomb.h"
#include "block.h"
#include "background.h"
#include "map.h"
#include "boost.h"
#include "fire.h"
#include "memory"
#include <vector>
#include "WinnerAssesmentTimeOut.h"


class CScene
{

private:
	CMap map;
	std::vector<CBlock*> sceneBlocks;
	std::vector<CBomb*> sceneBombs;
	std::vector<CBoost*> sceneBoosts;
	std::vector<CFire*> sceneFire;
	std::vector<CTimeOut> timeOuts;
	
	std::vector<bool> m_Ids;
	std::vector<CWinnerAssesmentTimeOut> m_WinnerAssesmentTimeout;

	CBomber players[2];
	CBlock block;
	CBomb bomb;
	CBoost boost;
	CFire fire;
	bool m_IsRunning;
	bool hideScreen;
	bool m_IsResultAssess;


public:
	static int TILE_WIDTH;

	void Init(HDC hdc);
	void Render(HDC hdc);
	void UserInputPressed(WPARAM wParam);
	void UserInputReleased(WPARAM wParam);
	void Move();
	void GameLoop();
	void Update();

	void SetRunning(bool running);
	void SetAssessGameResult(bool assessGameResult);

	CBomb* GetGUIBomb();
	CFire* GetGUIFire();
	CBoost* GetGUIBoost();

	std::vector<bool> CheckMultiCollision();

	CBomber* GetPlayers();
	std::vector<CWinnerAssesmentTimeOut>* GetWinnerAssesment();

	bool isRunning();
	bool isResultAssess();
	CScene();
	~CScene(void);
};


