#include "Object2DAttribute.h"


Object2DAttribute::Object2DAttribute()
{
	_cx = 0.0f;
	_cy = 0.0f;	//描画する画像の中心座標(0.0f ～ 1.0f)
	_size = 0.0f;	//描画する画像のサイズ
	_angle = 0.0f;	//描画する画像の回転角度(ラジアン単位)
	_handle = -1;	// 描画する画像のハンドル
	_transFlag = false; //画像の透明度を
}


Object2DAttribute::~Object2DAttribute()
{
}
