#include"DirectInput.h"

DirectInput* DirectInput::pInstance = nullptr;

DirectInput::DirectInput()
{
	pDInput = nullptr;

	pKeyDevice = nullptr;
	pMouseDevice = nullptr;
	initialized = false;

	//�z��ϐ��̏�����
	//���ׂă[��
	ZeroMemory(KeyInput, sizeof(int)*INPUT_BUFFER_SIZE);
	ZeroMemory(KeyInputPreview, sizeof(int)*INPUT_BUFFER_SIZE);

}

DirectInput::~DirectInput()
{
	//Release();
}

HRESULT DirectInput::Init(HWND hWnd)
{
	this->hWnd = hWnd;

	if (initialized == false)
	{
		//DirectInput�I�u�W�F�N�g�̍쐬
		HRESULT hresult
			= DirectInput8Create
			(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
				IID_IDirectInput8, (VOID**)&pDInput, NULL);

		if (FAILED(hresult))
		{
			return hresult;
		}

		//�I�u�W�F�N�g���ł����̂ŃL�[�{�[�h�p�̃f�o�C�X��������
		hresult = InitKey();

		if (FAILED(hresult))
		{
			return hresult;
		}

		//���ׂĂ̏��������I��
		//�������ς݂Ƃ���
		initialized = true;
	}
	//����������
	return S_OK;
}

HRESULT DirectInput::InitKey()
{
	HRESULT hresult;


	//CreateDevice�̑���������肽���f�o�C�X�̃^�C�v������
	//��������������f�o�C�X�̕ۑ��悪����|�C���^
	//�^�C�v�ɂ�����炸�������̌^��
	//LPDIRECTINPUTDEVICE8*�@�ł��邱�Ƃɒ���
	hresult = pDInput
		->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL);

	if (FAILED(hresult))
	{
		return hresult;
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�@�L�[�{�[�h��I��
	hresult = pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hresult))
	{
		return hresult;
	}

	//�������[�h�̐ݒ�
	//OS��ق��̃A�v���P�[�V�����Ƃ̃f�o�C�X���L�̂��߂̐ݒ�
	//�f�t�H���g�ݒ�
	hresult = pKeyDevice->SetCooperativeLevel
	(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	if (FAILED(hresult))
	{
		return hresult;
	}

	//���̓f�o�C�X�ւ̃A�N�Z�X�����擾
	pKeyDevice->Acquire();

	return S_OK;
}

HRESULT DirectInput::Update()
{
	//���������ς�ł��Ȃ���������s����̂ɖ�肪���낢��Əo��̂�
	//�֐��������ɒ��f
	if (initialized == false)
	{
		return S_FALSE;
	}

	//�L�[�{�[�h�̏�Ԃ��擾����
	//�����o�ϐ��̍X�V

	//�A�N�Z�X���擾
	HRESULT hresult = pKeyDevice->Acquire();

	//S_FALSE�ȊO�̎��s�͒ʂ��Ȃ�
	if (hresult == DI_OK || hresult == S_FALSE)
	{
		//�O��̃t���[���̃L�[����preview�̂ق��ɃR�s�[
		memcpy(KeyInputPreview,
			KeyInput,
			sizeof(int)*INPUT_BUFFER_SIZE);

		//��ԁ@�܂��f�o�C�X���猻�݂�ON OFF�����擾
		//t tmporaly �ꎞ��
		//work ��Ɨp��
		BYTE tKeyInputWork[INPUT_BUFFER_SIZE];

		//�f�o�C�X����L�[���(On Off)�̎擾
		pKeyDevice->
			GetDeviceState(sizeof(BYTE)*INPUT_BUFFER_SIZE,
				&tKeyInputWork);

		//�L�[��OnOff����
		//���t���[�������ꑱ���Ă��邩�Ƃ������ɉ��H
		for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
		{
			if (tKeyInputWork[i])//�L�[��������Ă���
			{
				if (KeyInput[i] < 2147483647)
				{
					//�����ꑱ���Ă���t���[���������Z
					KeyInput[i] ++;;
				}
			}
			else
			{
				//������Ă��Ȃ��ꍇ�́@�A���t���[���������O�ɂ���
				KeyInput[i] = 0;
			}
		}
	}
	return S_OK;
}

//���݉�����Ă��邩
bool DirectInput::KeyState(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		//������Ă����Ԃ��O�Ȃ̂łO���傫���Ɖ�����Ă��邱�Ƃ��킩��
		return KeyInput[code] > 0;
	}

	//�͈͊O��false
	return false;
}

//���̃t���[�������̃L�[�̉����ꂽ�u�Ԃł��邩
bool DirectInput::KeyJustPressed(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		//0����P�ɐ؂�ւ�����u�Ԃ������ꂽ�u�Ԃ������Ă���
		return KeyInput[code] == 1;
	}

	//�͈͊O��false
	return false;
}

//���̃t���[�����L�[�̗����ꂽ�u�Ԃ�
bool DirectInput::KeyJustReleased(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		//���݂�0������
		//1�t���[���O�͉�����Ă���
		return (KeyInput[code] == 0 &&
			KeyInputPreview[code] > 0);
	}

	//�͈͊O��false
	return false;
}

//�����ꑱ���Ă���t���[������Ԃ�
int DirectInput::KeyCount(int code)
{
	if (code >= 0 && code < INPUT_BUFFER_SIZE)
	{
		return KeyInput[code];
	}

	//�͈͊O��false
	return false;
}