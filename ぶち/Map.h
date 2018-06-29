#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<vector>

#include "Direct3D.h"
#include "Texture.h"
#include "Sprite.h"


#define MIN_ROOM_WIDTH 8
#define MIN_ROOM_HEIGHT 8
#define MAP_WIDTH 32
#define MAP_HEIGHT 25

struct RoomInfo
{
	int baseX;
	int baseY;
	int width;
	int height;
	RoomInfo()
	{
		baseX = baseY = 0;
		width = height = 0;
	}
};

struct Space
{
	int baseX;
	int baseY;
	int width;
	int height;
	RoomInfo room;
	Space()
	{
		baseX = baseY = 0;
		width = height = 0;
	}
};




class Map
{
private:
	Space g_space;
	std::vector<Space> g_spaceVec;
	
	int MapX;
	int MapY;
	int BackX;
	int BackY;
	Sprite MapSprite;
	Sprite BackSprite;
	Texture MapTexture;
	Texture BackTexture;
public:
	Map();
	void Draw();
	void Init();
	int scrollX;
	int scrollY;
	bool ItemCheckFlag;

	int g_map[MAP_HEIGHT][MAP_WIDTH];
	void DrawMap(int scrollx ,int scrolly);
	void SplitX(Space& t_room, Space& splited_room1, Space& splited_room2);
	void SplitY(Space& t_room, Space& splited_room1, Space& splited_room2);
	void Split(Space& t_room);
	void Split();
	void MakeRoom();
	void DeleteTrail();
	void DrawAllData();
	void MakeTrail();
	void SetPlayerInitPoint(int& x, int& y);
	int GetMapNum(int x, int y);
	void SetGimmickPos(int& PlayerX, int& PlayerY);
	void reset();
};


enum MapID
{
	MAP_NOT_OBJECT,
	MAP_BOUNDARY,
	MAP_WALL,
	MAP_ROOM,
	MAP_TRAIL,
	MAP_MAX,
	MAP_GORL,
	MAP_ITEM
};


#define DEBUG_FLAG 0

int main(void);