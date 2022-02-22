#include "StdAfx.h"
#include "Scene.h"


int CScene::TILE_WIDTH = 32;


CScene::CScene(void)
{
}

CScene::~CScene(void)
{
}

std::vector<CWinnerAssesmentTimeOut>* CScene::GetWinnerAssesment()
{
	return &m_WinnerAssesmentTimeout;
}


bool CScene::isResultAssess()
{
	return m_IsResultAssess;
}


void CScene::Init(HDC hdc) {
	players[0] = CBomber(&map, &sceneBombs, &sceneBoosts, &timeOuts, &sceneBlocks, &sceneFire, this);
	players[1] = CBomber(&map, &sceneBombs, &sceneBoosts, &timeOuts, &sceneBlocks, &sceneFire, this);

	sceneBlocks = std::vector<CBlock*>();
	sceneBombs = std::vector<CBomb*>();
	sceneBoosts = std::vector<CBoost*>();
	sceneFire = std::vector<CFire*>();
	timeOuts = std::vector<CTimeOut>();
	m_WinnerAssesmentTimeout = std::vector < CWinnerAssesmentTimeOut>();

	m_IsRunning = true;
	m_IsResultAssess = false;
	hideScreen = false;

	players[0].SetX(32);
	players[0].SetY(32);
	players[1].SetX(672);
	players[1].SetY(480);
	
	map.LoadMap();

	hideScreen = false;

	CBackground::LoadData(hdc);
	CBackground::SetAnimePhase(0);

	players[0].LoadData(hdc, "sprites\\white_bomber.bmp");
	players[1].LoadData(hdc, "sprites\\red_bomber.bmp");
	bomb.LoadData(hdc);
	fire.LoadData(hdc);
	boost.LoadData(hdc);
	block.LoadData(hdc);

	std::vector<std::vector<CRectangle>> tempMap = map.GetMap();
	for (int i = 0; i < tempMap.size(); i++)
	{
		for (int j = 0; j < tempMap[0].size(); j++)
		{
			if (tempMap[i][j].type == 2) {
				CBlock* b = new CBlock();
				*b = block;
				b->SetX(tempMap[i][j].left);
				b->SetY(tempMap[i][j].top);

				sceneBlocks.push_back(b);

			}
		}
	}
	 m_Ids = std::vector<bool>(2, false);
	 
}


void CScene::Render(HDC hdc) {

	if(!hideScreen)
		CBackground::Display(hdc);
	

		for (int i = 0; i < sceneBlocks.size(); i++)
		{
			sceneBlocks[i]->Display(hdc);
		}


		for (int i = 0; i < sceneBombs.size(); i++)
		{
			sceneBombs[i]->Display(hdc);
		}

		for (int i = 0; i < sceneBoosts.size(); i++)
		{
			sceneBoosts[i]->SetAnimPhase(sceneBoosts[i]->GetSpecial());
			sceneBoosts[i]->Display(hdc);
		}
		for (int i = 0; i < sceneFire.size(); i++)
		{
			if (sceneFire[i]->type == CFire::FIRE_TYPE_1) {
				sceneFire[i]->SetAnimRow(1);
			}
			else if (sceneFire[i]->type == CFire::FIRE_TYPE_2) {
				sceneFire[i]->SetAnimRow(2);
			}
			else if (sceneFire[i]->type == CFire::FIRE_TYPE_3) {
				sceneFire[i]->SetAnimRow(5);
			}
			else if (sceneFire[i]->type == CFire::FIRE_TYPE_4) {
				sceneFire[i]->SetAnimRow(0);
			}
			else if (sceneFire[i]->type == CFire::FIRE_TYPE_5) {
				sceneFire[i]->SetAnimRow(4);
			}
			else if (sceneFire[i]->type == CFire::FIRE_TYPE_6) {
				sceneFire[i]->SetAnimRow(3);
			}
			else if (sceneFire[i]->type == CFire::FIRE_TYPE_7) {
				sceneFire[i]->SetAnimRow(6);
			}
			sceneFire[i]->Display(hdc);
	}
	players[0].Display(hdc);
	players[1].Display(hdc);
	if(hideScreen)
		CBackground::Display(hdc);



}

void CScene::UserInputPressed(WPARAM wParam) {
	// zpracujeme uzivateluv vstup z klavesnice
	if (m_IsRunning) {
		switch (wParam)
		{
		case VK_RIGHT:
			players[0].SetMovingRight(true);
			break;

		case VK_LEFT:
			players[0].SetMovingLeft(true);
			break;

		case VK_UP:
			players[0].SetMovingUp(true);
			break;

		case VK_DOWN:
			players[0].SetMovingDown(true);
			break;
		case VK_SHIFT:
			players[0].SetBomb();
			break;

		case 0x57:
			players[1].SetMovingUp(true);
			break;

		case 0x53:
			players[1].SetMovingDown(true);
			break;

		case 0x41:
			players[1].SetMovingLeft(true);
			break;

		case 0x44:
			players[1].SetMovingRight(true);
			break;

		case VK_SPACE:
			players[1].SetBomb();
		}
	
	}
	
}

