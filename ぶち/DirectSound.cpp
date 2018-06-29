#include "DirectSound.h"

//�ÓI�����o�ϐ��̏�����
DirectSound* DirectSound::pInstance = nullptr;

//�R���X�g���N�^
DirectSound::DirectSound()
{
	pDirectSound8 = NULL;
}

//�f�X�g���N�^
DirectSound::~DirectSound()
{
	Release();
}

//������� �R���X�g���N�^���s���Ɠ�����Ԃ֖߂�
void DirectSound::Release()
{
	if (pDirectSound8 != NULL)
	{
		pDirectSound8->Release();
		pDirectSound8 = NULL;
	}
}

bool DirectSound::Create(HWND hWnd)
{
	if (FAILED(DirectSoundCreate8(NULL, &pDirectSound8, NULL)))
	{
		//���s
		Release();
		return false;
	}

	//�������x���̐ݒ�
	//�܂�����炷�E�B���h�E�̎w��
	if (FAILED(pDirectSound8->
		SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		//PRIORITY �D�� 
		//���̃A�v���P�[�V�����̃T�E���h�Ƃ������ɍĐ��ł���
		//EXCUSIVE �r�� 
		//���̃A�v���P�[�V�����̃T�E���h�𖳉��ɂ���悤�ȂƂ��Ɏg��
	{
		//���s
		Release();
		return false;
	}

	return true;
}

HRESULT DirectSound::CreateSoundBuffer
(DSBUFFERDESC*pDesc, IDirectSoundBuffer** ppBuffer)
{
	if (pDirectSound8 == NULL)
	{
		//�f�o�C�X�̍쐬������Ă��Ȃ�����
		//�o�b�t�@�̍쐬���ł��Ȃ�
		return E_FAIL;
	}
	//�T�E���h�o�b�t�@�̍쐬
	HRESULT hr =
		pDirectSound8->
		CreateSoundBuffer(pDesc, ppBuffer, NULL);

	return hr;
}