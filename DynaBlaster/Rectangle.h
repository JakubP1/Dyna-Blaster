#pragma once
struct CRectangle
{
	int top;
	int left;
	int right;
	int bottom;
	bool walkable;
	int type;
	
	enum RectType {
		GRASS = 0,
		WALL,
		BLOCK,
		BOMB,
		FIRE_BOOST,
		BOMB_BOOST,
		FIRE
	};

	static int SIDE_LENGTH;

	CRectangle();
	CRectangle(int x, int y, int type, bool walkable);
	bool Intersect(int x1, int y1, int x2, int y2);

};

