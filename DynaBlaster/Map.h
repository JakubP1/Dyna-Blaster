#pragma once
#include "rectangle.h"
#include "vector"
class CMap
{
	std::vector<std::vector<CRectangle>> map;


public:
	CMap();
	void LoadMap();
	std::vector<std::vector<CRectangle>> GetMap();
	void SetRectangle(int x, int y, int type, bool walkable);
	
};

