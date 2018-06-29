#include"Map.h"

Map::Map()
{

	int map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 }
	};

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			g_map[y][x] = map[y][x];
		}

	}
}


void Map::Init()
{

	int map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{ 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 }
	};

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			g_map[y][x] = map[y][x];
		}

	}

	ItemCheckFlag = true;

	scrollX = 0;
	scrollY = 0;

	MapSprite.SetAlpha(1);
	MapSprite.SetAngle(0);
	MapSprite.SetSize(32,32);
	MapTexture.Load(_T("map.png"));
	MapTexture.SetDivide(6, 1);
	
	/*MapX = 400;
	MapY = 300;*/

	BackSprite.SetAlpha(1); 
	BackSprite.SetAngle(0); 
	BackSprite.SetSize(800,600);
	BackTexture.Load(_T("back.png"));
	BackTexture.SetDivide(1, 1);
	BackTexture.SetNum(0, 0);
	BackX = 400;
	BackY = 300;

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{

			g_map[y][x] = MAP_NOT_OBJECT;
		}
	}
	g_space.height = MAP_HEIGHT;
	g_space.width = MAP_WIDTH;

	g_spaceVec.clear();
}

void Map::SplitX(Space& t_room, Space& splited_room1, Space& splited_room2)
{
	if (t_room.width > MIN_ROOM_WIDTH * 2)
	{
		int num = t_room.baseX + (rand() % (t_room.width - MIN_ROOM_WIDTH * 2) + MIN_ROOM_WIDTH);

		for (int i = t_room.baseY; i < t_room.baseY + t_room.height; i++)
		{
			g_map[i][num] = MAP_BOUNDARY;
		}
		splited_room1.baseX = t_room.baseX;
		splited_room1.baseY = t_room.baseY;
		splited_room1.width = num - t_room.baseX;
		splited_room1.height = t_room.height;

		splited_room2.baseX = num + 1;
		splited_room2.baseY = t_room.baseY;
		splited_room2.width = t_room.width + t_room.baseX - (num + 1);
		splited_room2.height = t_room.height;

		int a = 0;
	}

}

void Map::SplitY(Space& t_room, Space& splited_room1, Space& splited_room2)
{
	if (t_room.height > MIN_ROOM_HEIGHT * 2)
	{
		int num = t_room.baseY + (rand() % (t_room.height - MIN_ROOM_HEIGHT * 2) + MIN_ROOM_HEIGHT);

		for (int i = t_room.baseX; i < t_room.baseX + t_room.width; i++)
		{
			g_map[num][i] = MAP_BOUNDARY;
		}
		splited_room1.baseX = t_room.baseX;
		splited_room1.baseY = t_room.baseY;
		splited_room1.width = t_room.width;
		splited_room1.height = num - t_room.baseY;

		splited_room2.baseX = t_room.baseX;
		splited_room2.baseY = num + 1;
		splited_room2.width = t_room.width;
		splited_room2.height = t_room.height + t_room.baseY - (num + 1);
	}
}

void Map::Split()
{
	do
	{ 
		g_spaceVec.clear();
		Split(g_space); 
	} 
	while (g_spaceVec.size()<3);

}


void Map::Split(Space& t_room)
{
	Space splited_room1, splited_room2;
	int flag = 0;

	if (rand() % 2 == 0) 
	{
		if (t_room.width > MIN_ROOM_WIDTH * 2)
		{
			SplitX(t_room, splited_room1, splited_room2);
			flag = 1;
		}
	}
	else {
		if (t_room.height > MIN_ROOM_HEIGHT * 2)
		{
			SplitY(t_room, splited_room1, splited_room2);
			flag = 1;
		}
	}

	if (flag == 1)
	{
		Split(splited_room1);
		Split(splited_room2);
	}
	else {
		g_spaceVec.push_back(t_room);
	}
}



