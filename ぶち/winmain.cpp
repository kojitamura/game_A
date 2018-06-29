
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#include <tchar.h>
#include"Direct3D.h"
#include"Sprite.h"
#include"Texture.h"
#include"DirectInput.h"
#include "Player.h"
#include "Map.h"
#include "camera.h"
#include "DirectSound.h"
#include "Wave.h"
#include "SoundBuffer.h"
#include <time.h>


enum GameMode
{
	Title,
	GamePlay,
	Clear,
	Over
};



//ウィンドウプロシージャ
LRESULT CALLBACK WndPrc
(
	HWND hWnd,	//ウィンドウのハンドル
	UINT msg,	//メッセージ
	WPARAM wParam,
	LPARAM lParam
)
{
	//メッセージ処理のための関数
	//DispatchMessageによって呼び出される

	//ウィンドウクラスの登録時に
	//各ウィンドウに設定される

	//アプリケーションがメッセージを
	//取得したら呼び出される

	//メッセージの例

	//WM_DESTROY ウィンドウが破棄された
	//			 ×ボタンが押された時など
	//WM_MOVE    ウィンドウが移動
	//WM_SIZE    ウィンドウサイズの変更
	//等

	//特別な処理を必要とする場合
	//または自分で独自の処理を定義したい場合
	//ここでメッセージの種類に応じた
	//処理を行う

	//取りあえず WM_DESTROYが来た時の
	//終了処理のみ定義

	switch (msg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);

		//メッセージキューに
		//新しくWM_QUITメッセージを送る

		//いずれメッセージキューから
		//取り出され
		//メインループが終了する
		//(メインループの終了条件を
		//そのように作る)
		break;
	}

	//独自の処理を行ったら
	//デフォルトのウィンドウプロシージャを実行

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//ウィンドウ設定の名前
static const TCHAR* WC_BASIC = _T("Basic");

//作りたいウィンドウの設定を
//登録する関数
HRESULT RegistClassEx(HINSTANCE hInstance)
{
	//ウィンドウの設定を保存する構造体
	WNDCLASSEX wcex;

	//wcexの先頭アドレスから
	//WNDCLASSEXの長さ分のメモリを
	//全て0で埋める
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	//つまりはwcexが使用しているメモリ領域を
	//全て0で初期化する処理

	//ウィンドウの設定

	//構造体のサイズ
	wcex.cbSize = sizeof(WNDCLASSEX);

	//ウィンドウの設定情報に追加する捕捉を付けないので
	//0で固定
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	//Windowのスタイル
	//それぞれがビット単位のフラグであるため
	//オア演算で合成したものがスタイルの最終的な設定
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//CS_HREDRAW 横サイズが変わったときウィンドウ全体の再描画
	//   VREDRAW 縦サイズが変わったときウィンドウ全体の再描画
	//   DBLCLKS ダブルクリックが発生したことをウィンドウに通知

	//WinMainのインスタンスハンドル
	wcex.hInstance = hInstance;

	//ウィンドウプロシージャのアドレス
	//関数ポインタの設定
	//ウィンドウプロシージャをOSが呼び出せるようにする
	wcex.lpfnWndProc = (WNDPROC)WndPrc;

	//背景色
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//メニュー　なし
	wcex.lpszMenuName = NULL;

	//ウィンドウクラスの名前　このウィンドウ設定の名前
	wcex.lpszClassName = WC_BASIC;

	//アイコン　デフォルトのを使う
	wcex.hIcon = (HICON)LoadImage(NULL,
		MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);
	wcex.hIconSm = NULL;

	//カーソル デフォルトのものを使う
	wcex.hCursor = (HCURSOR)LoadImage(NULL,
		MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR,
		0,
		0,
		LR_DEFAULTSIZE | LR_SHARED);

	//設定したウィンドウクラスを登録
	//登録したウィンドウ設定でないと
	//ウィンドウを作ることができない
	return RegisterClassEx(&wcex);
	//HRESULT型の実行結果が戻される
}


