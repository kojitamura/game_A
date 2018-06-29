#define _CRT_SECURE_NO_WARNINGS
//fopen�ł̌x�����Ȃ����@
//���̌x��������ƃR���p�C���ł��Ȃ��Ȃ�


#include "Wave.h"

using namespace std;

//�R���X�g���N�^
WaveFile::WaveFile()
{
	//WaveFormat�̒��g�S�Ă�0�ɏ�����
	memset(&waveFormat, 0, sizeof(WAVEFORMATEX));

	pWaveData = nullptr;
	dataSize = 0;

}

//�f�X�g���N�^
WaveFile::~WaveFile()
{
	Release();
}

//������� �����o�ϐ����R���X�g���N�^���s���Ɠ�����Ԃɖ߂�
void WaveFile::Release()
{
	if (pWaveData)//���[�h�ς݂�
	{
		delete[] pWaveData;
		pWaveData = nullptr;
	}
	memset(&waveFormat, 0, sizeof(WAVEFORMATEX));
	dataSize = 0;
}

bool WaveFile::Load(TCHAR *filepath)
{
	//.wav�@�`���̃f�[�^�̕ۑ��̂��ꂩ��
	//3�̃`�����N�ɕ�����Ă���
	//�`�����N�@�f�[�^����؂�����

	//RIFF�w�b�_�[�`�����N�@�t�@�C���̎�ނ�\���Ă���
	//�t�H�[�}�b�g�`�����N�@�����f�[�^�̋L�^�̂����
	//�f�[�^�`�����N�@�@�@�@����(�g�`)�f�[�^

	FILE* fp = nullptr;

	//�t�@�C���̃I�[�v��
	//�o�C�i���`���ł̓ǂݍ��݃��[�h�ŊJ��
	fp = _tfopen(filepath, _T("rb"));	//�@r read
										//  b binary

	if (fp == nullptr)
	{
		//�t�@�C���I�[�v���Ɏ��s
		return false;
	}

	//�t�@�C���̃I�[�v���ɐ���

	//�`�����N�Ɋւ����������ϐ�
	char chunkID[5]{};
	char type[5]{};
	unsigned int chunkSize = 0;

	//RIFF�w�b�_�[�`�����N��ǂݍ���

	//RIFF�w�b�_�[�̍\��-----------------------------------
	//riff 4byte "RIFF"��4����
	//size 4byte ���t�@�C���T�C�Y-8(byte �P��)
	//           �����ꂽ8��riff��size�̗e�ʕ�
	//           (�܂� size �ȍ~�̎c��̃f�[�^��)
	//type 4byte "WAVE"��4����(�����f�[�^�ł��邱�Ƃ�����)
	//-----------------------------------------------------

	//riff =="RIFF" type=="WAVE"
	//�̏ꍇ�̂݁A���̌�̓ǂݍ��݂��s��

	//fread�֐�
	//chunkID�̃A�h���X��fp����ǂݏo�����f�[�^���R�s�[����
	//�f�[�^��char4��
	//1 (����)//�z��ϐ��ɂ܂Ƃ߂ĕ������f�[�^��ǂݍ��݂����Ƃ��ɗ��p
	fread(chunkID, sizeof(char) * 4, 1, fp);

	//fread�s���� �ǂݏo������ fp�̎���̓ǂݏo���J�n�ʒu��
	//�ǂݏo�����f�[�^�ʕ��������ւ����

	//�t�@�C���f�[�^�ʂ̓ǂݍ���
	//�t�@�C���̑��e�ʎ��͈̂ȍ~���p���Ȃ���
	//fp�̓ǂݍ��݊J�n�n�_�����炷���߂Ɏ��s
	fread(&chunkSize, sizeof(unsigned int), 1, fp);
	//type�̓ǂݏo��
	fread(type, sizeof(char) * 4, 1, fp);

	//������̓�����r�����₷���悤��
	//string�^�ɕ�������R�s�[����
	string chunkID_st = chunkID;
	string type_st = type;

	//������WAVE�t�@�C�����ǂ����𒲂ׂ�
	if (!(chunkID_st == "RIFF" && type_st == "WAVE"))
	{
		return false;//��������O��Ă���̂Ŏ��s
	}

	//���ꂼ��̃`�����N��ǂݏo������
	bool fmtChunk = false;
	bool dataChunk = false;

	//�`�����N���Ƃ̓ǂݏo��
	//�t�H�[�}�b�g�`�����N�ƃf�[�^�`�����N��
	//�����ǂݏo�����烋�[�v���甲����
	while (!(fmtChunk && dataChunk))
	{
		//�ǂ̃`�����N��chunkID��chunk�̗e�ʂ���
		//�f�[�^���X�^�[�g����
		fread(chunkID, sizeof(char) * 4, 1, fp);
		fread(&chunkSize, sizeof(unsigned int), 1, fp);
		//�`�����N�T�C�Y�̓`�����N�S�̂���-8
		//(id��size�̗e�ʕ�)���ꂽ����

		chunkID_st = chunkID;

		if (chunkID_st == "fmt ")//fmt�̌��ɃX�y�[�X
		{
			//�ǂݍ������Ƃ��Ă���̂��t�H�[�}�b�g�`�����N

			//�t�H�[�}�b�g�`�����N-------------------------------------
			//id				4byte�@�`�����N���ʎq	
			//size				4byte�@id��size�������`�����N�T�C�Y
			//format			2byte�@�g�`�f�[�^�̃t�H�[�}�b�g
			//channels			2byte�@�`�����l����(���m����or�X�e���I)
			//samplerate		4byte�@�T���v�����O���g��
			//bytepersec		4byte�@���σf�[�^�̊���
			//blockalign		2byte�@�f�[�^�̃u���b�N�T�C�Y
			//bitswidth			2byte  1�T���v��������̃r�b�g��
			//extended_size		2byte�@�g���f�[�^�̃T�C�Y
			//extended			Nbyte�@�g���f�[�^
			//----------------------------------------------------------
			//�����̃f�[�^���܂Ƃ߂�WAVEFORMATEX�̕ϐ��ɓǂݍ���

			if (chunkSize >= sizeof(WAVEFORMATEX))
			{
				//�`�����N�T�C�Y��WAVEFORMATEX���傫���ꍇ
				//�����炭�g���f�[�^������ꍇ

				//���̏ꍇ�͊g�����𖳎�

				fread(&waveFormat, sizeof(WAVEFORMATEX), 1, fp);

				//�`�����N�̎c��̗̈�̑傫�����v�Z
				int diff = chunkSize - sizeof(WAVEFORMATEX);
				//diff difference ��

				//���̃`�����N�̐擪�܂ŃV�[�N
				//(�ǂݔ�΂�)
				fseek(fp, diff, SEEK_CUR);//CUR�͌��݂̈ʒu����

			}
			else
			{
				//�`�����N�T�C�Y��WAVEFORMATEX�̂��������ɖ����Ȃ��ꍇ
				//�`�����N�̏I���܂œǂ�
				//��肠�������镪����
				fread(&waveFormat, chunkSize, 1, fp);

			}

			//�t�H�[�}�b�g�`�����N�ǂݍ��ݍς݃t���O
			fmtChunk = true;
		}
		else if (chunkID_st == "data")//�f�[�^�`�����N
		{
			//�f�[�^�`�����N----------------------------------------
			//id				4byte �`�����N���ʎq
			//size				4byte id��size�������`�����N�̃T�C�Y
			//					      (���̂܂ܔg�`�f�[�^�̃f�[�^��)
			//waveformatData	Nbyte �g�`�f�[�^
			//-------------------------------------------------------

			//�f�[�^�̈�̊m��
			dataSize = chunkSize;
			pWaveData = new byte[dataSize];//���I�Ƀf�[�^�m��

										   //�f�[�^�̓ǂݍ���
										   //fread�̖߂�l�͐������ǂ߂�����
										   //dataSize�����ǂ�
			unsigned long readCount
				= fread(pWaveData, sizeof(byte), dataSize, fp);

			if (readCount != dataSize)
			{
				//�S�ēǂ߂Ȃ�����
				fclose(fp);//�t�@�C������

				Release();//�f�[�^���Z�b�g����

				return false;//���s
			}

			dataChunk = true;
		}
		else
		{
			//fmt�ł�data�ł��Ȃ��`�����N�͓ǂݔ�΂�
			//(JUNK�Ƃ�)

			fseek(fp, chunkSize, SEEK_CUR);
		}
	}
	fclose(fp);
	return true;//����
}


bool WaveFile::Load(string filepath)
{
	const TCHAR* tp = _T(filepath.c_str());

	return Load(tp);
}