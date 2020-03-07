#include "GameApp.h"
#include "DxLib.h"
#include "Player.h"
#include <vector>
#include "Obstacle.h"
#include "Position.h"
#include "Floor.h"
#include "FieldLength.h"
#include "HitBox.h"
#include "TurnController.h"
#include "FloorOfTheDungeon.h"
#include "Enemy.h"
#include "LoadScreen.h"
#include "Object_3D_Duplicate.h"
#include "Stage.h"
#include "Object_3D.h"
#include "Object_3D_Duplicate.h"
#include "EffekseerForDXLib.h"
#include "StatesPoint.h"
#include "PauseMenu.h"
#include "DataRead.h"
#include "PlayerDatas.h"
#include "DamageDisplay.h"
#include "ItemListScreen.h"
#include "PlayerItems.h"
#include "SceneUpdater.h"
#include "Key.h"
#include "MessgeBox.h"
#include "EffectUpdater.h"
#include "HitBoxUpdater.h"
#include "HandleCreater.h"

GameApp::GameApp()
{
}


GameApp::~GameApp()
{

}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	// DirectX9���g�p����悤�ɂ���B
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	//SetUseDirect3DVersion(DX_DIRECT3D_9EX);
	// DX���C�u�����̕\�����@���E�B���h�E���[�h�ɕύX����B
	ChangeWindowMode(true);

	SetUseDirect3D9Ex(FALSE);


	// DX���C�u����������������B
	if (DxLib_Init() == -1) return -1;

	SetGraphMode(1024, 768, 32);

	//�`���𗠉�ʂɕύX����B
	SetDrawScreen(DX_SCREEN_BACK);
	//Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();


	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);



	HandleCreater hc;

	hc.loadOrigins();

	double loadMax = GetASyncLoadNum();
	double load;
	int loadS;
	std::vector< std::string > loadingMessage;

	loadingMessage.push_back("N");
	loadingMessage.push_back("o");
	loadingMessage.push_back("w");
	loadingMessage.push_back("L");
	loadingMessage.push_back("o");
	loadingMessage.push_back("a");
	loadingMessage.push_back("d");
	loadingMessage.push_back("i");
	loadingMessage.push_back("n");
	loadingMessage.push_back("g");


	std::vector<std::shared_ptr< BezierCurve_ThreePoint >> _beziers;

	for (int i = 0; i < loadingMessage.size(); i++){
		_beziers.push_back(std::make_shared<BezierCurve_ThreePoint>());
		_beziers[i]->setPoint(350 + (i * 35), 400, 350 + (i * 35), 400, 350 + (i * 35), 400 - 50, 0.025f, 100);
		_beziers[i]->start();

	}
	SetFontSize(40);

	int timer = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
		if (!hc.isLoadOrigin()){
			load = 100 - ((GetASyncLoadNum() / loadMax) * 100);
			loadS = load;

			//	DrawString(350, 400, "Now Loading", GetColor(255, 255, 255));

			int j = 0;

			timer++;
			int finishNum = 0;

			for (int i = 0; i < _beziers.size(); i++){
				if (timer / 10 > i && !_beziers[i]->isEnd()){	//10�b���Ƃɒx�点�ăX�^�[�g����B
					_beziers[i]->start();
				}

				if (_beziers[_beziers.size() - 1]->isEnd()){
					for (int i = 0; i < loadingMessage.size(); i++){
						_beziers[i]->setPoint(350 + (i * 35), 400, 350 + (i * 35), 400, 350 + (i * 35), 400 - 50, 0.025f, 100);
					}

					timer = 0;
				}

				if (!_beziers[i]->isEnd()){
					DrawString(_beziers[i]->get_x(), _beziers[i]->get_y(), loadingMessage[i].c_str(), GetColor(255 - i * 18, 255 - i * 18, 255 - i * 18));
				}
				else{
					DrawString(350 + (i * 35), 400, loadingMessage[i].c_str(), GetColor(255 - i * 18, 255 - i * 18, 255 - i * 18));
				}
			}

			DrawString(500, 450, std::to_string(loadS).c_str(), GetColor(255, 255, 255));
			DrawString(550, 450, " %", GetColor(255, 255, 255));
		}
		else{
			SceneUpdater::getInstance()->update();

			HitBoxUpdater::getInstance()->update();
			DamageDisplay::getInstance()->update();
			Key::getInstance()->update();
			EffectUpdater::getInstance()->update();
			MessgeBox::getInstance()->update();
			//	clsDx();
		}
	}
	/*






		SceneUpdater::getInstance()->update();

		HitBoxUpdater::getInstance()->update();
		DamageDisplay::getInstance()->update();
		Key::getInstance()->update();
		EffectUpdater::getInstance()->update();
		MessgeBox::getInstance()->update();

		}*/

	DxLib_End(); // DX���C�u�����I������
	return 0;
}