//登録した設定を基にウィンドウを作成する
HRESULT MakeWindow
(HINSTANCE hInstance,//WinMainの識別子
	HWND &refHWnd,	//ウィンドウの識別子
					//正しくウィンドウの作成ができたら
					//この変数に識別子を代入する
	int width = 400,	//クライアント領域の幅
	int height = 300)	//クライアント領域の高さ
						//クライアント領域はウィンドウ全体から
						//外枠やメニューの部分を除いた物と今は思っておけばOK
{
	//クライアント領域のおおきさを決める
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	//クライアント領域を保持するのに必要な
	//ウィンドウのおおきさを計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE/*TRUE*/);
	//正しく実行されるとrectの値が更新される

	//WS_OVERLAPPEDWINDOWはウィンドウのスタイルの一つ

	//ウィンドウのハンドル
	//ウィンドウの識別に使用する
	HWND hWnd;

	hWnd = CreateWindowEx
	(0,						//ウィンドウ拡張スタイル
		WC_BASIC,				//作りたいウィンドウクラス
								//あらかじめ登録されたもの
		_T("2Dゲーム"),			//ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,	//ウィンドウのスタイル
		CW_USEDEFAULT,			//位置x座標 デフォルトの値
		CW_USEDEFAULT,			//位置y座標 デフォルトの値
		rect.right - rect.left,	//ウィンドウ全体の幅
		rect.bottom - rect.top, //ウィンドウ全体の高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューのハンドル
		hInstance,				//WinMainのハンドル

		NULL);					//ウィンドウ作成データ
								//ウィンドウに好きな32ビットのデータを
								//付属させることができる
								//追加情報構造体へのポインタなど
								//を付けるのが無難な使い方か
								//今回は使わない

								//ウィンドウが正しく作れたかをチェック
								//正しく作れたらhWndにNULL以外が入るはず
	if (hWnd == NULL)
	{
		return S_FALSE;//HRESULT型　失敗を表す識別子の一つ
	}

	//ウィンドウをアクティブにして表示
	//hWndでウィンドウの識別をしていることに注目
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//クライアント領域の更新
	UpdateWindow(hWnd);

	//参照渡しになっている引数に
	//ウィンドウの識別ハンドルをコピーする
	//これによって今作ったウィンドウの識別ハンドルを
	//呼び出し元のプログラムで得ることができる
	refHWnd = hWnd;

	//HRESULT型　成功を表す識別子の一つ
	return S_OK;
}


//エントリーポイント
//プログラムの開始関数

