#include "HandleCreater.h"
#include "DxLib.h"
#include "Obstacle.h"

HandleCreater::HandleCreater()
{
}


HandleCreater::~HandleCreater()
{
}

bool HandleCreater::isOriginHandle(int handle)
{
	for (auto originHandle : _originHandles){
		if (originHandle == handle){
			return true;
		}
	}
	return false;
}

std::vector<int> HandleCreater::_originHandles;
std::vector<std::string> HandleCreater::_registeredHandleName;


void HandleCreater::loadOrigins()
{
	/*_obstacleNames.push_back("cake");
	_obstacleNames.push_back("strawberry");
	_obstacleNames.push_back("cracker");
	_obstacleNames.push_back("crackerSingle");
	_obstacleNames.push_back("chocolate");
	_obstacleNames.push_back("koke");
	_obstacleNames.push_back("TutorialBlock");
	*/

	SetUseASyncLoadFlag(true);
	_handleMap["cake.pmd"] = MV1LoadModel("cake.pmd");
	_handleMap["strawberry.pmd"] = MV1LoadModel("strawberry.pmd");
	_handleMap["cracker.pmd"] = MV1LoadModel("cracker.pmd");
	_handleMap["crackerSingle.pmd"] = MV1LoadModel("crackerSingle.pmd");
	_handleMap["chocolate.pmd"] = MV1LoadModel("chocolate.pmd");
	_handleMap["koke.pmd"] = MV1LoadModel("koke.pmd");
	_handleMap["主人公/主人公魔女剣.pmd"] = MV1LoadModel("主人公/主人公魔女剣.pmd");
	_handleMap["主人公/主人公魔女杖.pmd"] = MV1LoadModel("主人公/主人公魔女杖.pmd");
	_handleMap["主人公/主人公魔女槌.pmd"] = MV1LoadModel("主人公/主人公魔女槌.pmd");
	_handleMap["主人公/主人公yoroi槌.pmd"] = MV1LoadModel("主人公/主人公yoroi槌.pmd");
	_handleMap["主人公/主人公yoroi杖.pmd"] = MV1LoadModel("主人公/主人公yoroi杖.pmd");
	_handleMap["主人公/主人公yoroi剣.pmd"] = MV1LoadModel("主人公/主人公yoroi剣.pmd");
	_handleMap["enemy.pmd"] = MV1LoadModel("enemy.pmd");
	_handleMap["宝箱(ミミック)/宝箱(ミミック).pmd"] = MV1LoadModel("宝箱(ミミック)/宝箱(ミミック).pmd");
	_handleMap["ピエロ.pmd"] = MV1LoadModel("ピエロ.pmd");
	_handleMap["ダークピエロ.pmd"] = MV1LoadModel("ダークピエロ.pmd");
	_handleMap["キャンディ.pmd"] = MV1LoadModel("キャンディ.pmd");
	_handleMap["レッドキャンディ.pmd"] = MV1LoadModel("レッドキャンディ.pmd");
	_handleMap["bag.pmd"] = MV1LoadModel("bag.pmd");
	_handleMap["ジャグラー/Juggler.pmd"] = MV1LoadModel("ジャグラー/Juggler.pmd");
	_handleMap["魔女.pmd"] = MV1LoadModel("魔女.pmd");
	_handleMap["宮本/Miyamoto.pmd"] = MV1LoadModel("宮本/Miyamoto.pmd");
	_handleMap["水の精霊/Water.pmd"] = MV1LoadModel("水の精霊/Water.pmd");
	_handleMap["アンコウ/Ankou.pmd"] = MV1LoadModel("アンコウ/Ankou.pmd");
	_handleMap["花/Hana.pmd"] = MV1LoadModel("花/Hana.pmd");
	_handleMap["キングスライム/Kingsuraimu.pmd"] = MV1LoadModel("キングスライム/Kingsuraimu.pmd");
	_handleMap["ドラキー/Doraki.pmd"] = MV1LoadModel("ドラキー/Doraki.pmd");
	_handleMap["火車/Kasya.pmd"] = MV1LoadModel("火車/Kasya.pmd");
	_handleMap["ゴレムス君/ゴレムス君.pmd"] = MV1LoadModel("ゴレムス君/ゴレムス君.pmd");
	_handleMap["ゴレムス君亜種/ゴレムス君亜種.pmd"] = MV1LoadModel("ゴレムス君亜種/ゴレムス君亜種.pmd");
	_handleMap["BookMonster/BookMonster.pmd"] = MV1LoadModel("BookMonster/BookMonster.pmd");
	_handleMap["たまご君/たまご君.pmd"] = MV1LoadModel("たまご君/たまご君.pmd");
	_handleMap["キノコ君/キノコ君.pmd"] = MV1LoadModel("キノコ君/キノコ君.pmd");
	_handleMap["モフモフ君/モフモフ君.pmd"] = MV1LoadModel("モフモフ君/モフモフ君.pmd");
	_handleMap["ぺんぺん君/ぺんぺん君.pmd"] = MV1LoadModel("ぺんぺん君/ぺんぺん君.pmd");
	_handleMap["BookMonster亜種/BookMonster亜種.pmd"] = MV1LoadModel("BookMonster亜種/BookMonster亜種.pmd");
	_handleMap["たまご君亜種/たまご君亜種.pmd"] = MV1LoadModel("たまご君亜種/たまご君亜種.pmd");
	_handleMap["キノコ君亜種/キノコ君亜種.pmd"] = MV1LoadModel("キノコ君亜種/キノコ君亜種.pmd");
	_handleMap["モフモフ君亜種/モフモフ君亜種.pmd"] = MV1LoadModel("モフモフ君亜種/モフモフ君亜種.pmd");
	_handleMap["ぺんぺん君亜種/ぺんぺん君亜種.pmd"] = MV1LoadModel("ぺんぺん君亜種/ぺんぺん君亜種.pmd");
	_handleMap["宝箱(ミミック)亜種/宝箱(ミミック)亜種.pmd"] = MV1LoadModel("宝箱(ミミック)亜種/宝箱(ミミック)亜種.pmd");
	_handleMap["アンコウ亜種/Ankouasyu.pmd"] = MV1LoadModel("アンコウ亜種/Ankouasyu.pmd");
	_handleMap["キングスライムレッド/KingsuraimuRed.pmd"] = MV1LoadModel("キングスライムレッド/KingsuraimuRed.pmd");
	_handleMap["クラーケン　足1/kurakenLegOne.pmd"] = MV1LoadModel("クラーケン　足1/kurakenLegOne.pmd");
	_handleMap["クラーケン　足2/kurakenLegTwo.pmd"] = MV1LoadModel("クラーケン　足2/kurakenLegTwo.pmd");
	_handleMap["クラーケン　本体/kuraken.pmd"] = MV1LoadModel("クラーケン　本体/kuraken.pmd");
	_handleMap["闇宮本/MiyamotoDark.pmd"] = MV1LoadModel("闇宮本/MiyamotoDark.pmd");
	_handleMap["ジャグラー亜種/JugglerAsyu.pmd"] = MV1LoadModel("ジャグラー亜種/JugglerAsyu.pmd");
	_handleMap["花亜種/HanaAsyu.pmd"] = MV1LoadModel("花亜種/HanaAsyu.pmd");
	_handleMap["水車/Suisya.pmd"] = MV1LoadModel("水車/Suisya.pmd");
	_handleMap["火の精霊/Faire.pmd"] = MV1LoadModel("火の精霊/Faire.pmd");
	_handleMap["ドラキーグリーン/GreenDoraki.pmd"] = MV1LoadModel("ドラキーグリーン/GreenDoraki.pmd");
	_handleMap["TutorialEnemy.pmd"] = MV1LoadModel("TutorialEnemy.pmd");
	_handleMap["openingTitle2.pmd"] = MV1LoadModel("openingTitle2.pmd");
	_handleMap["potion.pmd"] = MV1LoadModel("potion.pmd");
	_handleMap["saveBook.pmd"] = MV1LoadModel("saveBook.pmd");
	_handleMap["TreasureChest/TreasureChest.pmd"] = MV1LoadModel("TreasureChest/TreasureChest.pmd");
	_handleMap["剣.pmd"] = MV1LoadModel("剣.pmd");
	_handleMap["Stairs.pmd"] = MV1LoadModel("Stairs.pmd");
	_handleMap["服.pmd"] = MV1LoadModel("服.pmd");
	_handleMap["Spring.pmd"] = MV1LoadModel("Spring.pmd");
	_handleMap["Needle.pmd"] = MV1LoadModel("Needle.pmd");
	_handleMap["HanselAndGretelStageFloor.pmd"] = MV1LoadModel("HanselAndGretelStageFloor.pmd");
	_handleMap["HanselAndGretelStageSaveFloor.pmd"] = MV1LoadModel("HanselAndGretelStageSaveFloor.pmd");
	_handleMap["SeabedTempleStageSaveFloor.pmd"] = MV1LoadModel("SeabedTempleStageSaveFloor.pmd");
	_handleMap["SeabedTempleStageFloor.pmd"] = MV1LoadModel("SeabedTempleStageFloor.pmd");
	_handleMap["exp.pmd"] = MV1LoadModel("exp.pmd");
	_handleMap["exp.mqo"] = MV1LoadModel("exp.mqo");
	_handleMap["hitBox.mqo"] = MV1LoadModel("hitBox.mqo");
	_handleMap["TutorialStageFloor.pmd"] = MV1LoadModel("TutorialStageFloor.pmd");
	_handleMap["TutorialStageSaveFloor.pmd"] = MV1LoadModel("TutorialStageSaveFloor.pmd");
	_handleMap["TutorialBlock.pmd"] = MV1LoadModel("TutorialBlock.pmd");
	_handleMap["bigrock.pmd"] = MV1LoadModel("bigrock.pmd");
	_handleMap["beautifulrock.pmd"] = MV1LoadModel("beautifulrock.pmd");
	_handleMap["table.pmd"] = MV1LoadModel("table.pmd");
	_handleMap["savetableyoko.pmd"] = MV1LoadModel("savetableyoko.pmd");
	_handleMap["savetabletate.pmd"] = MV1LoadModel("savetabletate.pmd");
	_handleMap["savetablecorner.pmd"] = MV1LoadModel("savetablecorner.pmd");
	_handleMap["savewall.pmd"] = MV1LoadModel("savewall.pmd");
	_handleMap["tallglass.pmd"] = MV1LoadModel("tallglass.pmd");
	_handleMap["tree.pmd"] = MV1LoadModel("tree.pmd");
	_handleMap["cobble.pmd"] = MV1LoadModel("cobble.pmd");
	_handleMap["woodbox.pmd"] = MV1LoadModel("woodbox.pmd");
	_handleMap["MazeOfGrasslandStageFloor.pmd"] = MV1LoadModel("MazeOfGrasslandStageFloor.pmd");
	_handleMap["MazeOfGrasslandStageSaveFloor.pmd"] = MV1LoadModel("MazeOfGrasslandStageSaveFloor.pmd");
	
	SetUseASyncLoadFlag(false);

}

int HandleCreater::get3DHandle(std::string fileName)
{
	int handle;

	auto itr = _handleMap.find(fileName);
	
	if (itr == _handleMap.end()){
		SetUseASyncLoadFlag(false);
		handle = MV1LoadModel(fileName.c_str());

	//	printfDx("fn : %s\n", fileName.c_str());
	//	printfDx("fn  handle : %d\n", handle);
		if (handle != -1){
			add(handle, fileName);
		}

	}
	else{
		handle = MV1DuplicateModel(_handleMap[fileName]);
	}


	return handle;
}

void HandleCreater::add(int handle, std::string fileName)
{
	_handleMap[fileName] = handle;
	_originHandles.push_back(handle);
	_registeredHandleName.push_back(fileName);
}

int HandleCreater::getDuplicate3DHandle(int handle)
{
	return MV1DuplicateModel(handle);
}