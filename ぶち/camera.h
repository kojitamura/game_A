#pragma once

#include "direct3D.h"

//�J����������s���N���X
//�J�����̍��W�ƒ����_���R���g���[������
//�r���[�s����o��

class Camera
{
private:
	D3DXVECTOR3 eyePoint;
	D3DXVECTOR3 relLookAtPoint;//�����_�@eyePoint����̍��W����
							   //���_���ړ����Ă������_�Ǝ��_��
							   //�ʒu�֌W��ς��Ȃ��悤�ɂ���

	D3DXVECTOR3 lookAtPoint;   //�O���[�o�����W�ł̒����_
							   //���΍��W�ł̑�����s���̂�
							   //eyePoint + relLookAtPoint;
							   //������

	D3DXVECTOR3 upVec;		   //�O���[�o����ԁ@�����

	float pitchMax;
	float pitchMin;

public:
	Camera();
	~Camera();

	//�ʒu�̈ړ� �����̓J�����̍��W�ړ���
	void Move(float x, float y, float z);

	//���݂̌�������ɂ����ړ��@���ʂ⍶�E�Ɉړ������ہ@�㉺�̈ړ����N����\��������
	void MoveBasedRotation(float forward, float right, float up);
	//���݂̌�������ɂ����ړ� (���ʓI) ���ʂ⍶�E�Ɉړ������ۂɏ㉺�̈ړ����N���Ȃ�
	void MoveBasedRotation_Flatten(float forward, float right, float up = 0);

	//��]		 yaw   Y�������ɂ�����]�@�@
	//           Pitch �p���p�@�㉺�̊p�x�@���S�ɐ�����0
	void Rotate(float radYaw, float radPitch);

	//�ʒu�̎w��@�ړ��̍����łȂ��@
	//�ړ��������O���[�o�����W�̈ʒu�𒼐ڎw��
	void SetPosition(float x, float y, float z);

	//��]�̎w��
	//��]�̕ω��ʂłȂ���]�̒l�𒼐ڎw��
	void SetRotation(float radYaw, float radPitch);

	//���݂̃J�����̏�Ԃɍ��킹��
	//�r���[�s��̏o��
	D3DXMATRIXA16 CreateViewMatrix();
};
