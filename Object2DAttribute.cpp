#include "Object2DAttribute.h"


Object2DAttribute::Object2DAttribute()
{
	_cx = 0.0f;
	_cy = 0.0f;	//�`�悷��摜�̒��S���W(0.0f �` 1.0f)
	_size = 0.0f;	//�`�悷��摜�̃T�C�Y
	_angle = 0.0f;	//�`�悷��摜�̉�]�p�x(���W�A���P��)
	_handle = -1;	// �`�悷��摜�̃n���h��
	_transFlag = false; //�摜�̓����x��
}


Object2DAttribute::~Object2DAttribute()
{
}
