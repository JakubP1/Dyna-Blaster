#include "Map.h"
#include <fstream>


CMap::CMap()
{
	map = std::vector<std::vector<CRectangle>>(17, std::vector<CRectangle>(23));
}

void CMap::LoadMap()
{

	std::vector<std::vector<int>> mapArray(17, std::vector<int>(23));
	std::ifstream mapFile;
	mapFile.open("maps\\map1.txt");
	if (mapFile.is_open()) {
		char num = 0;
		for (int i = 0; i < 17; i++) {
			for (int j = 0; j < 23; j++) {
				if (mapFile.get(num)) {
					if (num != 10) {
						mapArray[i][j] = num - '0';
					}
					else {
						j--;
					}
				}
			}
		}
		mapFile.close();
	}
	else {
		//ERROR HANDLING
	}
	CRectangle rect;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			rect.left = j * rect.SIDE_LENGTH;
			rect.top = i * rect.SIDE_LENGTH;
			rect.right = (j + 1) * (rect.SIDE_LENGTH)-1;
			rect.bottom = (i + 1) * (rect.SIDE_LENGTH)-1;
			rect.type = mapArray[i][j];
			if (rect.type == 0)
			{
				rect.walkable = true;
			}
			else {
				rect.walkable = false;
			}
			map[i][j] = rect;
		}
	}

}

std::vector<std::vector<CRectangle>> CMap::GetMap()
{
	return map;
}

void CMap::SetRectangle(int x, int y, int type, bool walkable)
{
	map[y][x].type = type;
	map[y][x].walkable = walkable;
}