int _stdcall WinMain
(HINSTANCE hInstance,	//プログラムを識別するハンドル
	HINSTANCE hPrevInstance,//アプリケーションの前のインスタンスハンドル
							//win32だと常にNULL
	LPSTR lpCmdLine,		//コマンドライン引数
	int nCmdShow)		//ウィンドウの表示状態
{
	//メッセージボックス
	MessageBox(NULL,		//ウィンドウのハンドル 
		TEXT("こんにちわ"),		//本文
		TEXT("2Dゲーム"),//タイトル
		MB_OK);				//メッセージボックスのタイプ
							//MB_OK  okのボタンが表示

	if (FAILED(RegistClassEx(hInstance)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウクラス設定失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	HWND hWnd = NULL;

	//正しくウィンドウが作成されれば
	//hWndにウィンドウの識別ハンドルが入る
	if (FAILED(MakeWindow(hInstance, hWnd)))
	{
		MessageBox(NULL,
			TEXT("ウィンドウ作成失敗"),
			TEXT("テスト-タイトル"),
			MB_OK);
		return 0;
	}

	//Direct3Dを管理するクラス(シングルトン)への参照を取得
	Direct3D& d3d = Direct3D::GetInstance();

	//Direct3DDeviceの作成を試みる
	if (d3d.TryCreate(hWnd))
	{
		MessageBox(NULL,
			TEXT(""),
			TEXT("2Dゲーム"),
			MB_OK);
	}

	//レンダーステートの設定  αブレンド
	d3d.SetRenderState(RENDERSTATE::RENDER_ALPHABLEND);

	Sprite spritescene;
	spritescene.SetAlpha(1);//透明度
	spritescene.SetAngle(0);//何度回転するか（角度）
	spritescene.SetSize(400, 300);//画像の大きさ
	spritescene.SetPos(200, 150);//画像の描画位置


	Texture tTitle;
	Texture tClear;
	Texture tOver;

	tTitle.Load(_T("title.png"));
	tTitle.SetDivide(1, 1);//画像の分割
	tTitle.SetNum(0, 0);//分割設定したとこのどこを使うか


	tClear.Load(_T("clear.png"));
	tClear.SetDivide(1, 1);//画像の分割
	tClear.SetNum(0, 0);//分割設定したとこのどこを使うか

	tOver.Load(_T("Over.png"));
	tOver.SetDivide(1, 1);//画像の分割
	tOver.SetNum(0, 0);//分割設定したとこのどこを使うか


	bool titleflag = true;
	bool endflag = false;

	bool titlebgmFlag = false;
	bool mainbgmFlag = false;
	bool getbgmFlag = false;
	bool clearbgmFlag = false;

	Map map;
	map.Init();

	srand(unsigned int(time(NULL)));

	GameMode gamemode = Title;


	//ダイレクトサウンドのデバイス作成
	DirectSound* pDs = DirectSound::GetInstance();
	pDs->Create(hWnd);

	WaveFile waveFile;			//音声ファイルデータ
	SoundBuffer TsoundBuffer;	//タイトル再生用バッファ
	SoundBuffer MsoundBuffer;	//メイン再生用バッファ
	SoundBuffer CsoundBuffer;	//クリア画面再生用バッファ
	SoundBuffer OsoundBuffer;	//ゲームオーバー画面再生用バッファ


	Player player;


	Camera camera;

	DirectInput*pDi = DirectInput::GetInstansce();
	pDi->Init(hWnd);

	if (pDi->KeyJustPressed(DIK_RETURN) && titleflag == true)
	{
		titleflag = false;
	}

	int Starttime = clock();
	const int Endtime = 30;

	RECT rect;
	SetRect(&rect, 200, 10, 0, 0);
	std::string str;
	D3DXCOLOR black = D3DCOLOR_ARGB(255, 255, 255, 255);



	//メインループ
	//メッセージループ

	MSG msg = {};

	//quitメッセージが出てくるまでループを繰り返す
	//quitメッセージは上記のウィンドウプロシージャから送信
	//送信の条件などはウィンドウプロシージャを確認
	while (msg.message != WM_QUIT)
	{
		//PeekMessage
		//メッセージキューの中にメッセージがあるかを調べて
		//msgの中に書き込みtrueを返す
		//メッセージがなければfalseを返す
		//PM_REMOVEを設定しているとメッセージの書き込みのあとに
		//メッセージキューから元のメッセージを消す

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//仮想キーメッセージを文字メッセージに変換し
			//それをメッセージキューにポストする
			TranslateMessage(&msg);

			//メッセージの割り当て
			//ウィンドウプロシージャでメッセージを処理
			DispatchMessage(&msg);
		}
		else
		{
			//メッセージキューにメッセージが無かったとき
			//こちらの処理
			//ここにゲーム処理を書き込んでいく
			pDi->Update();

			if (pDi->KeyJustPressed(DIK_A))
			{
				MessageBox(NULL,
					TEXT("キー入力確認"),
					TEXT("テストータイトル"),
					MB_OK);
			}


			switch (gamemode)
			{

			case Title:
				spritescene.Draw(tTitle);

				if (titlebgmFlag == false)
				{
					if (waveFile.Load("loop1.wav"))
					{
						TsoundBuffer.Create(waveFile);
						TsoundBuffer.Play(true);
					}
					else
					{
						int a = 0;
					}

					titlebgmFlag = true;
				}


				if (pDi->KeyJustPressed(DIK_RETURN))
				{

					Starttime = clock();
					titleflag = false;
					TsoundBuffer.Stop();

					TsoundBuffer.Release();
					titlebgmFlag = false;

					gamemode = GamePlay;
					map.Init();
					map.Split();
					map.MakeRoom();
					map.MakeTrail();
					map.DeleteTrail();
					player.Init();



					int x = 0;
					int y = 0;
					//map.SetPlayerInitPoint(x, y);
					map.SetGimmickPos(x, y);
					player.PlayerPos(x, y);
				}

				break;


			case GamePlay:

				if (mainbgmFlag == false)
				{
					if (waveFile.Load("whistle.wav"))
					{
						MsoundBuffer.Create(waveFile);
						MsoundBuffer.Play(true);
					}
					else
					{
						int a = 0;
					}

					mainbgmFlag = true;
				}

				//カメラの位置を調整
				camera.Move(0, 0, -10);

				//map.MapContoroll();
				player.PlayerContoroll(&map);
				map.scrollX = player.GetPlayerX() - 200;
				map.scrollY = player.GetPlayerY() - 150;

				player.PlayerItemCheck(&map);

				
				if (player.PlayerGoalCheck(&map))
				{
					MsoundBuffer.Stop();
					MsoundBuffer.Release();

					mainbgmFlag = false;
					//ゲームクリアの処理
					gamemode = Clear;
				}
				//ゲームオーバー処理
				
				if ((clock() - Starttime) / 1000 < Endtime)
				{
				}
				else
				{

					
					endflag = true;
					if (endflag == true)
					{
						MsoundBuffer.Stop();
						MsoundBuffer.Release();

						mainbgmFlag = false;

						gamemode = Over;
					}
				}
				
				

				break;

			case Clear:
				spritescene.Draw(tClear);

				if (clearbgmFlag == false)
				{
					if (waveFile.Load("fanfare.wav"))
					{
						CsoundBuffer.Create(waveFile);
						CsoundBuffer.Play(true);
					}
					else
					{
						int a = 0;
					}

					clearbgmFlag = true;
				}

				if (pDi->KeyJustPressed(DIK_RETURN))
				{
					CsoundBuffer.Stop();
					CsoundBuffer.Release();
					clearbgmFlag = false;
					gamemode = Title;
				}

				break;
			case Over:
				spritescene.Draw(tOver);
				if (clearbgmFlag == false)
				{
					if (waveFile.Load("loop2.wav"))
					{
						OsoundBuffer.Create(waveFile);
						OsoundBuffer.Play(true);
					}
					else
					{
						int a = 0;
					}

					clearbgmFlag = true;
				}

				if (pDi->KeyJustPressed(DIK_RETURN)&&endflag==true)
				{
					titleflag = false;
					endflag = false;
					OsoundBuffer.Stop();
					OsoundBuffer.Release();
					clearbgmFlag = false;
					gamemode = Title;
					Starttime = clock();
				}

				break;
			}

			//描画処理
			if (SUCCEEDED(d3d.BeginScene()))
			{
				//バックバッファのクリア
				d3d.ClearScreen();


				//レンダーステートの設定  αブレンド

				switch (gamemode)
				{

				case Title:
					spritescene.Draw(tTitle);

					break;


				case GamePlay:

					map.Draw();
					
					player.Draw(map.scrollX, map.scrollY);
					str = std::to_string(Endtime - (clock() - Starttime) / 1000);
					d3d.DrawString(&str, rect, black);

					break;

				case Clear:

					spritescene.Draw(tClear);

					break;

				case Over:

					spritescene.Draw(tOver);


				default:
					break;
				}







				//描画終了の合図
				d3d.EndScene();
				//バックバッファをフロントへ反映
				d3d.Present();
			}
		}
	}



	return 0;
}
