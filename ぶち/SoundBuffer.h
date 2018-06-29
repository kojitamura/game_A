#pragma once


#pragma comment(lib,"dsound.lib")

#include <dsound.h>

class WaveFile;

class SoundBuffer
{
private:
	//サウンドバッファ
	IDirectSoundBuffer8 *pBuffer;

public:
	//コンストラクタ
	SoundBuffer();
	//デストラクタ
	~SoundBuffer();

	bool Create(WaveFile& waveFile);

	//再生　
	void Play(bool loop);
	//停止
	void Stop();

	//解放
	void Release();

};