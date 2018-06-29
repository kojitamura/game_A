#include "DirectSound.h"
#include "Wave.h"

#include "SoundBuffer.h"

//�R���X�g���N�^
SoundBuffer::SoundBuffer()
{
	pBuffer = NULL;
}

//�f�X�g���N�^
SoundBuffer::~SoundBuffer()
{
	Release();
}

//�������
void SoundBuffer::Release()
{
	//�o�b�t�@�Ƀf�[�^������Ȃ�
	if (pBuffer != NULL)
	{
		//�J�������̑O�ɍĐ����~����
		Stop();

		pBuffer->Release();
		pBuffer = NULL;
	}
}

bool SoundBuffer::Create(WaveFile& waveFile)
{
	//�o�b�t�@�쐬�p�̐ݒ�@�ϐ�
	//desc : description
	DSBUFFERDESC desc = {};

	//�`�����l�����ŕ���
	//���m���� 1�`�����l��
	//�X�e���I 2�`�����l��

	switch (waveFile.waveFormat.nChannels)
	{
	case 1: //���m����
		desc.dwFlags =
			DSBCAPS_CTRL3D |
			DSBCAPS_CTRLVOLUME |
			DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 |
			DSBCAPS_CTRLPOSITIONNOTIFY |
			DSBCAPS_STATIC;

		desc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;

		break;

	default://�X�e���I //3�`�����l���ȏ�̏ꍇ������			
		if (waveFile.waveFormat.nChannels >= 2)
		{
			desc.dwFlags =
				//DSBCAPS_CTRL3D |//���m�����̐ݒ肩�甲��
				DSBCAPS_CTRLVOLUME |
				DSBCAPS_CTRLFREQUENCY |
				DSBCAPS_GETCURRENTPOSITION2 |
				DSBCAPS_CTRLPOSITIONNOTIFY |
				DSBCAPS_STATIC |
				DSBCAPS_CTRLPAN;
			//���m�����̃t���O�ݒ肩��Ō�̈�s������������

			desc.guid3DAlgorithm = GUID_NULL;
		}

		break;
	}

	//�\���̂̃T�C�Y
	desc.dwSize = sizeof(DSBUFFERDESC);
	//�g�`�f�[�^�̃T�C�Y
	desc.dwBufferBytes = waveFile.dataSize;
	//wave�t�@�C���t�H�[�}�b�g
	desc.lpwfxFormat = &(waveFile.waveFormat);

	//�ݒ�I���

	//�f�o�C�X�̎擾
	DirectSound* pDirectSound = DirectSound::GetInstance();

	//�T�E���h�o�b�t�@
	//�����o�ϐ��̕��̃T�E���h�o�b�t�@�ƌ^���Ⴄ
	//�^���Ƃ��Ă�8���t���Ă��邩���Ă��Ȃ���
	IDirectSoundBuffer* pBuffer_work = NULL;

	//�o�b�t�@�̍쐬��DirectSound�N���X�ɂ���Ă��炤
	//waveFile.dataSize�����܂�悤�ȃf�[�^�̈�̊m��
	if (FAILED(pDirectSound->CreateSoundBuffer(&desc, &pBuffer_work)))
	{
		return false;
		//�n���ꂽwave�f�[�^�ɖ�肪����
		//����������Ă��Ȃ�
		//���[�h���s
		//�̉\��
	}

	//�T�E���h�o�b�t�@�̕ϊ�
	//IDirectSoundBuffer*����IDirectSoundBuffer8�ɕϊ�
	//�������ŕϊ���̌^���w��
	//�������ŕϊ���̃f�[�^�������Ƃ�|�C���^
	//�ϊ���̌^���w�肷�鐫����@�������̌^���s��
	//�Ȃ̂�void**�ɕϊ����ċ����Ɉ����ɓn��
	pBuffer_work->
		QueryInterface
		(IID_IDirectSoundBuffer8, (void**)&pBuffer);

	//�ϊ��ŗ�����ϊ����͗p�ς�
	pBuffer_work->Release();

	//�f�[�^�̏�������
	unsigned char * block1 = nullptr;
	unsigned char * block2 = nullptr;
	unsigned long blockSize1 = 0;
	unsigned long blockSize2 = 0;

	//�o�b�t�@�����b�N���ăf�[�^����������
	pBuffer->Lock(
		0, waveFile.dataSize,
		(void**)&block1, &blockSize1,
		(void**)&block2, &blockSize2,
		DSBLOCK_ENTIREBUFFER);

	//�o�b�t�@�ɉ��f�[�^�R�s�[
	memcpy(block1, waveFile.pWaveData, waveFile.dataSize);

	//���b�N����
	pBuffer->Unlock(block1, blockSize1, block2, 0);

	return true;

}

//�Đ��J�n
void SoundBuffer::Play(bool loop)
{
	if (pBuffer != NULL)
	{
		DWORD loopFlag = (loop ? DSBPLAY_LOOPING : 0);

		//������ reserved �\��ς� 0�łȂ���΂Ȃ�Ȃ�
		//������ priority �D�揇��
		//�@�@�@�@�@�@�@�@�@�n�[�h�E�F�A�~�L�V���O���\�[�X
		//					�����蓖�Ă�ۂɎg���B
		//					�o�b�t�@���쐬����ۂ�
		//					DSBCAPS_LOCDEFER ���t���O�Ƃ���
		//					�ݒ肳��ĂȂ��ꍇ�� 
		//					0�łȂ���΂Ȃ�Ȃ�
		pBuffer->Play(0, 0, loopFlag);
	}
}

//�Đ���~
void SoundBuffer::Stop()
{
	if (pBuffer != NULL)
	{
		pBuffer->Stop();
	}
}