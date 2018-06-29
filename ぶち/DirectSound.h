#pragma once

#define DIRECTSOUND_VERSION 0x800

#pragma comment (lib,"dsound.lib")

#include <dsound.h>

class DirectSound
{
private:
	//�V���O���g���ɂ���
	static DirectSound* pInstance;

	//�T�E���h�f�o�C�X
	IDirectSound8* pDirectSound8;

	void Release();

	//�V���O���g���ɂ��邽�߂ɃN���X�O������s�ł��Ȃ��悤�ɂ���
	DirectSound();//�R���X�g���N�^
	~DirectSound();
	void operator=(const DirectSound& obj) {}//������Z
	DirectSound(const DirectSound& obj) {}	//�R�s�[�R���X�g���N�^
public:
	//�C���X�^���X�̎擾
	static DirectSound* GetInstance()
	{
		if (pInstance == NULL)
		{
			pInstance = new DirectSound();
		}
		return pInstance;
	}

	//�f�o�C�X�̍쐬
	bool Create(HWND hWnd);

	//�T�E���h�o�b�t�@�[�̍쐬
	HRESULT CreateSoundBuffer
	(DSBUFFERDESC * pDesc, IDirectSoundBuffer** ppBuffer);
};