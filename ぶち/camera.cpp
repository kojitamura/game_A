#include "Camera.h"

Camera::Camera()
{
	//�����@���_
	eyePoint = D3DXVECTOR3(0, 0, 0);

	//�O���[�o�����W�ł̏����
	upVec = D3DXVECTOR3(0, 1, 0);//y�� �v���X

								 //�J���������_�@eyePoint�𒆐S�ɂ������΍��W
								 //�����l��z�v���X���� �Ő����������悤�ɐݒ�
	relLookAtPoint = D3DXVECTOR3(0, 0, 1);

	//�����_�@�O���[�o�����W
	lookAtPoint = eyePoint + relLookAtPoint;

	//�p���p�̌��x��ݒ�@�����l��+-36�x
	pitchMax = (3.1415f*(1.0f / 5.0f));
	pitchMin = -(3.1415f *(1.0f / 5.0f));
}


Camera::~Camera()
{
	//����new �����Ă��Ȃ����ߋ�
}

//�J�����̌������l�����Ȃ��ړ�
//�O���[�o����Ԃł̂��ꂼ��̎��̕ω��ʂ��w��
void Camera::Move(float x, float y, float z)
{
	//�J�������_�@�ړ���
	D3DXVECTOR3 delta(x, y, z);
	//���_�ړ�
	eyePoint += delta;
}

//�J�����̉�] (�ω��ʎw��)
// yaw   Y�������ɂ�����]�@�@
// Pitch �p���p�@�㉺�̊p�x�@
void Camera::Rotate(float radYaw, float radPitch)
{
	//�܂��͌��݂� Yaw��Pitch�̏�Ԃ𒲂ׂ�
	double x = relLookAtPoint.x;
	double y = relLookAtPoint.y;
	double z = relLookAtPoint.z;

	//z,x ����yaw��]�̊p�x�����߂�@(���W�A��)
	//atan2 �A�[�N�^���W�F���g
	double first_radYaw = atan2(z, x);

	//pitch��]�����߂�

	//relLookAtPoint����y�̗v�f����菜�����x�N�g���̒���
	//�O�����̒藝�Ōv�Z
	//sqrt SquareRoot�̗��@������
	double pitchX = sqrt(x*x + z*z);
	//pitch�̊p�x�v�Z
	double first_radPitch = atan2(y, pitchX);

	//�V����relLookAt�̊e�v�f���v�Z
	//�܂�x z����
	//�O�p�֐��̉��@�藝�𗘗p

	//�T�C���̉��@�藝�𗘗p
	double resultZ = sin(first_radYaw)*cos(radYaw)
		+ cos(first_radYaw)*sin(radYaw);

	//�R�T�C���̉��@�藝�𗘗p
	double resultX = cos(first_radYaw)* cos(radYaw)
		- sin(first_radYaw)*sin(radYaw);

	//�s�b�`�@���p�p���v�Z
	//�p�x�ɏ��������ݒ�
	double addRadPitch = radPitch;

	//180*(1/5) 36�x�@�𒴂��Ă�����
	//�v���X�����̐���
	if (first_radPitch + addRadPitch >= pitchMax)
	{
		addRadPitch = pitchMax - first_radPitch;
		//��]��ɐ����̊p�x�ƈ�v����܂�
		//�ω��ʂ����炷		
	}
	//�}�C�i�X�����̐���
	if (addRadPitch + first_radPitch <= pitchMin)
	{
		addRadPitch = pitchMin - first_radPitch;
	}

	//�V����relLookAt�̊e�v�f���v�Z
	//y���v�Z

	//�T�C���̉��@�藝�𗘗p
	double resultY = sin(first_radPitch)*cos(addRadPitch)
		+ cos(first_radPitch)*sin(addRadPitch);

	//resultX resultY�݂̂̃x�N�g���̒���
	//�R�T�C���̉��@�藝�𗘗p
	double resultPitchX = cos(first_radPitch)*cos(addRadPitch)
		- sin(first_radPitch)*sin(addRadPitch);

	//���� resultX resultZ�@���킹�Ē�����1�Ȃ̂�
	//PitchX�ŏk��
	//(resultX resultY resultZ 
	//���킹�Ē�����1�̃x�N�g���ɂȂ�悤�ɂ���) 
	resultX *= resultPitchX;
	resultZ *= resultPitchX;


	relLookAtPoint = D3DXVECTOR3(
		static_cast<float>(resultX),
		static_cast<float>(resultY),
		static_cast<float>(resultZ));

	//�x�N�g���̕W�����@�O�̂��߂�
	D3DXVec3Normalize(&relLookAtPoint, &relLookAtPoint);

}