void Map::MakeRoom()
{

	std::vector<Space>::iterator it;

	for (it = g_spaceVec.begin(); it != g_spaceVec.end(); it++)
	{
		it->room.width = rand() % (it->width - MIN_ROOM_WIDTH + 1) + MIN_ROOM_WIDTH;
		it->room.height = rand() % (it->height - MIN_ROOM_HEIGHT + 1) + MIN_ROOM_HEIGHT;
		it->room.baseX = it->baseX + (rand() % (it->width - it->room.width + 1));
		it->room.baseY = it->baseY + (rand() % (it->height - it->room.height + 1));

		for (int i = it->room.baseY; i < it->room.baseY + it->room.height; i++)
		{
			for (int j = it->room.baseX; j < it->room.baseX + it->room.width; j++)
			{
				if (i == it->room.baseY || i == it->room.baseY + it->room.height - 1 ||
					j == it->room.baseX || j == it->room.baseX + it->room.width - 1)
				{
					g_map[i][j] = MAP_WALL;
				}
				else
				{
					g_map[i][j] = MAP_ROOM;
				}
			}
		}
	}
}


void Map::MakeTrail()
{
	std::vector<Space>::iterator it;

	for (it = g_spaceVec.begin(); it != g_spaceVec.end(); it++)
	{
		int trailX, trailY;
		if (it->baseX > 0) {
			trailY = it->room.baseY + (rand() % (it->room.height - 2) + 1);
			for (int i = it->room.baseX; i >= it->baseX - 1; i--)
			{
				g_map[trailY][i] = MAP_TRAIL;
			}
		}
		if (it->baseX + it->width < MAP_WIDTH)
		{
			trailX = it->room.baseX + it->room.width - 1;
			it->room.baseX + (rand() % (it->room.width - 2) + 1);
			trailY = it->room.baseY + (rand() % (it->room.height - 2) + 1);
			for (int i = trailX; i <= it->baseX + it->width; i++) {
				g_map[trailY][i] = MAP_TRAIL;
			}
		}
		if (it->baseY > 0)
		{
			trailX = it->room.baseX + (rand() % (it->room.width - 2) + 1);
			for (int i = it->room.baseY; i >= it->baseY - 1; i--)
			{
				g_map[i][trailX] = MAP_TRAIL;
			}
		}
		if (it->baseY + it->height < MAP_HEIGHT)
		{
			trailX = it->room.baseX + (rand() % (it->room.width - 2) + 1);
			trailY = it->room.baseY + it->room.height - 1;
			for (int i = trailY; i <= it->baseY + it->height; i++)
			{
				g_map[i][trailX] = MAP_TRAIL;
			}
		}
	}
}


void Map::DeleteTrail()
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (g_map[0][i] == 1)
		{
			for (int j = 0; g_map[j][i] == 1; j++)
			{
				g_map[j][i] = 0;
			}
		}
		if (g_map[MAP_HEIGHT - 1][i] == 1)
		{
			for (int j = MAP_HEIGHT - 1; g_map[j][i] == 1; j--)
			{
				g_map[j][i] = 0;
			}
		}
	}
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		if (g_map[i][0] == 1)
		{
			for (int j = 0; g_map[i][j] == 1; j++)
			{
				g_map[i][j] = 0;
			}
		}
		if (g_map[i][MAP_WIDTH - 1] == 1)
		{
			for (int j = MAP_WIDTH - 1; g_map[i][j] == 1; j--)
			{
				g_map[i][j] = 0;
			}
		}
	}
}

void Map::SetPlayerInitPoint(int& X, int& Y)
{
	X = 10;
	Y = 10;

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (g_map[y][x] == MAP_ROOM)
			{
				X = x * 32;
				Y = y * 32;
				return;
			}
		}
	}

}


void Map::Draw()
{
	
	BackSprite.SetPos(BackX, BackY);
	BackSprite.Draw(BackTexture);
	scrollX++;
	DrawMap( scrollX,scrollY);
}