void CScene::UserInputReleased(WPARAM wParam)
{
	if (m_IsRunning) {

		players[0].SetAnimePhaseToDefault();
		players[1].SetAnimePhaseToDefault();

		switch (wParam)
		{
		case VK_RIGHT:
			players[0].SetMovingRight(false);
			players[0].StopX();
			Sleep(30);
			break;

		case VK_LEFT:
			players[0].SetMovingLeft(false);
			players[0].StopX();
			Sleep(30);
			break;

		case VK_UP:
			players[0].SetMovingUp(false);
			players[0].StopY();
			Sleep(30);

			break;

		case VK_DOWN:
			players[0].SetMovingDown(false);
			players[0].StopY();
			Sleep(30);

			break;
		case 0x57:
			players[1].SetMovingUp(false);
			players[1].StopY();
			Sleep(30);
			break;

		case 0x53:
			players[1].SetMovingDown(false);
			players[1].StopY();
			Sleep(30);
			break;

		case 0x41:
			players[1].SetMovingLeft(false);
			players[1].StopY();
			Sleep(30);
			break;

		case 0x44:
			players[1].SetMovingRight(false);
			players[1].StopY();
			Sleep(30);
			break;
		}

	}

}

void CScene::Move() {
	players[0].Move();
	players[1].Move();

	for (int i = 0; i < sceneBombs.size(); i++)
	{
		sceneBombs[i]->Animate();
	}

	for (int i = 0; i < sceneBlocks.size(); i++)
	{
		if (sceneBlocks[i]->GetBurned() == true) {
			sceneBlocks[i]->Animate();
		}
	}

	for (int i = 0; i < sceneFire.size(); i++)
	{
		sceneFire[i]->Animate();
	}
}

void CScene::GameLoop()
{

	if (m_IsRunning) {

		 if (!players[0].GetIsAlive()) {
			m_IsRunning = false;
			players[0].SetAnimeRow(4);
		}
		 if (!players[1].GetIsAlive()) {
			m_IsRunning = false;
			players[1].SetAnimeRow(4);
		}
			
			
	}
	else {
		
		if (!players[0].GetIsAlive() && !players[1].GetIsAlive()) {
			players[0].DeathAnimation();
			players[1].DeathAnimation();
		}
		else if (!players[0].GetIsAlive()) {
			players[0].DeathAnimation();
		}
		else if (!players[1].GetIsAlive()) {
			players[1].DeathAnimation();

		}
	}
	Update();
	Move();
}

void CScene::Update()
{
	for (int i = 0; i < sizeof(players) / sizeof(players[0]); i++)
	{
		players[i].Update();
	}
	if (sceneBombs.size() != 0) {
		for (int i = 0; i < sceneBombs.size(); i++)
		{
			sceneBombs[i]->Update();
		}
	
	}
	if (m_WinnerAssesmentTimeout.size() != 0) {
		if (GetTickCount() - m_WinnerAssesmentTimeout[0].GetLastTime() > 1000) {
			m_WinnerAssesmentTimeout[0].Update();

			if (!players[0].GetIsAlive() && !players[1].GetIsAlive()) {
				hideScreen = true;
				CBackground::SetAnimePhase(3);
			}
			else if (!players[0].GetIsAlive()) {
				hideScreen = true;
				CBackground::SetAnimePhase(2);
			}
			else if (!players[1].GetIsAlive()) {
				hideScreen = true;
				CBackground::SetAnimePhase(1);

			}
			m_WinnerAssesmentTimeout.erase(m_WinnerAssesmentTimeout.begin());


		}

	}
	if (timeOuts.size() != 0) {
		for (int i = 0; i < timeOuts.size(); i++)
		{
			if (GetTickCount() - timeOuts[i].GetLastTime() > 500) {
				timeOuts[i].Update();
 				timeOuts.erase(timeOuts.begin() +i);
			}
		
		}

	}
}

void CScene::SetRunning(bool running)
{
	m_IsRunning = running;
}

CBomb* CScene::GetGUIBomb()
{
	return &bomb;
}

CFire* CScene::GetGUIFire()
{
	return &fire;
}

CBoost* CScene::GetGUIBoost()
{
	return &boost;
}

void CScene::SetAssessGameResult(bool assessGameResult)
{
	m_IsResultAssess = assessGameResult;
}


std::vector<bool> CScene::CheckMultiCollision()
{
	std::vector<CRectangle> rect;
	CBomber* playersPtr = GetPlayers();
	std::vector<std::vector<CRectangle>> tempMap = map.GetMap();
	
	std::vector<CRectangle> players;

	for (int i = 0; i < 2; i++) {
		CRectangle player;
		player.top = playersPtr[i].GetY(); player.left = playersPtr[i].GetX(); player.bottom = playersPtr[i].GetY() + CBomber::PLAYER_HEIGHT; player.right = playersPtr[i].GetX() + CBomber::PLAYER_WIDTH;
		players.push_back(player);
	}

	for (int i = 0; i < tempMap.size(); i++) {
		for (int j = 0; j < tempMap[0].size(); j++) {
			if (tempMap[i][j].type == CRectangle::FIRE) {

				rect.push_back(tempMap[i][j]);
			}
		}
	}

	for (CRectangle collision : rect) {
		for (int i = 0; i < 2; i++) {
			if (collision.Intersect(players[i].left, players[i].top, players[i].right, players[i].bottom)) {
				m_Ids[i] = true;
			}
		}
	}

	return m_Ids;
}

CBomber* CScene::GetPlayers()
{
	return players;
}

 bool CScene::isRunning() {
	return m_IsRunning;
}