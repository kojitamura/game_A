#pragma once

//using namespace std;//string���g�p����ۂ� std:: ���ȗ��ł��邪
//�w�b�_�[����using namespace ���g�p����̂�
//���܂�ǂ��Ȃ��̂Ł@�g�p���Ȃ�
//�ǂ��Ȃ����R�� ���̃w�b�_�[��
//�ǂݍ��񂾃t�@�C���S�ĂŗL���ɂȂ邩��

#pragma comment (lib,"dsound.lib")//�_�C���N�g�T�E���h
#include <dsound.h>//�_�C���N�g�T�E���h

#include <tchar.h>
#include <string>

//1��Wave�`���̉����f�[�^�t�@�C����ǂݍ���ŕێ�����N���X
class WaveFile
{
	//SoundBuffer�N���X���炱�̃N���X��private�ȃ����o��
	//�A�N�Z�X�ł���悤�ɂ���
	friend class SoundBuffer;

private:
	//�ǂݍ��񂾁i�ǂݍ������Ƃ��Ă���j
	//Wave�t�@�C���̋L�^�̂����
	WAVEFORMATEX waveFormat;

	int dataSize;	//�g�`�f�[�^�̃f�[�^��
	byte* pWaveData;//�g�`�f�[�^�i�����f�[�^�j

public:
	//�R���X�g���N�^
	WaveFile();
	//�f�X�g���N�^
	~WaveFile();

	//�������
	void Release();

	//�t�@�C�����[�h
	bool Load(TCHAR* filePath);
	bool Load(std::string filePath);

};
