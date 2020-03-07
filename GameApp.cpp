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
	// DirectX9を使用するようにする。
	// Effekseerを使用するには必ず設定する。
	//SetUseDirect3DVersion(DX_DIRECT3D_9EX);
	// DXライブラリの表示方法をウィンドウモードに変更する。
	ChangeWindowMode(true);

	SetUseDirect3D9Ex(FALSE);


	// DXライブラリを初期化する。
	if (DxLib_Init() == -1) return -1;

	SetGraphMode(1024, 768, 32);

	//描画先を裏画面に変更する。
	SetDrawScreen(DX_SCREEN_BACK);
	//Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();


	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
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
				if (timer / 10 > i && !_beziers[i]->isEnd()){	//10秒ごとに遅らせてスタートする。
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

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}