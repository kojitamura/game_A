#pragma once

#include "Texture.h"
#include "DirectInput.h"
#include "Sprite.h"

class Map;

class Player
{
private:
	int PlayerX;
	int PlayerY;
	float speed;
	Sprite PlayerSprite;
	Texture PlayerTexture;
	DirectInput *pDi = DirectInput::GetInstansce();
	bool PlayerFlag;



public:
	void PlayerContoroll(Map* pMap);
	void Init();
	void Draw(int scrollX,int scrollY);
	void PlayerPos(int PosX,int PosY);

	int GetPlayerX() { return PlayerX; }
	int GetPlayerY() { return PlayerY; }
	bool PlayerItemCheck(Map* pMap);
	bool PlayerGoalCheck(Map* pMap);



	void check(Map* pMap);
};