void Map::DrawMap(int scrollX,int scrollY)
{

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{

			switch (g_map[y][x])
			{
			case MAP_BOUNDARY:	printf("×");
				MapTexture.SetNum(0, 0);
				break;
			case MAP_TRAIL:		printf("×");
				MapTexture.SetNum(0, 0);
				break;
			case MAP_WALL:		printf("●");
				MapTexture.SetNum(1, 0);
				break;
			case MAP_ROOM:		printf("・");
				MapTexture.SetNum(2, 0);
				break;
			case MAP_ITEM:		printf("Y");
				if(ItemCheckFlag)
					MapTexture.SetNum(3, 0);
				break;
			case MAP_NOT_OBJECT:printf("　");
				MapTexture.SetNum(4, 0);	
				break;
			case MAP_GORL:		printf("_");
				MapTexture.SetNum(5, 0);
				break;
			}

			MapSprite.SetPos(x * 32 - scrollX,  y * 32 - scrollY);
			MapSprite.Draw(MapTexture);


		}
		puts("　");
	}
}

int Map::GetMapNum(int x,int y)
{



	if (x < 0 || x >= MAP_WIDTH)return MAP_NOT_OBJECT;
	if (y < 0 || y >= MAP_HEIGHT)return MAP_NOT_OBJECT;

	return g_map[y][x];
}

void Map::DrawAllData()
{
	for (int i = 0, count = g_spaceVec.size(); i < count; i++)
	{
		printf("Space[%d]\n", i);
		printf("BaseX  = %d\n", g_spaceVec[i].baseX);
		printf("BaseY  = %d\n", g_spaceVec[i].baseY);
		printf("height = %d\n", g_spaceVec[i].height);
		printf("width = %d\n", g_spaceVec[i].width);
		printf("Room[%d]\n", i);
		printf("BaseX  = %d\n", g_spaceVec[i].room.baseX);
		printf("BaseY  = %d\n", g_spaceVec[i].room.baseY);
		printf("height = %d\n", g_spaceVec[i].room.height);
		printf("width = %d\n", g_spaceVec[i].room.width);
		puts("-------------------");
	}
}
void Map::reset()
{

}

void Map::SetGimmickPos(int& PlayerX, int& PlayerY)
{

	int Roomnum = g_spaceVec.size();

	if (Roomnum == 0)
	{
		return;
	}

	std::vector<int>RoomList;
	for (int i = 0; i < Roomnum; i++)
	{
		RoomList.push_back(i);
		//0から部屋の最大数-1の数が一個ずつListに入る
	}

	if (Roomnum >= 3)
	{
		int Random = rand() % RoomList.size();
		int PlayerRoomnum = RoomList[Random];
		RoomList.erase(RoomList.begin() + Random);

		Random = rand() % RoomList.size();
		int GoalRoomnum = RoomList[Random];
		RoomList.erase(RoomList.begin() + Random);

		Random = rand() % RoomList.size();
		int ItemRoomnum = RoomList[Random];
		RoomList.erase(RoomList.begin() + Random);

		//プレイヤーとアイテム、ゴールを全て別の部屋に配置
		RoomInfo info = g_spaceVec[PlayerRoomnum].room;//プレイヤー
		int x = info.baseX + (rand() % (info.width - 2)) + 1;
		int y = info.baseY + (rand() % (info.height - 2)) + 1;
		PlayerX = x * 32;
		PlayerY = y * 32;
		
		info = g_spaceVec[GoalRoomnum].room;//ルーム
		x = info.baseX + (rand() % (info.width - 2)) + 1;
		y = info.baseY + (rand() % (info.height - 2)) + 1;
		g_map[y][x] = MAP_GORL;

		info = g_spaceVec[ItemRoomnum].room;//アイテム
		x = info.baseX + (rand() % (info.width - 2)) + 1;
		y = info.baseY + (rand() % (info.height - 2)) + 1;
		g_map[y][x] = MAP_ITEM;
	}
}









/*void Init(void)
{
	
}
			*/	   
				





//#define DEBUG_FLAG 0
//
//int main(void)
//{
//	srand(unsigned int(time(NULL)));
//	//Init();
//	Split(g_space);
//	MakeRoom();
//	//境界と部屋の情報を分かりやすく確認したい場合は、
//	//上記のDEBUG_FLAGを1にする。
//#if DEBUG_FLAG == 0
//	MakeTrail();
//	DeleteTrail();
//#endif
//	DrawMap();
//
//#if DEBUG_FLAG == 1
//	DrawAllData();
//#endif
//}