//���݂̃����o�̒l����r���[�s����쐬���Ԃ�
D3DXMATRIXA16 Camera::CreateViewMatrix()
{
	//�����_�@�O���[�o�����W
	lookAtPoint = eyePoint + relLookAtPoint;

	D3DXMATRIXA16 view;

	//�r���[�s��쐬
	D3DXMatrixLookAtLH(&view, &eyePoint, &lookAtPoint, &upVec);

	return view;
}

void Camera::SetPosition(float x, float y, float z)
{
	eyePoint = D3DXVECTOR3(x, y, z);
}

void Camera::SetRotation(float yaw, float pitch)
{
	//�s�b�`�̐����ɂ������Ă��邩���`�F�b�N
	//�v���X����
	if (pitch > pitchMax)
	{
		pitch = pitchMax;
	}
	//�}�C�i�X����
	if (pitch < pitchMin)
	{
		pitch = pitchMin;
	}

	//�e���̗v�f���v�Z
	double y = sin(pitch);

	//x z�݂̂Ńx�N�g����������ꍇ�̒���
	double pitchX = cos(pitch);

	//yaw��0����x�̃v���X����������
	double x = cos(yaw)*pitchX;
	double z = sin(yaw)*pitchX;

	relLookAtPoint = D3DXVECTOR3(
		static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(z));
}

//���݂̌�������ɂ����ړ��@���ʂ⍶�E�Ɉړ������ہ@�㉺�̈ړ����N����\��������
void  Camera::MoveBasedRotation(float forward, float right, float up)
{
	//���ʂ̕����͒����_�̕����ƈꏏ
	D3DXVECTOR3 forwardVec = relLookAtPoint;

	//������ƉE�������v�Z

	//�܂��͌��݂� Yaw��Pitch�̏�Ԃ𒲂ׂ�
	double x = relLookAtPoint.x;
	double y = relLookAtPoint.y;
	double z = relLookAtPoint.z;

	//z,x ����yaw��]�̊p�x�����߂�@(���W�A��)
	//atan2 �A�[�N�^���W�F���g
	double first_radYaw = atan2(z, x);

	D3DXVECTOR3 rightVec =
		D3DXVECTOR3(cos(first_radYaw - (3.1415f*0.5f)),//���ʕ�������90�x�����Z�ŉE����
			0,//roll��]�������̂ō��E��y���̕ω��͂Ȃ�
			sin(first_radYaw - (3.1415f*0.5f)));

	//�����
	double pitchX = sqrt(x*x + z*z);
	double first_radPitch = atan2(y, pitchX);//���݂̃s�b�`�̊p�x
	double cosPitch = cos(first_radPitch + 3.1415f*0.5);//���ʕ�������90�x�����Z�ŏ����

	D3DXVECTOR3 upVector =
		D3DXVECTOR3(x*cosPitch,
			sin(first_radPitch + 3.1415f*0.5),
			z*cosPitch);

	eyePoint += upVector*up + forwardVec*forward + rightVec*right;
}

//���݂̌�������ɂ����ړ� (���ʓI) ���ʂ⍶�E�Ɉړ������ۂɏ㉺�̈ړ����N���Ȃ�
//�㉺�ړ��͌Œ��y���́{�|����
void  Camera::MoveBasedRotation_Flatten(float forward, float right, float up)
{
	double x = relLookAtPoint.x;
	double y = relLookAtPoint.y;
	double z = relLookAtPoint.z;

	double first_radYaw = atan2(z, x);

	D3DXVECTOR3 forwardVec =
		D3DXVECTOR3(cos(first_radYaw),
			0,
			sin(first_radYaw));

	D3DXVECTOR3 rightVec =
		D3DXVECTOR3(cos(first_radYaw - (3.1415f*0.5f)),//���ʕ�������90�x�����Z�ŉE
			0,
			sin(first_radYaw - (3.1415f*0.5f)));

	eyePoint += upVec*up + forwardVec*forward + rightVec*right;

}