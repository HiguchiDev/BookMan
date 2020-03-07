#include "Key.h"
#include "Dxlib.h"
#include "MessgeBox.h"

Key::Key()
{
	
}


Key::~Key()
{
}
void Key::update(){
	// �L�[�̓��͏�Ԃ��X�V����
		char tmpKey[256];				// ���݂̃L�[�̓��͏�Ԃ��i�[����
		GetHitKeyStateAll(tmpKey);		// �S�ẴL�[�̓��͏�Ԃ𓾂�
		for (int i = 0; i<256; i++){
			if (tmpKey[i] != 0){		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
				key[i]++;				// ���Z
			}
			else {			            // ������Ă��Ȃ����
				key[i] = 0;				// 0�ɂ���
			}
		}
}

int Key::getHitKey()
{


	for (int i = 0; i < 256; i++){
		if (key[i] == 1){
			return i;
		}
	}

	return NULL;
}

int Key::getHitFlame(int keyNum){
	if ((MessgeBox::getInstance()->isDisplay() && keyNum == KEY_INPUT_SPACE) || !MessgeBox::getInstance()->isDisplay()){
		return key[keyNum];
	}
	else{
		return 0;
	}
}
bool Key::isHit(int keyNum){
	if (key[keyNum] >= 1){
		return true;
	}else{
		return false;
	}
}

std::unique_ptr<Key> Key::_instance;

std::unique_ptr<Key>& Key::getInstance()
{
	if (_instance.get() == nullptr){
		_instance = std::make_unique<Key>();
	}
	return _instance;
}