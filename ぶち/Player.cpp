#include "Player.h"
#include "Map.h"

void Player::Init()
{
	PlayerSprite.SetAlpha(1); //透明度
	PlayerSprite.SetAngle(0); //プレイヤーの回転
	PlayerSprite.SetSize(32, 32); // プレイヤーのサイズの指定
	PlayerTexture.Load(_T("test.png"));//画像のロード
	PlayerTexture.SetDivide(1, 1);//分割
	PlayerTexture.SetNum(0, 0);//画像の番号（左から）
	PlayerX = 10;
	PlayerY = 10;
	speed = 3.0f;
	PlayerFlag = false;
}


void Player::PlayerContoroll(Map* pMap)
{
	//移動処理＆あたり判定
	float checkX = PlayerX+16;
	float checkY = PlayerY+16;
	float moveX = 0;
	float moveY = 0;
	if (pDi->KeyState(DIK_RIGHTARROW))
	{
		checkX += 10+  speed;
		moveX += speed;
		
	}else if (pDi->KeyState(DIK_LEFTARROW))
	{
		checkX -= 10+ speed;
		moveX -= speed;
	}

	if (pDi->KeyState(DIK_DOWNARROW))
	{
		checkY += 10 + speed;
		moveY += speed;
	}else if (pDi->KeyState(DIK_UPARROW))
	{
		checkY -= 10 + speed;
		moveY -= speed;
	}

	int checkX_Map = ((int)checkX) / 32;
	int checkY_Map = ((int)checkY) / 32;

	int mapNum = pMap->GetMapNum(checkX_Map, checkY_Map);

	if (mapNum == MAP_ROOM|| mapNum==MAP_TRAIL||mapNum==MAP_BOUNDARY||mapNum==MAP_GORL||mapNum==MAP_ITEM)
	{
		PlayerX += moveX;
		PlayerY += moveY;
	}

}

bool Player::PlayerItemCheck(Map* pMap)
{
	float checkX = PlayerX + 16;
	float checkY = PlayerY + 16;
	int checkX_Map = ((int)checkX) / 32;
	int checkY_Map = ((int)checkY) / 32;
	int mapNum = pMap->GetMapNum(checkX_Map, checkY_Map);
	if (mapNum == MAP_ITEM)
	{
		pMap->ItemCheckFlag = false;
	

		PlayerFlag=true;
		return true;

	}

}

bool Player::PlayerGoalCheck(Map* pMap)
{
	float checkX = PlayerX + 16;
	float checkY = PlayerY + 16;
	int checkX_Map = ((int)checkX) / 32;
	int checkY_Map = ((int)checkY) / 32;
	int mapNum = pMap->GetMapNum(checkX_Map, checkY_Map);

	if (mapNum == MAP_GORL&&PlayerFlag==true)
	{
		return true;
	}
	return false;
}


void Player::Draw(int scrollX, int scrollY)
{
	PlayerSprite.Draw(PlayerTexture);
	PlayerSprite.SetPos(PlayerX-scrollX, PlayerY-scrollY);

}

void Player::PlayerPos(int PosX, int PosY)
{
	PlayerX = PosX;
	PlayerY = PosY;

}


void Player::check(Map* pMap)
{
	int centerX;

	int centerY;


}

