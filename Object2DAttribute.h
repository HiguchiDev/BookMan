#pragma once

class Object2DAttribute
{
public:
	//詳しくはDxライブラリ置き場の	int DrawBillboard3D( VECTOR Pos, float cx, float cy, float Size, float Angle, int GrHandle, int TransFlag ) ;　を見てね


	float _cx, _cy;	//描画する画像の中心座標(0.0f ～ 1.0f)
	float _size;	//描画する画像のサイズ
	float _angle;	//描画する画像の回転角度(ラジアン単位)
	int _handle;	// 描画する画像のハンドル
	bool _transFlag; //画像の透明度を有効にするかどうか（ TRUE：有効　FALSE：無効 ）
	
	Object2DAttribute();
	~Object2DAttribute();
};

