#pragma once

class Object2DAttribute
{
public:
	//�ڂ�����Dx���C�u�����u�����	int DrawBillboard3D( VECTOR Pos, float cx, float cy, float Size, float Angle, int GrHandle, int TransFlag ) ;�@�����Ă�


	float _cx, _cy;	//�`�悷��摜�̒��S���W(0.0f �` 1.0f)
	float _size;	//�`�悷��摜�̃T�C�Y
	float _angle;	//�`�悷��摜�̉�]�p�x(���W�A���P��)
	int _handle;	// �`�悷��摜�̃n���h��
	bool _transFlag; //�摜�̓����x��L���ɂ��邩�ǂ����i TRUE�F�L���@FALSE�F���� �j
	
	Object2DAttribute();
	~Object2DAttribute();
};

